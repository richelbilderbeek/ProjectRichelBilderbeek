#ifndef QTTEXTPOSITIONWIDGET_H
#define QTTEXTPOSITIONWIDGET_H

#include <QGraphicsView>

struct QtTextPositionWidget : public QGraphicsView
{
  QtTextPositionWidget(const std::vector<std::string>& items);
};

#endif // QTTEXTPOSITIONWIDGET_H
