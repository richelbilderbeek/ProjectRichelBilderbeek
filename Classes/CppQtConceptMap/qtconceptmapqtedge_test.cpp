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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapqtedge.h"

#include <cassert>

#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "counter.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapqtedgefactory.h"
#include "qtquadbezierarrowitem.h"
#include "qtroundededitrectitem.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::QtEdge::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    NodeFactory();
    QtRoundedEditRectItem();
    QtRoundedEditRectItem a;
    QtRoundedEditRectItem b;
    QtQuadBezierArrowItem(&a,false,nullptr,true,&b);
    const boost::shared_ptr<Node> node_from{NodeFactory().GetTest(0)};
    const boost::shared_ptr<Node> node_to{NodeFactory().GetTest(0)};
    const boost::shared_ptr<QtNode> qtnode_from{new QtNode(node_from)};
    const boost::shared_ptr<QtNode> qtnode_to{new QtNode(node_to)};
    const boost::shared_ptr<Edge> edge{EdgeFactory().GetTest(0,node_from,node_to)};
    //const boost::shared_ptr<QtEdge> qtedge{QtEdgeFactory().Create(edge,qtnode_from.get(),qtnode_to.get())};
    const boost::shared_ptr<QtEdge> qtedge{QtEdgeFactory().Create(edge,qtnode_from,qtnode_to)};
  }

  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  const int node_test_index{0};
  const int edge_test_index{0};
  const boost::shared_ptr<Node> node_from{NodeFactory().GetTest(node_test_index)};
  const boost::shared_ptr<Node> node_to{NodeFactory().GetTest(node_test_index)};
  const boost::shared_ptr<QtNode> qtnode_from{new QtNode(node_from)};
  const boost::shared_ptr<QtNode> qtnode_to{new QtNode(node_to)};
  const boost::shared_ptr<Edge> edge{EdgeFactory().GetTest(edge_test_index,node_from,node_to)};
  const boost::shared_ptr<QtEdge> qtedge{new QtEdge(edge,qtnode_from,qtnode_to)};
  //const boost::shared_ptr<QtEdge> qtedge{new QtEdge(edge,qtnode_from.get(),qtnode_to.get())};
  const boost::shared_ptr<QtRoundedEditRectItem> qtitem{boost::dynamic_pointer_cast<QtRoundedEditRectItem>(qtedge->GetQtNode())};
  assert(qtitem);
  //Head arrow
  if (verbose) { TRACE("An Edge's head arrow and it QtQuadBezierArrowItem must match at creation"); }
  {
    const bool edge_has_head{qtedge->GetEdge()->HasHeadArrow()};
    const bool arrow_has_head{qtedge->GetArrow()->HasHead()};
    assert(edge_has_head == arrow_has_head);
  }
  if (verbose) { TRACE("If a QtEdge its Edge's head arrow is changed, a signal must be emitted by Edge"); }
  {
    Counter c{0}; //For receiving the signal
    qtedge->GetEdge()->m_signal_head_arrow_changed.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );
    qtedge->GetEdge()->SetHeadArrow(true);
    qtedge->GetEdge()->SetHeadArrow(false);
    assert(c.Get() > 0);
  }
  if (verbose) { TRACE("If a QtEdge its Edge's head arrow is changed, a signal must be emitted by QtEdge"); }
  {
    Counter c{0}; //For receiving the signal
    qtedge->m_signal_edge_changed.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );
    qtedge->GetEdge()->SetHeadArrow(false);
    qtedge->GetEdge()->SetHeadArrow(true);
    assert(c.Get() > 0);
  }
  if (verbose) { TRACE("If a QtEdge its Edge's head arrow is changed, it QtQuadBezier must match"); }
  {
    qtedge->GetEdge()->SetHeadArrow(false);
    assert(!qtedge->GetArrow()->HasHead());
    qtedge->GetEdge()->SetHeadArrow(true);
    assert(qtedge->GetArrow()->HasHead());
  }

  //Tail arrow
  if (verbose) { TRACE("An Edge's tail arrow and it QtQuadBezierArrowItem must match at creation"); }
  {
    const bool edge_has_tail{qtedge->GetEdge()->HasTailArrow()};
    const bool arrow_has_tail{qtedge->GetArrow()->HasTail()};
    assert(edge_has_tail == arrow_has_tail);
  }

  //Text
  if (verbose) { TRACE("Text of QtEdge must be one line"); }
  {
    assert(qtitem->GetText().size() == 1);
  }
  if (verbose) { TRACE("Text of QtEdge and QtRoundedEditRectItem must match at creation"); }
  {
    const std::string qtitem_name{qtitem->GetText()[0]};
    const std::string qtedge_name{qtedge->GetEdge()->GetNode()->GetConcept()->GetName()};
    assert(qtitem_name == qtedge_name);
  }
  if (verbose) { TRACE("If a QtEdge its text is changed, a signal must be emitted"); }
  {
    qtedge->GetEdge()->GetNode()->GetConcept()->SetName("A");
    Counter c{0}; //For receiving the signal
    qtedge->m_signal_edge_changed.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );
    qtedge->GetEdge()->GetNode()->GetConcept()->SetName("B");
    assert(c.Get()>0);
  }
  if (verbose) { TRACE("If text is set via QtEdge, QtRoundedEditRectItem must sync"); }
  {
    qtedge->GetEdge()->GetNode()->GetConcept()->SetName("A");
    assert(qtitem->GetText()[0] == "A");
    qtedge->GetEdge()->GetNode()->GetConcept()->SetName("B");
    assert(qtitem->GetText()[0] == "B");
  }
  if (verbose) { TRACE("If text is set via QtRoundedEditRectItem, QtEdge must sync"); }
  {
    qtitem->SetText( { "A" } );
    assert(qtedge->GetEdge()->GetNode()->GetConcept()->GetName() == "A");
    qtitem->SetText( { "B" } );
    assert(qtedge->GetEdge()->GetNode()->GetConcept()->GetName() == "B");
  }

  //X
  if (verbose) { TRACE("X of QtEdge and QtRoundedEditRectItem must match at creation"); }
  {
    const double edge_x{edge->GetNode()->GetX()};
    const double qtedge_x{qtitem->GetOuterX()};
    assert(edge_x == qtedge_x);
  }
  if (verbose) { TRACE("If X is set via QtEdge, QtRoundedEditRectItem must sync"); }
  {
    const double old_x{qtedge->m_qtnode->GetOuterX()};
    const double new_x{old_x + 10.0};
    qtedge->m_qtnode->SetOuterX(new_x);
    assert(std::abs(qtitem->GetOuterX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("If X is set via QtRoundedEditRectItem, QtEdge must sync"); }
  {
    const double old_x{qtitem->GetOuterX()};
    const double new_x{old_x + 10.0};
    qtitem->SetOuterX(new_x);
    assert(std::abs(qtedge->m_qtnode->GetOuterX() - new_x) < 2.0);
  }
  //Y
  if (verbose) { TRACE("Y of QtEdge and QtRoundedEditRectItem must match at creation"); }
  {
    const double edge_y{edge->GetNode()->GetY()};
    const double qtedge_y{qtitem->GetOuterY()};
    assert(edge_y == qtedge_y);
  }
  if (verbose) { TRACE("If Y is set via QtEdge, QtRoundedEditRectItem must sync"); }
  {
    const double old_y{qtedge->m_qtnode->GetOuterY()};
    const double new_y{old_y + 10.0};
    qtedge->m_qtnode->SetOuterY(new_y);
    assert(std::abs(qtitem->GetOuterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("If Y is set via QtRoundedEditRectItem, QtEdge must sync"); }
  {
    const double old_y{qtitem->GetOuterY()};
    const double new_y{old_y + 10.0};
    qtitem->SetOuterY(new_y);
    assert(std::abs(qtedge->m_qtnode->GetOuterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("QtEdge must accept hover events"); }
  {
    assert(qtedge->acceptHoverEvents()); //Must remove the 's' in Qt5?
  }
  if (verbose) { TRACE("QtEdge its arrow must accept hover events"); }
  {
    assert(qtedge->GetArrow()->acceptHoverEvents()); //Must remove the 's' in Qt5?
  }
}
#endif

