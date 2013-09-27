#ifndef QTTEXTPOSITIONWIDGET_H
#define QTTEXTPOSITIONWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QtTextPositionWidget : public QGraphicsView
{
  QtTextPositionWidget(const std::vector<std::string>& items);
};

#endif // QTTEXTPOSITIONWIDGET_H
