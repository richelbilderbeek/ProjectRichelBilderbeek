//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
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
