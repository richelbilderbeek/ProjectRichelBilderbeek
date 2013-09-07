#ifndef QTKNOKFIGHTERBACKGROUND_H
#define QTKNOKFIGHTERBACKGROUND_H

#include <QGraphicsPixmapItem>

namespace ribi {

struct QtKnokfighterBackground : public QGraphicsPixmapItem
{

  QtKnokfighterBackground(
    const int width, const int height,
    QGraphicsItem *parent = 0);


  void advance(int);

  private:
  int z;

  void DrawPixmap();
};

} //~namespace ribi

#endif // QTKNOKFIGHTERBACKGROUND_H
