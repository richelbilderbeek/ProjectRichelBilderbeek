#include "popup.h"

#include <cassert>
#include <QMessageBox>
#include <QTimer>

PopUp::PopUp()
  :
    m_signal_clicked{},
    m_fademode{FadeMode::in},
    m_node{nullptr},
    m_transparancy{128}
{
  setZValue(10);
}

void PopUp::mousePressEvent(QGraphicsSceneMouseEvent *) noexcept
{
  m_signal_clicked(this);
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
