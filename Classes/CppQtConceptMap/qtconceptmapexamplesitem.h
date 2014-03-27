//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
#ifndef QTCONCEPTMAPEXAMPLESITEM_H
#define QTCONCEPTMAPEXAMPLESITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "qtroundededitrectitem.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct QtExamplesItem : public QtRoundedEditRectItem
{
  QtExamplesItem(QGraphicsItem* parent = 0);
  QtExamplesItem(const QtExamplesItem&) = delete;
  QtExamplesItem& operator=(const QtExamplesItem&) = delete;
  ~QtExamplesItem() noexcept {}
  ///Check the buddy item
  const QtConceptMapElement* GetBuddyItem() const noexcept { return m_item; }

  ///Set the concept this item displays the examples of.
  ///If the concept is nullptr, this item hides
  void SetBuddyItem(const QtConceptMapElement* const item);

  ///Request update of QGraphicsScene, because this item has changed
  mutable boost::signals2::signal<void() > m_signal_request_scene_update;

protected:

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

  ///The concept this item displays the examples of.
  ///If m_concept is nullptr, this item hides
  const QtConceptMapElement* m_item;

  ///Item has updated, Examples must follow
  void OnItemUpdated();

  void SetExamples(const boost::shared_ptr<const cmap::Examples>& examples);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPEXAMPLESITEM_H
