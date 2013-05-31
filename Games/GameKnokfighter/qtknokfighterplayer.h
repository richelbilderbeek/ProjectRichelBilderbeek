#ifndef QTKNOKFIGHTERPLAYER_H
#define QTKNOKFIGHTERPLAYER_H

#include <QGraphicsPixmapItem>

struct QtKnokfighterPlayer : public QGraphicsPixmapItem
{
  enum class Name { richel, joost };

  QtKnokfighterPlayer(
    const Name name,
    QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

  void advance(int);

  private:
  int m_z;

  ///The fighter his/her name
  const std::string m_name;

  void DrawPixmap();
};

#endif // QTKNOKFIGHTERPLAYER_H
