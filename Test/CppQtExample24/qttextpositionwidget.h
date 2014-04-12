#ifndef QTTEXTPOSITIONWIDGET_H
#define QTTEXTPOSITIONWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QtTextPositionWidget : public QGraphicsView
{
  QtTextPositionWidget(const std::vector<std::string>& items);
};

#endif // QTTEXTPOSITIONWIDGET_H
