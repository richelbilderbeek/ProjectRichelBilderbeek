#include "popup.h"

PopUp::PopUp()
  :
    m_signal_clicked{}
{
  this->setFlags(0);
}

void PopUp::mousePressEvent(QGraphicsSceneMouseEvent *) noexcept
{
  m_signal_clicked(this);
}
