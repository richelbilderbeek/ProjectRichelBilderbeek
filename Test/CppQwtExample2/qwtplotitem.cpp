#include "qwtplotitem.h"

QwtPlotItem::QwtPlotItem(
  QwtPlotWidget * const widget,
  QGraphicsProxyWidget * const proxy)
  : m_proxy(proxy), m_widget(widget)
{

}
