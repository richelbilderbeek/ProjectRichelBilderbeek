#ifndef QTKNOKFIGHTERBACKGROUND_H
#define QTKNOKFIGHTERBACKGROUND_H

#include <QGraphicsPixmapItem>

struct QtKnokfighterBackground : public QGraphicsPixmapItem
{

  QtKnokfighterBackground(
    const int width, const int height,
    QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);


  void advance(int);

  private:
  int z;

  void DrawPixmap();
};

#endif // QTKNOKFIGHTERBACKGROUND_H
