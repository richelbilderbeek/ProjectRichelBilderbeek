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
#ifndef QTCONCEPTMAPCONCEPTMAPITEM_H
#define QTCONCEPTMAPCONCEPTMAPITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include "qtconceptmapfwd.h"
#include "qtroundededitrectitem.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///A focusable element of a concept map, which is either a Node or an Edge
///QtRoundedTextRectItem: single line
///QtRoundedEditRectItem: multiple lines
struct QtConceptMapElement : public QtRoundedEditRectItem
{
  QtConceptMapElement();
  virtual ~QtConceptMapElement() noexcept {}

  //virtual void DisableAll() = 0;
  //virtual void EnableAll() = 0;

  ///Obtain the Concept from either a Node or an Edge
  //virtual boost::shared_ptr<const Node>  GetNode() const noexcept = 0;
  //virtual boost::shared_ptr<      Node>  GetNode()       noexcept = 0;

  //virtual boost::shared_ptr<const QtItemDisplayStrategy> GetDisplayStrategy() const noexcept = 0;
  //virtual boost::shared_ptr<      QtItemDisplayStrategy> GetDisplayStrategy()       noexcept = 0;

  ///Set the name of the concept
  //virtual void SetName(const std::string& name) noexcept = 0;

  ///Set the position
  //void SetPos(const double x, const double y) noexcept { SetX(x); SetY(y); }

  ///Set the X coordinat
  //virtual void SetX(const double x) noexcept = 0;

  ///Set the Y coordinat
  //virtual void SetY(const double y) noexcept = 0;

  ///A more specific signal: a Concept requests an edit, this is passed to
  ///OnConceptRequestsEdit, which lets this QtConceptMapItem request for an edit
  //boost::signals2::signal<void(QtConceptMapElement*)> m_signal_conceptmapitem_requests_edit;

  ///Slot for a Concept its signal to be edited, all it does is add the ConceptMapItem
  ///the Concept is a member of
  //void OnConceptRequestsEdit();

  protected:
  ///Remove this member function, let the client call the virual SetX and SetY member functions
  //void setPos(const QPointF &pos) { QtRoundedEditRectItem::setPos(pos); }
  ///Remove this member function, let the client call the virual SetX and SetY member functions
  //void setPos(qreal x, qreal y) { QtRoundedEditRectItem::setPos(x,y); }

  void hoverMoveEvent(QGraphicsSceneHoverEvent *) noexcept override final;
  void hoverEnterEvent(QGraphicsSceneHoverEvent *) noexcept override final;


  private:
  //virtual void SetNode(const boost::shared_ptr<Node>& node) = 0;

};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTMAPITEM_H
