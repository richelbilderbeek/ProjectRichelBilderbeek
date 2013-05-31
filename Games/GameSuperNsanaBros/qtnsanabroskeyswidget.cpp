//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#include <QPainter>
//---------------------------------------------------------------------------
#include "nsanabrosqtheader.h"
#include "qtnsanabroskeyswidget.h"
//---------------------------------------------------------------------------
QtNsanaBrosKeysWidget::QtNsanaBrosKeysWidget(
  const NsanaBrosKeys * const keys,
  QWidget *parent)
  : QWidget(parent),
    m_keys(keys)
{
  TRACE_FUNC();
  m_keys->m_signal_keyschanged.connect(
    boost::bind(
      &QtNsanaBrosKeysWidget::OnKeysChanged,
      this));

}
//---------------------------------------------------------------------------
void QtNsanaBrosKeysWidget::OnKeysChanged()
{
  this->repaint();
}
//---------------------------------------------------------------------------
void QtNsanaBrosKeysWidget::paintEvent(QPaintEvent *)
{
  QPainter p(this);
  const int width  = this->width();
  const int height = this->height();
  const int midx = width / 2;
  const int midy = height / 2;

  //Draw black background
  p.setBrush(QBrush(Qt::black));
  p.setPen(QPen(Qt::black));

  p.drawLine(
    midx,
    midy,
    midx + (midx * m_keys->GetHorizontal()),
    midy + (midy * m_keys->GetVertical()));
}
//---------------------------------------------------------------------------


