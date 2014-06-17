//---------------------------------------------------------------------------
/*
QtRoundedEditRectItem, editable rectangular-shaped QGraphicsItem
Copyright (C) 2012-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/QtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtroundededitrectitem.h"

#include <cassert>
#include <sstream>
#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <QInputDialog>
#include <QPainter>

#include "container.h"
#include "trace.h"

#pragma GCC diagnostic pop

const ribi::QtRoundedEditRectItem::Padding ribi::QtRoundedEditRectItem::m_text_padding(3.0,0.0,0.0,3.0);

ribi::QtRoundedEditRectItem::QtRoundedEditRectItem(
  const std::vector<std::string>& text,
  const Padding& padding,
  const QFont& font,
  QGraphicsItem* parent)
  : QtRoundedRectItem(parent),
    m_signal_item_requests_edit{},
    m_font(font),
    m_padding(padding),
    m_text( {""} ), //Empty std::vector<std::string>, as m_text must be set by SetText
    m_text_pen{}
{
  #ifndef NDEBUG
  Test();
  #endif

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  ///Obtain a white background
  this->setBrush(QBrush(QColor(255,255,255)));

  this->SetFont(font);
  this->SetRadiusX(4.0);
  this->SetRadiusY(4.0);
  this->SetPadding(Padding(1.0,1.0,1.0,1.0));
  this->SetText(text);
  this->update();
}

ribi::QtRoundedEditRectItem::~QtRoundedEditRectItem() noexcept
{
  //OK
}

const QFont& ribi::QtRoundedEditRectItem::GetFont() const noexcept
{
  return m_font;
}

QRectF ribi::QtRoundedEditRectItem::GetPaddedTextRect(
  const std::string& s,
  const QFont& font
) noexcept
{
  return GetTextRect(s,font).adjusted(
    -m_text_padding.left,
    -m_text_padding.top,
     m_text_padding.right,
     m_text_padding.bottom);
}

const std::vector<std::string>& ribi::QtRoundedEditRectItem::GetText() const noexcept
{
  return m_text;
}

QRectF ribi::QtRoundedEditRectItem::GetTextRect(
  const std::string& s,
  const QFont& font
) noexcept
{
  const double h = QFontMetricsF(font).height();
  const double w = QFontMetricsF(font).width(s.c_str());
  assert(h > 0.0);
  assert(w >= 0.0 && "An empty text can have width 0");
  #ifdef _WIN32
  //adjusted(0.0,0.0,2.0,0.0) works fine for 50% of the fonts supplied by Wine under native Lubuntu
  //adjusted(0.0,0.0,3.0,0.0) works fine for 80% of the fonts supplied by Wine under native Lubuntu
  return QRectF(-0.5 * w, 0.0,w,h).adjusted(0.0,0.0,3.0,0.0);
  #else
  //adjusted(0.0,0.0,2.0,-1.0) works fine for 90% of the fonts under native Lubuntu
  //adjusted(0.0,0.0,3.0,-1.0) works fine for 99% of the fonts under native Lubuntu
  //adjusted(0.0,0.0,4.0,-1.0) works fine for all the fonts I've tried under native Lubuntu
  //return QRectF(-0.5 * w,0.0,w,h).adjusted(0.0,0.0,2.0,-1.0);
  const QRectF result = QRectF(-0.5 * w,0.0,w,h).adjusted(0.0,0.0,2.0,0.0);
  assert(result.width() >= 0.0);
  assert(result.height() > 0.0);
  return result;
  #endif


}

QRectF ribi::QtRoundedEditRectItem::GetTextRect(
  const std::vector<std::string>& text,
  const QFont& font) noexcept
{
  std::vector<QRectF> v;
  std::transform(text.begin(),text.end(),std::back_inserter(v),
    [font](const std::string& s)
    {
      return QtRoundedEditRectItem::GetPaddedTextRect(s,font);
    }
  );
  const auto width_iter = std::max_element(v.begin(),v.end(),
    [](const QRectF& lhs, const QRectF& rhs)
    {
      return lhs.width() < rhs.width();
    }
  );
  const double width = width_iter == v.end() ? 1.0 : width_iter->width();
  const double height = std::accumulate(v.begin(),v.end(),0.0,
    [](double& init, const QRectF& r)
    {
      assert(r.height() > 0.0);
      return init + r.height() + 0.0;
    }
  );

  assert(width  > 0.0);
  assert(height > 0.0);
  return QRectF(-0.5 * width,-0.5 * height, width, height).adjusted(-0.0,-0.0,0.0,0.0);
}

std::string ribi::QtRoundedEditRectItem::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtRoundedEditRectItem::GetVersionHistory() noexcept
{
  return {
    "2012-12-19: version 1.0: initial version"
  };
}

void ribi::QtRoundedEditRectItem::keyPressEvent(QKeyEvent* event) noexcept
{
  switch (event->key())
  {
    case Qt::Key_F2:
    m_signal_item_requests_edit(this);
    break;
  }
  QtRoundedRectItem::keyPressEvent(event);
}

void ribi::QtRoundedEditRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept
{
  const double border_width
    = std::max(GetContourPen().width(),GetFocusPen().width());

  //Possibly adapt the rounded rect border here
  {
    const QRectF text_rect = GetTextRect(m_text,m_font);
    this->SetRoundedRect(
      text_rect.adjusted(
        -m_padding.left   - border_width,
        -m_padding.top    - border_width,
         m_padding.right  + border_width,
         m_padding.bottom + border_width
      ),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
  }

  //Draws the rounded rectangle
  QtRoundedRectItem::paint(painter,option,widget);

  //Draw the text lines at the right spot
  painter->setFont(m_font);
  painter->setPen(m_text_pen);
  const int sz = static_cast<int>(m_text.size());
  //const double line_height = rect().height() / static_cast<double>(sz);
  for (int i=0; i!=sz;++i)
  {
    const std::string& s = m_text[i];
    //Set the padded text rectangle
    QRectF padded_rect = GetPaddedTextRect(s,m_font);
    const QRectF current_rect = GetRect();

    padded_rect.translate(
      0.0
      //  + (border_width / 2.0)
      ,
      current_rect.top()
        + m_text_padding.top
        + (static_cast<double>(i) * (0.0 + padded_rect.height()))
        + (border_width / 2.0)
    );
    //const auto focus_pen = GetFocusPen();
    const QRectF r(
      padded_rect.adjusted(
         m_text_padding.left,  // + (border_width / 2.0),
         m_text_padding.top,   //  + (border_width / 2.0),
        -m_text_padding.right, // + (border_width / 2.0),
        -m_text_padding.bottom //+ (border_width / 2.0)
      )
    );

    #ifndef NDEBUG
    if (r.left() < this->GetRect().left())
    {
      TRACE(GetRect().left());
      TRACE(GetRect().right());
      TRACE(GetRect().top());
      TRACE(GetRect().bottom());
      TRACE(r.left());
      TRACE(r.top());
      TRACE("BREAK");
    }
    #endif
    //assert(r.left() >= this->rect().left());
    //assert(r.left() < this->rect().right());
    //assert(r.top()  >= this->rect().top());
    //assert(r.top()  < this->rect().bottom());
    #ifndef NDEBUG
    //painter->setBrush(QBrush(QColor(255,0,0)));
    //painter->drawRect(r);
    #endif
    //Draw text to the unpadded text rectangle
    painter->drawText(r,s.c_str());
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
void ribi::QtRoundedEditRectItem::SetFont(const QFont& font)
{
  if (m_font != font)
  {
    m_font = font;
    this->update();
    //m_signal_request_scene_update();
  }
}
#pragma GCC diagnostic pop

void ribi::QtRoundedEditRectItem::SetPadding(const Padding& padding)
{
  if ( padding.bottom != m_padding.bottom
    || padding.left   != m_padding.left
    || padding.right  != m_padding.right
    || padding.top    != m_padding.top
    )
  {
    m_padding = padding;
    /*
    const QRectF text_rect = GetTextRect(m_text);
    const auto focus_pen = GetFocusPen();
    this->SetRoundedRect(
      text_rect.adjusted(
        -m_padding.left - (focus_pen.widthF() / 2.0),
        -m_padding.top  - (focus_pen.widthF() / 2.0),
         m_padding.right  + focus_pen.widthF(),
         m_padding.bottom + focus_pen.widthF()
      ),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
    */
    this->update();
    //m_signal_request_scene_update();
  }
}

void ribi::QtRoundedEditRectItem::SetText(const std::vector<std::string>& text)
{
  const bool verbose = false;

  if (text != m_text)
  {
    if (verbose)
    {
      std::stringstream s;
      s << "Text will change from '" << Container().ToStr(m_text)
        << "' to '" << Container().ToStr(text)
        << "'"
      ;
      TRACE(s.str());
    }
    m_text = text;
    /*
    const QRectF text_rect = GetTextRect(m_text,m_font);
    const double border_width
      = std::max(GetContourPen().width(),GetFocusPen().width());
    this->SetRoundedRect(
      text_rect.adjusted(
        -m_padding.left   - border_width,
        -m_padding.top    - border_width,
         m_padding.right  + border_width,
         m_padding.bottom + border_width
      ),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
    */
    this->update();
    //this->m_signal_item_has_updated(this);
    //m_signal_request_scene_update();
  }
  else
  {
    if (verbose)
    {
      std::stringstream s;
      s << "Text will remain '" << Container().ToStr(m_text)
        << "'"
      ;
      TRACE(s.str());
    }
  }
}

void ribi::QtRoundedEditRectItem::SetTextPen(const QPen& pen)
{
  if (m_text_pen != pen)
  {
    m_text_pen = pen;
    this->update();
    //this->m_signal_item_has_updated(this);
  }
}

#ifndef NDEBUG
void ribi::QtRoundedEditRectItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtRoundedEditRectItem::Test");
  for (const std::string& s: { "X" })
  {
    const QFont font;
    assert(GetTextRect(s,font).width() > 0.0);
    assert(GetPaddedTextRect(s,font).width() >= GetTextRect(s,font).width());
  }
  TRACE("Finished ribi::QtRoundedEditRectItem::Test successfully");
}
#endif
