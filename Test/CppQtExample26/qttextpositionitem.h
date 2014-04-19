#ifndef QTTEXTPOSITIONITEM_H
#define QTTEXTPOSITIONITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsItem>
#pragma GCC diagnostic pop

struct QtTextPositionItem : public QGraphicsItem
{
  ///Constructor of QtTextPositionItem
  QtTextPositionItem(
    const std::string& text,
    QGraphicsItem *parent = 0
  );
  QtTextPositionItem(const QtTextPositionItem&) = delete;
  QtTextPositionItem& operator=(const QtTextPositionItem&) = delete;
  ~QtTextPositionItem() noexcept {}

  protected:
  ///Paint a QtTextPositionItem
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

  ///The rectangle that determines the edges of the QtTextPositionItem
  QRectF boundingRect() const;

  ///The text to display
  const std::string m_text;
  ///The rectangle the text is in
  const QRectF m_rect;
};

#endif // QTTEXTPOSITIONITEM_H
