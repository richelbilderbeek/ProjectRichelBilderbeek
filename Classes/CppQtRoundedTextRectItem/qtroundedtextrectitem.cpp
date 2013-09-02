//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtroundedtextrectitem.h"

#include <cassert>
#include <sstream>
#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <QInputDialog>
#include <QPainter>

//#include "trace.h"
#pragma GCC diagnostic pop

const QtRoundedTextRectItem::Padding QtRoundedTextRectItem::m_text_padding(3.0,0.0,0.0,3.0);

QtRoundedTextRectItem::QtRoundedTextRectItem(
  const std::string& text,
  const Padding& padding,
  const QFont& font,
  QGraphicsItem* parent)
  : QtRoundedRectItem(parent),
    m_font(font),
    m_padding(padding),
    m_text("") //Empty std::string, as m_text must be set by SetText
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

const QRectF QtRoundedTextRectItem::GetPaddedTextRect() const
{
  return GetTextRect().adjusted(
    -m_text_padding.left,
    -m_text_padding.top,
     m_text_padding.right,
     m_text_padding.bottom);
}

const QRectF QtRoundedTextRectItem::GetTextRect() const
{
  const double h = QFontMetricsF(m_font).height();
  const double w = QFontMetricsF(m_font).width(m_text.c_str());
  #ifdef _WIN32
  //adjusted(0.0,0.0,2.0,0.0) works fine for 50% of the fonts supplied by Wine under native Lubuntu
  //adjusted(0.0,0.0,3.0,0.0) works fine for 80% of the fonts supplied by Wine under native Lubuntu
  return QRectF(-0.5 * w, -0.5 * h,w,h).adjusted(0.0,0.0,3.0,0.0);
  #else
  //adjusted(0.0,0.0,2.0,-1.0) works fine for 90% of the fonts under native Lubuntu
  //adjusted(0.0,0.0,3.0,-1.0) works fine for 99% of the fonts under native Lubuntu
  //adjusted(0.0,0.0,4.0,-1.0) works fine for all the fonts I've tried under native Lubuntu
  return QRectF(-0.5 * w, -0.5 * h,w,h).adjusted(0.0,0.0,2.0,-1.0);
  #endif
}

const std::string QtRoundedTextRectItem::GetVersion()
{
  return "1.3";
}

const std::vector<std::string> QtRoundedTextRectItem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-19: version 1.0: initial version");
  v.push_back("2012-12-20: version 1.1: added response to key press, text is displayed fully");
  v.push_back("2012-12-21: version 1.2: added debug drawing, text is displayed correctly to the pixel");
  v.push_back("2012-12-28: version 1.3: fixed incomplete displaying when using Wine");
  return v;
}

void QtRoundedTextRectItem::keyPressEvent(QKeyEvent* event)
{
  switch (event->key())
  {
    case Qt::Key_F2:
    {
      bool ok = true;
      const QString s = QInputDialog::getText(0,"Edit text","New text",QLineEdit::Normal,m_text.c_str(),&ok);
      if (ok) SetText(s.toStdString());
    }
    break;
  }
  QtRoundedRectItem::keyPressEvent(event);
}

void QtRoundedTextRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  QtRoundedRectItem::paint(painter,option,widget);
  painter->setFont(m_font);
  //#define DISPLAY_DIFFERENT_RECTS_873658735672347834573985792
  #ifdef  DISPLAY_DIFFERENT_RECTS_873658735672347834573985792
  painter->setBrush(QBrush(QColor(255,0,0)));
  painter->drawRect(this->GetPaddedTextRect());
  painter->setBrush(QBrush(QColor(0,0,255)));
  painter->drawRect(this->GetTextRect());
  #endif
  painter->setPen(m_text_pen);
  painter->drawText(GetTextRect(),m_text.c_str());
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
void QtRoundedTextRectItem::SetFont(const QFont& font)
{
  if (m_font != font)
  {
    m_font = font;
    this->update();
    this->m_signal_item_has_updated(this);
    m_signal_request_scene_update();
  }
}
#pragma GCC diagnostic pop

void QtRoundedTextRectItem::SetPadding(const Padding& padding)
{
  if ( padding.bottom != m_padding.bottom
    || padding.left   != m_padding.left
    || padding.right  != m_padding.right
    || padding.top    != m_padding.top
    )
  {
    m_padding = padding;
    const QRectF text_rect = GetPaddedTextRect();
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

void QtRoundedTextRectItem::SetText(const std::string& text)
{
  if (text != m_text)
  {
    m_text = text;
    const QRectF text_rect = GetPaddedTextRect();
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

void QtRoundedTextRectItem::SetTextPen(const QPen& pen)
{
  if (m_text_pen != pen)
  {
    m_text_pen = pen;
    this->update();
    this->m_signal_item_has_updated(this);
  }
}
