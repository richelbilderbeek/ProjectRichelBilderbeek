#ifndef QTKNOKFIGHTERPLAYER_H
#define QTKNOKFIGHTERPLAYER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsPixmapItem>
#pragma GCC diagnostic pop

namespace ribi {

struct QtKnokfighterPlayer : public QGraphicsPixmapItem
{
  enum class Name { richel, joost };

  QtKnokfighterPlayer(
    const Name name,
    QGraphicsItem *parent = 0);

  void advance(int);

  private:
  ///The fighter his/her name
  const std::string m_name;

  ///The fighter his/her Z-order
  int m_z;


  void DrawPixmap();
};

} //~namespace ribi

#endif // QTKNOKFIGHTERPLAYER_H
