#include "qtwidget.h"

#include <cassert>
#include <cmath>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/math/constants/constants.hpp>

#include <QGraphicsScene>
#include <QTimer>
#include "qttextitem.h"
#include "text.h"
#pragma GCC diagnostic pop

QtWidget::QtWidget(QWidget *parent)
  : QGraphicsView(new QGraphicsScene,parent),
    m_texts{}
{
  const int n_items = 16;
  //Create the Texts
  for (int i=0; i!=n_items; ++i)
  {
    boost::shared_ptr<Text> text(new Text("*"));
    m_texts.push_back(text);
  }
  //Create the QtTextItems
  for (int i=0; i!=n_items; ++i)
  {

    const double angle
      = boost::math::constants::two_pi<double>()
      * (static_cast<double>(i+0) / static_cast<double>(n_items));
    const double ray = 150.0;
    const double x =  std::sin(angle) * ray;
    const double y = -std::cos(angle) * ray;

    QtTextItem * const item = new QtTextItem(m_texts.at(i));
    item->setPos(x,y);
    scene()->addItem(item);
  }
  //Create and start a timer
  {
    QTimer * const timer(new QTimer(this));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(100);
    timer->start();
  }
}

void QtWidget::OnTimer()
{
  const boost::shared_ptr<Text>& text = m_texts[ std::rand() % m_texts.size() ];
  text->SetText(text->GetText() + "*");
}
