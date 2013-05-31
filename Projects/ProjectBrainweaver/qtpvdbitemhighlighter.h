#ifndef QTHIGHLIGHTER_H
#define QTHIGHLIGHTER_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QObject>
#include <QTimer>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "qtpvdbconceptitem.h"
#include <QTimer>
#endif


class QtPvdbItemHighlighter : public QObject
{
  Q_OBJECT

public:
  QtPvdbItemHighlighter(QObject *parent = 0);

  ///Get the item being highlighted
  ///Returns nullptr if no item is highlighted
        QtPvdbNodeItem* GetItem()       { return m_item; }
  const QtPvdbNodeItem* GetItem() const { return m_item; }

  ///Set the item to highlight.
  ///If set with a nullptr, highlighting the current item stops
  ///If set with the same item twice, nothing new happens
  void SetItem(QtPvdbNodeItem* const item);


private:
  ///A simple counter
  int m_cnt;

  ///The item being highlighted
  QtPvdbNodeItem* m_item;

  ///The timer used for highlighting every 100 ms
  QTimer * const m_timer;

private slots:
  void OnTimer();
};

#endif // QTHIGHLIGHTER_H
