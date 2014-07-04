#ifndef QTWIDGET_H
#define QTWIDGET_H

#include <QGraphicsView>

struct QwtPlotItem;

struct QtWidget : public QGraphicsView
{
  QtWidget(QGraphicsScene* scene = 0, QWidget* parent = 0);

  private:
  QwtPlotItem * m_item;

  void ReceiveValue(const double value);
};

#endif // QTWIDGET_H
