#ifndef QTHIGHLIGHTER_H
#define QTHIGHLIGHTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QObject>
#pragma GCC diagnostic pop

struct QGraphicsItem;
struct QTimer;

class QtHighlighter : public QObject
{
  Q_OBJECT

public:
  QtHighlighter(QObject *parent = 0);

  ///Set the item to highlight.
  ///If set with a nullptr, highlighting the current item stops
  ///If set with the same item twice, nothing new happens
  void SetItem(QGraphicsItem * const item);


private:
  ///The item being highlighted
  QGraphicsItem * m_item;

  ///The timer used for highlighting every 100 ms
  QTimer * const m_timer;


private slots:
  void OnTimer();
};

#endif // QTHIGHLIGHTER_H
