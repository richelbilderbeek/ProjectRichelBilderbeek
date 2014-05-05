#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsItem>
#include <QTimer>
#include "qthighlighter.h"
#pragma GCC diagnostic pop

QtHighlighter::QtHighlighter(QObject *parent)
  : QObject(parent),
    m_item(nullptr),
    m_timer(new QTimer(this))
{
  m_timer->setInterval(10); //ms
  QObject::connect(
    m_timer,SIGNAL(timeout()),
    this,SLOT(OnTimer()));
}

void QtHighlighter::SetItem(QGraphicsItem * const item)
{
  m_item = item;
  if (m_item)
  {
    this->m_timer->start();
  }
  else
  {
    this->m_timer->stop();
  }
}


void QtHighlighter::OnTimer()
{
  if (m_item)
  {
    m_item->setRotation(m_item->rotation() + 5.0);
  }
}
