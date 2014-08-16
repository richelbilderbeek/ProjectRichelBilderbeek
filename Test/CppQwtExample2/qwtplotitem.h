#ifndef QWTPLOTITEM_H
#define QWTPLOTITEM_H


#include <QGraphicsProxyWidget>

struct QwtPlotWidget;

///Has access to item and original widget
struct QwtPlotItem
{
  QwtPlotItem(
    QwtPlotWidget * const widget,
    QGraphicsProxyWidget * const proxy);

  QGraphicsProxyWidget * const m_proxy;
  QwtPlotWidget * const m_widget;
};


#endif // QWTPLOTITEM_H
