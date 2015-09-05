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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmap.h"

#include <chrono>

#include <QApplication>
#include <QMouseEvent>

#include "qtconceptmapcollect.h"
#include "conceptmapfactory.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeletenode.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

QKeyEvent CreateDel() { return QKeyEvent(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier); }
QKeyEvent CreateSpace() { return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier); }
QKeyEvent CreateControlDown() { return QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::ControlModifier); }
QKeyEvent CreateControlE() { return QKeyEvent(QEvent::KeyPress,Qt::Key_E,Qt::ControlModifier); }
QKeyEvent CreateControlN() { return QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::ControlModifier); }

#ifndef NDEBUG
void ribi::cmap::QtConceptMap::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer{__func__,__FILE__,1.0};
  TestTimer::SetMaxCnt(2); //Because the base class (QtKeyboardFriendlyGraphicsView)
                           //has to be tested as well
  const bool verbose{false};

  if (verbose) { TRACE("SetConceptMap and GetConceptMap return the same"); }
  {
    QtConceptMap m;
    const boost::shared_ptr<ConceptMap> conceptmap{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(2)
    };
    m.SetConceptMap(conceptmap);
    assert(m.GetConceptMap() == conceptmap);
  }
  if (verbose) { TRACE("SetConceptMap, two nodes"); }
  {
    QtConceptMap m;
    const boost::shared_ptr<ConceptMap> conceptmap{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(2)
    };
    m.SetConceptMap(conceptmap);
    const auto nodes = conceptmap->GetNodes();
    const auto items = Collect<QtNode>(m.GetScene());
    const std::size_t n_items = items.size();
    const std::size_t n_nodes = nodes.size();
    assert(n_items == n_nodes && "GUI and non-GUI concept map must match");
  }
  if (verbose) { TRACE("SetConceptMap, 3 nodes, 1 edge"); }
  {
    QtConceptMap m;
    const boost::shared_ptr<ConceptMap> conceptmap{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(3)
    };
    m.SetConceptMap(conceptmap);
    const auto nodes_in_conceptmap = conceptmap->GetNodes();
    const auto edges_in_conceptmap = conceptmap->GetEdges();
    const auto nodes_in_scene = Collect<QtNode>(m.GetScene());
    const auto edges_in_scene = Collect<QtEdge>(m.GetScene());
    const std::size_t n_nodes_in_scene = nodes_in_scene.size();
    const std::size_t n_edges_in_scene = edges_in_scene.size();
    const std::size_t n_nodes_in_conceptmap = nodes_in_conceptmap.size();
    const std::size_t n_edges_in_conceptmap = edges_in_conceptmap.size();
    assert(n_nodes_in_scene == n_nodes_in_conceptmap && "GUI and non-GUI concept map must match");
    assert(n_edges_in_scene == n_edges_in_conceptmap && "GUI and non-GUI concept map must match");
  }
  if (verbose) { TRACE("Test base class (after having tested cloning of derived class)"); }
  {
    const boost::shared_ptr<ConceptMap> conceptmap
      = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(15);
    assert(conceptmap);
    assert(conceptmap->IsValid());

    boost::shared_ptr<QtConceptMap> widget(new QtConceptMap);
    widget->SetConceptMap(conceptmap);
    assert(widget);
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding in both places"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto node = NodeFactory().GetTest(0);
    conceptmap->AddNode(node);
    qtconceptmap->AddNode(node);

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding in both places"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node); //First Qt
    //conceptmap->AddNode(node); //Allowed, results in a warning

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding it to QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding it to ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    const auto node = NodeFactory().GetTest(0);
    conceptmap->AddNode(node);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding it to ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    const auto command = new CommandCreateNewNode(conceptmap);
    qtconceptmap->DoCommand(command);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
  }
  if (verbose) { TRACE("AddNode: a Node added gets a QtNode to be found in QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node);
    assert(qtconceptmap->GetQtNode(node.get()));
  }
  if (verbose) { TRACE("AddNode: added QtNode must get selected"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetSelectedNodes().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());

    const auto node = NodeFactory().GetTest(0);
    const auto qtnode = qtconceptmap->AddNode(node);

    assert(qtnode->isSelected());
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
  }
  if (verbose) { TRACE("AddNode: adding two QtNode must select both"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node1 = NodeFactory().GetTest(0);
    const auto node2 = NodeFactory().GetTest(0);

    assert(conceptmap->GetSelectedNodes().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());

    const auto qtnode1 = qtconceptmap->AddNode(node1);

    assert(qtnode1->isSelected());
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());

    const auto qtnode2 = qtconceptmap->AddNode(node2);

    assert(qtnode1->isSelected());
    assert(qtnode2->isSelected());
    assert(conceptmap->GetSelectedNodes().size() == 2);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
  }
  if (verbose) { TRACE("DeleteNode: create two Nodes, delete one Node from QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    qtconceptmap->AddNode(NodeFactory().GetTest(0));

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    qtconceptmap->AddNode(NodeFactory().GetTest(0));

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    qtconceptmap->DeleteQtNode( qtconceptmap->GetQtNodes().back());

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
  }
  if (verbose) { TRACE("DeleteNode: create two Nodes, delete one Node from ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    qtconceptmap->AddNode(NodeFactory().GetTest(0));
    qtconceptmap->AddNode(NodeFactory().GetTest(0));

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    conceptmap->DeleteNode( conceptmap->GetNodes().back());

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
  }
  if (verbose) { TRACE("DeleteNode: delete a Node from ConceptMap using a Command"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node1 = NodeFactory().GetTest(0);
    const auto node2 = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,node1,node2);

    qtconceptmap->AddNode(node1);
    qtconceptmap->AddNode(node2);
    qtconceptmap->AddEdge(edge);

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());

    const auto command = new CommandDeleteNode(conceptmap,node1);
    qtconceptmap->DoCommand(command);


    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    assert(conceptmap->GetNodes().size() == 1);
    assert(qtconceptmap->GetQtEdges().size() == 0);
  }
  if (verbose) { TRACE("DeleteNode: create two Nodes and Edge, delete one Node from ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node1 = NodeFactory().GetTest(0);
    const auto node2 = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,node1,node2);

    const auto qtnode1 = qtconceptmap->AddNode(node1);
    const auto qtnode2 = qtconceptmap->AddNode(node2);
    const auto qtedge = qtconceptmap->AddEdge(edge);

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    assert(conceptmap->GetNodes().size() == 2);
    assert(qtconceptmap->GetQtEdges().size() == 1);

    qtconceptmap->DeleteNode(node1);

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    assert(conceptmap->GetNodes().size() == 1);
    assert(qtconceptmap->GetQtEdges().size() == 0);
    assert(!qtnode1->scene());
    assert( qtnode2->scene()); //node2 is left over
    assert(!qtedge->scene());

  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    qtconceptmap->AddEdge(edge);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    conceptmap->AddEdge(edge);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in both places, ConceptMap first"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    conceptmap->AddEdge(edge);
    qtconceptmap->AddEdge(edge);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in both places, QtConceptMap first"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    qtconceptmap->AddEdge(edge);
    //conceptmap->AddEdge(edge); //Correctly gives a warning

    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: added QtEdge must get selected"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(from);
    qtconceptmap->AddNode(to);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    const auto qtedge = qtconceptmap->AddEdge(edge);

    assert(conceptmap->GetSelectedEdges().size() == 1);
    assert(qtedge->isSelected() || qtedge->GetQtNode()->isSelected()); //Cannot choose which one is better
  }
  if (verbose) { TRACE("AddEdge: added QtEdge must unselect QtNodes"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    const auto qtfrom = qtconceptmap->AddNode(from);
    const auto qtto = qtconceptmap->AddNode(to);

    assert(qtfrom->isSelected());
    assert(qtto->isSelected());

    const auto qtedge = qtconceptmap->AddEdge(edge);

    assert(!qtfrom->isSelected());
    assert(!qtto->isSelected());
    assert(qtedge->isSelected());
    assert(conceptmap->GetSelectedNodes().size() == 0);
    assert(conceptmap->GetSelectedEdges().size() == 1);
  }
  if (verbose) { TRACE("AddEdge: QtEdge its QtNode must be in between the QtNodes"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto qtfrom = qtconceptmap->AddNode(from);
    const auto qtto = qtconceptmap->AddNode(to);

    const double x1{100.0};
    const double y1{200.0};
    const double x2{300.0};
    const double y2{400.0};
    const double x3{(x1+x2)/2.0};
    const double y3{(y1+y2)/2.0};
    qtfrom->GetNode()->SetX(x1);
    qtfrom->GetNode()->SetY(y1);
    qtto->GetNode()->SetX(x2);
    qtto->GetNode()->SetY(y2);

    const auto edge = EdgeFactory().Create(from,to);

    assert(std::abs(edge->GetNode()->GetX() - x3) < 1.0);
    assert(std::abs(edge->GetNode()->GetY() - y3) < 1.0);

    const auto qtedge = qtconceptmap->AddEdge(edge);

    assert(std::abs(qtedge->GetQtNode()->GetNode()->GetX() - x3) < 1.0);
    assert(std::abs(qtedge->GetQtNode()->GetNode()->GetY() - y3) < 1.0);
  }
  if (verbose) { TRACE("DeleteEdge: delete of QtEdge from QtConceptMap"); }
  {
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(10);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetEdges().size() == 2);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());

    const auto qtedge1 = qtconceptmap->GetQtEdges().back();
    qtconceptmap->DeleteQtEdge(qtedge1);

    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());

    const auto qtedge2 = qtconceptmap->GetQtEdges().back();
    qtconceptmap->DeleteQtEdge(qtedge2);

    assert(conceptmap->GetEdges().size() == 0);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
  }
  //Test Undo functionality of commands
  if (verbose) { TRACE("Undo CommandCreateNewNode"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto command = new CommandCreateNewNode(conceptmap);
    qtconceptmap->DoCommand(command);

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);

    command->undo();

    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    const int n_nodes_again{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_again == n_nodes_before);
  }
  //
  //
  //Selection by more direct/dirtier methods
  //
  //
  if (verbose) { TRACE("Seleting a QtNode also updates the ConceptMap::m_selected"); }
  if (!"I care")
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    auto qtnode = qtconceptmap->AddNode(NodeFactory().GetTest(0));

    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());

    qtnode->setSelected(false);

    assert(conceptmap->GetSelectedNodes().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());

    qtnode->setSelected(true);

    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());
  }

  //
  //
  //QWidget Events; direct GUI responses. Note: these are done by Commands anyways,
  //so it may be hard to create a test that breaks here)
  //
  if (verbose) { TRACE("CTRL-N creates a new QtNode"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N creates two QtNodes"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());

    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == 2);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());
  }
  if (verbose) { TRACE("CTRL-N, CTRL-Down: QtNode must move down"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    qtconceptmap->showFullScreen();
    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(qtconceptmap->GetQtNodes()[0]->x() == qtconceptmap->GetConceptMap()->GetNodes()[0]->GetX());
    assert(qtconceptmap->GetQtNodes()[0]->y() == qtconceptmap->GetConceptMap()->GetNodes()[0]->GetY());

    const double x_before{qtconceptmap->GetQtNodes()[0]->x()};
    const double y_before{qtconceptmap->GetQtNodes()[0]->y()};

    auto ctrl_down = CreateControlDown();
    qtconceptmap->keyPressEvent(&ctrl_down);

    const double x_after{qtconceptmap->GetQtNodes()[0]->x()};
    const double y_after{qtconceptmap->GetQtNodes()[0]->y()};
    assert(x_after == x_before);
    assert(y_after > y_before);
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, delete, creates two QtNodes and deletes two"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetSelectedNodes().size() == 2);
    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());

    auto del = CreateDel();
    qtconceptmap->keyPressEvent(&del);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetSelectedNodes().size() == 0);
    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, space, delete, creates two QtNodes, selects one and deletes one"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetSelectedNodes().size() == 2);
    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());

    auto space = CreateSpace();
    qtconceptmap->keyPressEvent(&space);

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());

    auto del = CreateDel();
    qtconceptmap->keyPressEvent(&del);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedEdges().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());

  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, CTRL-E: new Edge should be selected"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetNodes().size() == 0);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == 0);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    auto ctrl_e = CreateControlE();
    qtconceptmap->keyPressEvent(&ctrl_e);

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    assert(conceptmap->GetSelectedNodes().size() == 0);
    assert(conceptmap->GetSelectedNodes().size() == qtconceptmap->GetSelectedQtNodes().size());
    assert(conceptmap->GetSelectedEdges().size() == 1);
    assert(conceptmap->GetSelectedEdges().size() == qtconceptmap->GetSelectedQtEdges().size());
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, CTRL-E: new Edge its QtNode must be between the two QtNodes"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);


    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    const auto qtfrom = qtconceptmap->GetQtNodes()[0];
    const auto qtto = qtconceptmap->GetQtNodes()[1];

    const double x1{100.0};
    const double y1{200.0};
    const double x2{300.0};
    const double y2{400.0};
    const double x3{(x1+x2)/2.0};
    const double y3{(y1+y2)/2.0};
    qtfrom->GetNode()->SetPos(x1,y1);
    qtto->GetNode()->SetPos(x2,y2);

    auto ctrl_e = CreateControlE();
    qtconceptmap->keyPressEvent(&ctrl_e);

    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const auto qtedge = qtconceptmap->GetQtEdges()[0];

    assert(std::abs(qtedge->GetQtNode()->x() - x3) < 1.0);
    assert(std::abs(qtedge->GetQtNode()->y() - y3) < 1.0);
    assert(std::abs(qtedge->GetQtNode()->GetNode()->GetX() - x3) < 1.0);
    assert(std::abs(qtedge->GetQtNode()->GetNode()->GetY() - y3) < 1.0);
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, Down 10x, CTRL-E: new Edge its QtNode must be between the two QtNodes"); }
  if (!"Not sure of the usefulness of this test")
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    qtconceptmap->showFullScreen();
    auto ctrl_n = CreateControlN();

    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    const auto qtfrom = qtconceptmap->GetQtNodes()[0];
    const auto qtto = qtconceptmap->GetQtNodes()[1];

    for (int i=0; i!=100; ++i)
    {
      TRACE(qtfrom->GetNode()->GetY());
      TRACE(qtto->GetNode()->GetY());

      auto ctrl_down = CreateControlDown();
      qtconceptmap->keyPressEvent(&ctrl_down);
      //for (int j=0; j!=1000; ++j) { qApp->processEvents(); }
      //qtconceptmap->showFullScreen();
    }
    assert(qtfrom->GetNode()->GetY() > 100.0);
    assert(qtto->GetNode()->GetY() > 100.0);

    auto ctrl_e = CreateControlE();
    qtconceptmap->keyPressEvent(&ctrl_e);

    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    const auto qtedge = qtconceptmap->GetQtEdges()[0];

    assert(std::abs(qtedge->GetQtNode()->y() > 1000.0));
    assert(!"Green");
  }
  if (verbose) { TRACE("Delete Edge and Node-that-is-head-of-Edge: delete from QtConceptMap"); }
  {
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetEmptyConceptMap();
    qtconceptmap->SetConceptMap(conceptmap);

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(from);
    qtconceptmap->AddNode(to);
    qtconceptmap->AddEdge(EdgeFactory().GetTest(0,from,to));
    conceptmap->AddSelected( ConceptMap::Nodes( { from } ) );

    assert(conceptmap->GetNodes().size() == 2);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == 1);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedEdges().size() == 1);

    auto del = CreateDel();
    qtconceptmap->keyPressEvent(&del);

    assert(conceptmap->GetNodes().size() == 1);
    assert(conceptmap->GetNodes().size() == qtconceptmap->GetQtNodes().size());
    assert(conceptmap->GetEdges().size() == 0);
    assert(conceptmap->GetEdges().size() == qtconceptmap->GetQtEdges().size());
    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(conceptmap->GetSelectedEdges().size() == 0);
  }

  if (verbose) { TRACE("MouseDoubleClick"); }
  for (int i=0; i!=5; ++i)
  {
    QtConceptMap m;
    m.SetConceptMap(ConceptMapFactory().GetHeteromorphousTestConceptMap(16));
    QMouseEvent e(
      QEvent::Type::MouseButtonDblClick,
      QPointF( std::sin(static_cast<double>(i)), std::cos(static_cast<double>(i) ) ), //localPos,
      Qt::MouseButton::LeftButton,
      Qt::MouseButtons(),
      Qt::NoModifier
    );
    m.mouseDoubleClickEvent(&e);
    const int n_nodes_in_scene{static_cast<int>(Collect<QtNode>(m.GetScene()).size())};
    const int n_nodes_in_conceptmap{static_cast<int>(m.GetConceptMap()->GetNodes().size())};
    assert(n_nodes_in_scene == n_nodes_in_conceptmap);
  }
  TestTimer::SetMaxCnt(1); //Because the base class has been tested now
}
#endif
