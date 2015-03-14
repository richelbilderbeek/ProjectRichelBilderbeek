#include "popup.h"

#include <cassert>
#include <QMessageBox>
#include <QTimer>

PopUp::PopUp()
  :
    m_signal_clicked{},
    m_fademode{FadeMode::in},
    m_node{nullptr},
    m_timer{new QTimer},
    m_transparancy{128}
{
  setZValue(10);
  //QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(OnTimer())); //Only works on QObjects
}

void PopUp::mousePressEvent(QGraphicsSceneMouseEvent *) noexcept
{
  m_signal_clicked(this);
}

void PopUp::OnTimer()
{

}

void PopUp::SetNode(Node * const node)
{
  assert(node);
  m_node = node;
}

void PopUp::StartFadeIn()
{
  setVisible(true);
}

void PopUp::StartFadeOut()
{

}
