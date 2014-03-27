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
#ifndef QTCONCEPTMAPTOOLSITEM_H
#define QTCONCEPTMAPTOOLSITEM_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QBrush>
#include <QGraphicsPixmapItem>

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "conceptmapnode.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Tools item is a class that is displayed above a selected node or edge
///and displays clickable icons to perform actions, for example
///adding a relation or modifying arrow edges
///QtTool cannot have its visibility set directly:
///- if it has a buddy, it is visible
///- if it has no buddy, it is invisible
struct QtTool : public QGraphicsPixmapItem
{
  explicit QtTool();
  QtTool(const QtTool& other) = delete;
  QtTool& operator=(const QtTool& other) = delete;
  virtual ~QtTool() {}

  ///Get the item the tools item floats above
  ///Return type cannot be const, as the user might want to modify it
  const QtNode * GetBuddyItem() const;
        QtNode * GetBuddyItem();

  ///Set the position from the widget it floats above
  ///item cannot be const, as the user might want to modify it
  void SetBuddyItem(const QtNode * const item);

  ///Signalled when a tool is clicked
  boost::signals2::signal<void ()> m_signal_clicked;

  protected:
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *);

  private:
  ///Make private to ensure use of other setPos member function
  void setPos(qreal ax, qreal ay) { QGraphicsPixmapItem::setPos(ax,ay); }

  ///The item the tools item floats above
  ///m_item cannot be const, as the user might want to modify it
  const QtNode * m_item;

  void setVisible(bool visible) { QGraphicsPixmapItem::setVisible(visible); }
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTOOLSITEM_H
