#ifndef QTWIDGET_H
#define QTWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <functional>

#include <QGraphicsView>
#pragma GCC diagnostic pop

///The widget holding the items
struct QtWidget : public QGraphicsView
{
  QtWidget(QWidget *parent = 0);


  ///Respond to a key press
  void keyPressEvent(QKeyEvent *event);

  private:

  ///Obtain the closest item in the collection
  QGraphicsItem * GetClosest(
    const QGraphicsItem * const focus_item,
    const std::vector<QGraphicsItem *>& items) const;

  static double GetDistance(const QPointF& a, const QPointF& b);

  ///Obtain the items above the focus_item
  const std::vector<QGraphicsItem *> GetItemsAbove(const QGraphicsItem * const focus_item) const;

  ///Obtain the items below the focus_item
  const std::vector<QGraphicsItem *> GetItemsBelow(const QGraphicsItem * const focus_item) const;

  ///Obtain the items left of the focus_item
  const std::vector<QGraphicsItem *> GetItemsLeft(const QGraphicsItem * const focus_item) const;

  ///Obtain the items right of the focus_item
  const std::vector<QGraphicsItem *> GetItemsRight(const QGraphicsItem * const focus_item) const;

  ///Give focus to a random item
  void SetRandomFocus();

  ///Add selection to a random item
  void SetRandomSelect();
};

#endif // QTWIDGET_H
