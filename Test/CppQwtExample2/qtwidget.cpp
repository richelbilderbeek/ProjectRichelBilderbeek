#include "qtwidget.h"

#include <cassert>
#include <iostream>

#include <boost/lambda/lambda.hpp>

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

#include "qwtplotitem.h"
#include "qttextitem.h"
#include "qwtplotwidget.h"

QtWidget::QtWidget(QGraphicsScene* scene, QWidget* parent)
  : QGraphicsView(scene,parent), m_item(0)
{
  this->setScene(new QGraphicsScene);
  {
    QwtPlotWidget * const widget = new QwtPlotWidget(100);
    QGraphicsProxyWidget * const proxy = this->scene()->addWidget(widget,Qt::Dialog);
    m_item = new QwtPlotItem(widget,proxy);
  }
  m_item->m_proxy->setGeometry(QRectF(-200.0,-200.0,400.0,400.0));
  m_item->m_widget->AddY(1.0);
  {
    QtTextItem * const item = new QtTextItem("MOVE ME");
    item->m_signal_value.connect(boost::bind(&QtWidget::ReceiveValue,this,boost::lambda::_1));
    this->scene()->addItem(item);
    item->setPos(300.0,0.0);
  }
}

void QtWidget::ReceiveValue(const double value)
{
  this->m_item->m_widget->AddY(value);
}
