#ifndef QTTESTQTROUNDEDRECTITEMWIDGET_H
#define QTTESTQTROUNDEDRECTITEMWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsView>
#pragma GCC diagnostic pop

namespace ribi {

///The widget holding the items
struct QtTestQtRoundedRectItemWidget : public QGraphicsView
{
  QtTestQtRoundedRectItemWidget(QWidget *parent = 0);
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDRECTITEMWIDGET_H
