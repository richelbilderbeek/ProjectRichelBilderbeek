//---------------------------------------------------------------------------
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
//---------------------------------------------------------------------------
#include "nsanabrosqtheader.h"
#include "qtnsanabrosgamearea2dwidget.h"
//---------------------------------------------------------------------------
QtNsanaBrosGameArea2dWidget::QtNsanaBrosGameArea2dWidget(
  NsanaBrosGame * const game,
  QWidget *parent)
  : QWidget(parent),
    m_game(game)
{
  TRACE_FUNC();
  if (m_game)
  {
    m_game->m_signal_repaint.connect(
      boost::bind(
        &QtNsanaBrosGameArea2dWidget::Repaint,
        this));
  }
}
//---------------------------------------------------------------------------
void QtNsanaBrosGameArea2dWidget::paintEvent(QPaintEvent *)
{
  QPainter p(this);

  const double block_width
    = boost::numeric_cast<double>(this->width())
    / boost::numeric_cast<double>(m_game->GetWidth());
  const double block_height
    = boost::numeric_cast<double>(this->height())
    / boost::numeric_cast<double>(m_game->GetHeight());

  //Draw black background
  p.setBrush(QBrush(Qt::black));
  p.setPen(QPen(Qt::black));
  p.drawRect(this->rect());

  //Obtain all background sprites
  const std::vector<const NsanaBrosSprite*> sprites = m_game->GetSprites();
  //Obtain player sprite

  BOOST_FOREACH(const NsanaBrosSprite* sprite, sprites)
  {
    const int x1
      = boost::numeric_cast<int>(
          sprite->GetX() * block_width);
    const int y1
      = boost::numeric_cast<int>(
          sprite->GetY() * block_height);
    const int width
      = boost::numeric_cast<int>(
          sprite->GetWidth() * block_width);
    const int height
      = boost::numeric_cast<int>(
          sprite->GetHeight() * block_height);
    p.setPen(QPen(QColor(sprite->GetRed(),sprite->GetGreen(),sprite->GetBlue())));
    p.setBrush(QBrush(QColor(sprite->GetRed(),sprite->GetGreen(),sprite->GetBlue())));
    p.drawRect(x1,y1,width,height);
  }
}
//---------------------------------------------------------------------------
void QtNsanaBrosGameArea2dWidget::Repaint()
{
  this->repaint();
}
//---------------------------------------------------------------------------



