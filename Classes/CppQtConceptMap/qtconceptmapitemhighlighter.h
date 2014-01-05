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

class QtItemHighlighter : public QObject
{
  Q_OBJECT

public:
  QtItemHighlighter(QObject *parent = 0);
  QtItemHighlighter(const QtItemHighlighter&) = delete;
  QtItemHighlighter& operator=(const QtItemHighlighter&) = delete;

  ///Get the item being highlighted
  ///Returns nullptr if no item is highlighted
        QtNode* GetItem()       noexcept { return m_item; }
  const QtNode* GetItem() const noexcept { return m_item; }

  ///Set the item to highlight.
  ///If set with a nullptr, highlighting the current item stops
  ///If set with the same item twice, nothing new happens
  void SetItem(QtNode* const item);

private:
  ///A simple counter
  int m_cnt;

  ///The item being highlighted
  QtNode* m_item;

  ///The timer used for highlighting every 100 ms
  QTimer * const m_timer;

private slots:
  void OnTimer();
};

} //~namespace cmap

} //~namespace ribi

#endif // QTHIGHLIGHTER_H
