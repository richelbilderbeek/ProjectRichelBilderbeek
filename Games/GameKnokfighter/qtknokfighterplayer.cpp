#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtknokfighterplayer.h"

#include <QBitmap>
#include <QPixmap>
#include <QGraphicsScene>
#include "qtknokfighterbackground.h"
#pragma GCC diagnostic pop

ribi::QtKnokfighterPlayer::QtKnokfighterPlayer(
  const Name name,
  QGraphicsItem *parent)
  : QGraphicsPixmapItem(parent),
    m_name(name == Name::richel ? "Richel" : "Joost"),
    m_z(0)
{
  DrawPixmap();
}

void ribi::QtKnokfighterPlayer::advance(int i)
{
  if (i)
  {
    //this->setPos(this->x() + 10,this->y());
    ++m_z;
    DrawPixmap();
  }
}

void ribi::QtKnokfighterPlayer::DrawPixmap()
{
  std::string s;
  switch ((m_z / 50) % 2)
  {
    case 0: s = ":/images/" + m_name + "LooptRechts1.png"; break;
    case 1: s = ":/images/" + m_name + "LooptRechts2.png"; break;
  }
  {
    QPixmap pixmap(s.c_str());
    const QBitmap mask = pixmap.createMaskFromColor(QColor(0,0,255));
    pixmap.setMask(mask);
    this->setPixmap(pixmap);
  }
}
