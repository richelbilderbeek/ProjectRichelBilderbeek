#ifndef QTHIGHLIGHTER_H
#define QTHIGHLIGHTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QObject>
#include <QTimer>

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace cmap {

class QtConceptMapItemHighlighter : public QObject
{
  Q_OBJECT

public:
  QtConceptMapItemHighlighter(QObject *parent = 0);
  QtConceptMapItemHighlighter(const QtConceptMapItemHighlighter&) = delete;
  QtConceptMapItemHighlighter& operator=(const QtConceptMapItemHighlighter&) = delete;

  ///Get the item being highlighted
  ///Returns nullptr if no item is highlighted
        QtConceptMapNodeItem* GetItem()       noexcept { return m_item; }
  const QtConceptMapNodeItem* GetItem() const noexcept { return m_item; }

  ///Set the item to highlight.
  ///If set with a nullptr, highlighting the current item stops
  ///If set with the same item twice, nothing new happens
  void SetItem(QtConceptMapNodeItem* const item);


private:
  ///A simple counter
  int m_cnt;

  ///The item being highlighted
  QtConceptMapNodeItem* m_item;

  ///The timer used for highlighting every 100 ms
  QTimer * const m_timer;

private slots:
  void OnTimer();
};

} //~namespace cmap

} //~namespace ribi

#endif // QTHIGHLIGHTER_H
