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
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);

  ///Obtain a white background
  this->setBrush(QBrush(QColor(255,255,255)));

  this->SetFont(font);
  this->SetRadiusX(4.0);
  this->SetRadiusY(4.0);
  this->SetText(text);

}

QRectF ribi::QtRoundedEditRectItem::GetPaddedTextRect(const std::string& s) const noexcept
{
  return GetTextRect(s).adjusted(
    -m_text_padding.left,
    -m_text_padding.top,
     m_text_padding.right,
     m_text_padding.bottom);
}

QRectF ribi::QtRoundedEditRectItem::GetTextRect(const std::string& s) const noexcept
{
  const double h = QFontMetricsF(m_font).height();
  const double w = QFontMetricsF(m_font).width(s.c_str());
  #ifdef _WIN32
  //adjusted(0.0,0.0,2.0,0.0) works fine for 50% of the fonts supplied by Wine under native Lubuntu
  //adjusted(0.0,0.0,3.0,0.0) works fine for 80% of the fonts supplied by Wine under native Lubuntu
  return QRectF(-0.5 * w, 0.0,w,h).adjusted(0.0,0.0,3.0,0.0);
  #else
  //adjusted(0.0,0.0,2.0,-1.0) works fine for 90% of the fonts under native Lubuntu
  //adjusted(0.0,0.0,3.0,-1.0) works fine for 99% of the fonts under native Lubuntu
  //adjusted(0.0,0.0,4.0,-1.0) works fine for all the fonts I've tried under native Lubuntu
  //return QRectF(-0.5 * w,0.0,w,h).adjusted(0.0,0.0,2.0,-1.0);
  return QRectF(-0.5 * w,0.0,w,h).adjusted(0.0,0.0,2.0,0.0);
  #endif


}

QRectF ribi::QtRoundedEditRectItem::GetTextRect(const std::vector<std::string>& text) const noexcept
{
  std::vector<QRectF> v;
  std::transform(text.begin(),text.end(),std::back_inserter(v),
    [this](const std::string& s)
    {
      return this->GetPaddedTextRect(s);
    }
  );
  const auto width_iter = std::max_element(v.begin(),v.end(),
    [this](const QRectF& lhs, const QRectF& rhs)
    {
      return lhs.width() < rhs.width();
    }
  );
  const double width = width_iter == v.end() ? 1.0 : width_iter->width();
  const double height = std::accumulate(v.begin(),v.end(),0.0,
    [](double& init, const QRectF& r)
    {
      return init + r.height() + 0.0;
    }
  );

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
  QtRoundedRectItem::paint(painter,option,widget);

  painter->setFont(m_font);
  painter->setPen(m_text_pen);
  const int sz = static_cast<int>(m_text.size());
  //const double line_height = rect().height() / static_cast<double>(sz);
  for (int i=0; i!=sz;++i)
  {
    const std::string& s = m_text[i];
    //Set the padded text rectangle
    QRectF padded_rect = GetPaddedTextRect(s);


    padded_rect.translate(
      0.0,
      rect().top() +  m_text_padding.top + (static_cast<double>(i) * (0.0 + padded_rect.height()))
      );

    const QRectF r(
      padded_rect.adjusted(
         m_text_padding.left,
         m_text_padding.top,
        -m_text_padding.right,
        -m_text_padding.bottom
        )
      );

    assert(r.left() >= this->rect().left());
    assert(r.left() < this->rect().right());
    assert(r.top()  >= this->rect().top());
    assert(r.top()  < this->rect().bottom());
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
    m_signal_request_scene_update();
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
    const QRectF text_rect = GetTextRect(m_text);
    this->SetRoundedRect(
      text_rect.adjusted(
        -m_padding.left,
        -m_padding.top,
         m_padding.right,
         m_padding.bottom),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
    this->update();
    m_signal_request_scene_update();
  }
}

void ribi::QtRoundedEditRectItem::SetText(const std::vector<std::string>& text)
{
  if (text != m_text)
  {
    m_text = text;
    const QRectF text_rect = GetTextRect(m_text);
    this->SetRoundedRect(
      text_rect.adjusted(
        -m_padding.left,
        -m_padding.top,
         m_padding.right,
         m_padding.bottom),
      this->GetRadiusX(),
      this->GetRadiusY()
    );
    this->update();
    this->m_signal_item_has_updated(this);
    m_signal_request_scene_update();
  }
}

void ribi::QtRoundedEditRectItem::SetTextPen(const QPen& pen)
{
  if (m_text_pen != pen)
  {
    m_text_pen = pen;
    this->update();
    this->m_signal_item_has_updated(this);
  }
}
