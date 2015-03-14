#ifndef POPUP_H
#define POPUP_H

#include <boost/signals2.hpp>
#include <QGraphicsRectItem>

class PopUp : public QGraphicsRectItem
{
public:
  PopUp();
  PopUp(const PopUp&) = delete;
  PopUp& operator=(const PopUp&) = delete;
  boost::signals2::signal<void(PopUp * const)> m_signal_clicked;
  //Node * GetNode() const noexcept;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept;
};

#endif // POPUP_H
