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
#ifndef QTCONCEPTMAPNODEITEM_H
#define QTCONCEPTMAPNODEITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtroundedtextrectitem.h"
#include "qtconceptmapelement.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace cmap {

///QtNode displays a Node as a QtConceptMapElement
struct QtNode : public QtConceptMapElement
{
  typedef QtConceptMapElement Base;
  virtual ~QtNode() noexcept;

  ///Node cannot be const as it contains a Concept that the user might want to edit
  ///concept_item contains the Stategy to display (and respond to the concept)
  explicit QtNode(
    const boost::shared_ptr<Node> node,
    const boost::shared_ptr<QtItemDisplayStrategy> concept_item);

  //virtual QRectF boundingRect() const;

  //QBrush brush() const;

  void DisableAll();
  void EnableAll();

  boost::shared_ptr<const Node>  GetNode() const noexcept;
  boost::shared_ptr<      Node>  GetNode()       noexcept;

  boost::shared_ptr<const QtItemDisplayStrategy> GetDisplayStrategy() const noexcept final { return m_display_strategy; }
  boost::shared_ptr<      QtItemDisplayStrategy> GetDisplayStrategy()       noexcept final { return m_display_strategy; }

  //      boost::shared_ptr<const cmap::Node>  GetNode() const noexcept { return m_node; }
  //const boost::shared_ptr<      cmap::Node>& GetNode()       noexcept { return m_node; }

  void SetNode(const boost::shared_ptr<Node>& node);
  void SetDisplay(const boost::shared_ptr<QtItemDisplayStrategy>& display_strategy);

  //void SetName(const std::string& name) noexcept;

  ///Set the X coordinat of the central concept
  //void SetX(const double x) noexcept;

  ///Set the Y coordinat of the central concept
  //void SetY(const double y) noexcept;

  ///m_signal_request_rate_node is emitted due to a m_signal_request_rate_node
  ///of the Node its QtRateConceptItem
  boost::signals2::signal<void (QtNode *)> m_signal_node_requests_rate_concept;
  boost::signals2::signal<void (QtNode *)> m_signal_node_requests_rate_examples;

  ///No other signals, these are present in the ConceptItems

protected:

  void focusInEvent(QFocusEvent *event) final;
  void focusOutEvent(QFocusEvent *event) final;
  void keyPressEvent(QKeyEvent *event) final;

  //const boost::shared_ptr<QtConceptMapItem>& GetConceptItem() { return m_concept_item; }

  ///Next to QtConceptMapConcept::paint, check for collision
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) final;


private:

  ///The Strategy for displaying a Concept
  boost::shared_ptr<QtItemDisplayStrategy> m_display_strategy;

  //const QPen m_contour_pen;
  //const QPen m_focus_pen;

  ///The node being edited, or displayed and not changed, or rated
  boost::shared_ptr<Node> m_node;

  void OnItemHasUpdated();

  ///The m_node has changed
  //void OnXchanged(Node * const node);
  //void OnYchanged(Node * const node);

  ///This QtNode its Node changed
  void OnNodeChanged(Node * const node);
  void OnRequestsSceneUpdate();

  ///The item
  void OnItemRequestsRateConcept();
  void OnItemRequestsRateExamples();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPNODEITEM_H
