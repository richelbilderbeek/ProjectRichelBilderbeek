#ifndef POPUP_H
#define POPUP_H

#include <boost/signals2.hpp>
#include <QGraphicsPixmapItem>

struct Node;
struct QTimer;

class PopUp : public QGraphicsPixmapItem
{
public:
  PopUp();
  PopUp(const PopUp&) = delete;
  PopUp& operator=(const PopUp&) = delete;
  boost::signals2::signal<void(PopUp * const)> m_signal_clicked;
  void SetNode(Node * const node);
  Node * GetNode() const noexcept { return m_node; }
  void StartFadeIn();
  void StartFadeOut();
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept;
private:
  enum class FadeMode { in, out } m_fademode;
  Node * m_node; //The Node the PopUp belongs to
  int m_transparancy; //Alpha value, 255: opaque
};

#endif // POPUP_H
