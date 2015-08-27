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

#include <QMouseEvent>

#include "qtconceptmapcollect.h"
#include "conceptmapfactory.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommanddeletenode.h"
#include "conceptmap.h"
#include "conceptmapedgefactory.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

QKeyEvent CreateDel() { return QKeyEvent(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier); }
QKeyEvent CreateSpace() { return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier); }
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
    const boost::shared_ptr<ConceptMap> concept_map{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(2)
    };
    m.SetConceptMap(concept_map);
    assert(m.GetConceptMap() == concept_map);
  }
  if (verbose) { TRACE("SetConceptMap, two nodes"); }
  {
    QtConceptMap m;
    const boost::shared_ptr<ConceptMap> concept_map{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(2)
    };
    m.SetConceptMap(concept_map);
    const auto nodes = concept_map->GetNodes();
    const auto items = Collect<QtNode>(m.GetScene());
    const std::size_t n_items = items.size();
    const std::size_t n_nodes = nodes.size();
    assert(n_items == n_nodes && "GUI and non-GUI concept map must match");
  }
  if (verbose) { TRACE("SetConceptMap, 3 nodes, 1 edge"); }
  {
    QtConceptMap m;
    const boost::shared_ptr<ConceptMap> concept_map{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(3)
    };
    m.SetConceptMap(concept_map);
    const auto nodes_in_concept_map = concept_map->GetNodes();
    const auto edges_in_concept_map = concept_map->GetEdges();
    const auto nodes_in_scene = Collect<QtNode>(m.GetScene());
    const auto edges_in_scene = Collect<QtEdge>(m.GetScene());
    const std::size_t n_nodes_in_scene = nodes_in_scene.size();
    const std::size_t n_edges_in_scene = edges_in_scene.size();
    const std::size_t n_nodes_in_concept_map = nodes_in_concept_map.size();
    const std::size_t n_edges_in_concept_map = edges_in_concept_map.size();
    assert(n_nodes_in_scene == n_nodes_in_concept_map && "GUI and non-GUI concept map must match");
    assert(n_edges_in_scene == n_edges_in_concept_map && "GUI and non-GUI concept map must match");
  }
  if (verbose) { TRACE("Test base class (after having tested cloning of derived class)"); }
  {
    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(15);
    assert(concept_map);
    assert(concept_map->IsValid());

    boost::shared_ptr<QtConceptMap> widget(new QtConceptMap);
    widget->SetConceptMap(concept_map);
    assert(widget);
  }
  if (verbose) { TRACE("Deletion of nodes"); }
  {
    boost::shared_ptr<ConceptMap> concept_map = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    assert(concept_map);
    assert(concept_map->GetNodes().size() > 0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    assert(qtconceptmap);
    qtconceptmap->SetConceptMap(concept_map);

    assert(qtconceptmap->GetQtNodes().size() == concept_map->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    QtNode * const qtnode = qtconceptmap->GetQtNodes().back();
    assert(qtnode);

    qtconceptmap->DeleteQtNode(qtnode);

    assert(qtconceptmap->GetQtNodes().size() == concept_map->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before - 1 && "Node must really be gone");
  }
  if (verbose) { TRACE("Deletion of QtEdges from QtConceptMap"); }
  {
    boost::shared_ptr<QtConceptMap> qt_conceptmap(new QtConceptMap);
    assert(qt_conceptmap);
    boost::shared_ptr<ConceptMap> concept_map = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(10);
    assert(concept_map);

    qt_conceptmap->SetConceptMap(concept_map);

    assert(qt_conceptmap->GetQtEdges().size() == 2);
    assert(qt_conceptmap->GetQtEdges().size() == concept_map->GetEdges().size());

    QtEdge* const qtedge1 = qt_conceptmap->GetQtEdges().back();
    qt_conceptmap->DeleteQtEdge(qtedge1);

    assert(qt_conceptmap->GetQtEdges().size() == 1);
    assert(qt_conceptmap->GetQtEdges().size() == concept_map->GetEdges().size());

    QtEdge* const qtedge2 = qt_conceptmap->GetQtEdges().back();
    qt_conceptmap->DeleteQtEdge(qtedge2);

    assert(qt_conceptmap->GetQtEdges().size() == 0);
    assert(qt_conceptmap->GetQtEdges().size() == concept_map->GetEdges().size());
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding in both places"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto node = NodeFactory().GetTest(0);
    conceptmap->AddNode(node);
    qtconceptmap->AddNode(node);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding in both places"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node); //First Qt
    //conceptmap->AddNode(node); //Allowed, results in a warning

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding it to QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding it to ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto node = NodeFactory().GetTest(0);
    conceptmap->AddNode(node);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding it to ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const boost::shared_ptr<CommandCreateNewNode> command {
      new CommandCreateNewNode
    };
    assert(qtconceptmap->CanDoCommand(command));
    qtconceptmap->DoCommand(command);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  if (verbose) { TRACE("AddNode: a Node added gets a QtNode to be found in QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node);
    assert(qtconceptmap->GetQtNode(node.get()));
  }
  if (verbose) { TRACE("AddNode: added QtNode must get selected"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(conceptmap->GetSelectedNodes().size() == 0);

    const auto node = NodeFactory().GetTest(0);

    assert(qtconceptmap->AddNode(node)->isSelected());

    assert(conceptmap->GetSelectedNodes().size() == 1);
  }
  if (verbose) { TRACE("AddNode: adding two QtNode must select both"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node1 = NodeFactory().GetTest(0);
    const auto node2 = NodeFactory().GetTest(0);

    assert(conceptmap->GetSelectedNodes().size() == 0);

    const auto qtnode1 = qtconceptmap->AddNode(node1);

    assert(conceptmap->GetSelectedNodes().size() == 1);
    assert(qtnode1->isSelected());

    const auto qtnode2 = qtconceptmap->AddNode(node2);

    assert(conceptmap->GetSelectedNodes().size() == 2);
    assert(qtnode1->isSelected());
    assert(qtnode2->isSelected());
  }
  if (verbose) { TRACE("DeleteNode: create two Nodes, delete one Node from QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    qtconceptmap->AddNode(NodeFactory().GetTest(0));
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    qtconceptmap->AddNode(NodeFactory().GetTest(0));

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_items_before{static_cast<int>(conceptmap->GetNodes().size())};

    assert(!qtconceptmap->GetQtNodes().empty());
    qtconceptmap->DeleteQtNode( qtconceptmap->GetQtNodes().back());

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_items_after{static_cast<int>(conceptmap->GetNodes().size())};
    assert(n_items_before - n_items_after == 1);

  }
  if (verbose) { TRACE("DeleteNode: create two Nodes, delete one Node from ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    qtconceptmap->AddNode(NodeFactory().GetTest(0));
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    qtconceptmap->AddNode(NodeFactory().GetTest(0));

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_items_before{static_cast<int>(conceptmap->GetNodes().size())};

    assert(!conceptmap->GetNodes().empty());
    conceptmap->DeleteNode( conceptmap->GetNodes().back());

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_items_after{static_cast<int>(conceptmap->GetNodes().size())};
    assert(n_items_before - n_items_after == 1);

  }
  if (verbose) { TRACE("DeleteNode: delete a Node from ConceptMap using a Command"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node1 = NodeFactory().GetTest(0);
    const auto node2 = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,node1,node2);

    qtconceptmap->AddNode(node1);
    qtconceptmap->AddNode(node2);
    qtconceptmap->AddEdge(edge);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtEdges().size() == 1);

    const boost::shared_ptr<CommandDeleteNode> command {
      new CommandDeleteNode(node1)
    };
    assert(qtconceptmap->CanDoCommand(command));
    qtconceptmap->DoCommand(command);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    assert(qtconceptmap->GetQtNodes().size() == 1);
    assert(qtconceptmap->GetQtEdges().size() == 0);
  }
  if (verbose) { TRACE("DeleteNode: create two Nodes and Edge, delete one Node from ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node1 = NodeFactory().GetTest(0);
    const auto node2 = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,node1,node2);

    const auto qtnode1 = qtconceptmap->AddNode(node1);
    const auto qtnode2 = qtconceptmap->AddNode(node2);
    const auto qtedge = qtconceptmap->AddEdge(edge);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtEdges().size() == 1);

    qtconceptmap->DeleteNode(node1);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    assert(qtconceptmap->GetQtNodes().size() == 1);
    assert(qtconceptmap->GetQtEdges().size() == 0);
    assert(!qtnode1->scene());
    assert( qtnode2->scene()); //node2 is left over
    assert(!qtedge->scene());

  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    qtconceptmap->AddEdge(edge);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in ConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    conceptmap->AddEdge(edge);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in both places, ConceptMap first"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    conceptmap->AddEdge(edge);
    qtconceptmap->AddEdge(edge);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: an Edge added has to end up in both ConceptMap and QtConceptMap, by adding in both places, QtConceptMap first"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_before{static_cast<int>(qtconceptmap->GetQtEdges().size())};

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    qtconceptmap->AddEdge(edge);
    //conceptmap->AddEdge(edge); //Correctly gives a warning

    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    const int n_edges_after{static_cast<int>(qtconceptmap->GetQtEdges().size())};
    assert(n_edges_after == n_edges_before + 1);
  }
  if (verbose) { TRACE("AddEdge: added QtEdge must get selected"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    const auto qtedge = qtconceptmap->AddEdge(edge);

    assert(qtedge->isSelected());
  }
  if (verbose) { TRACE("AddEdge: added QtEdge must unselect QtNodes"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    const auto from = NodeFactory().GetTest(0);
    const auto to = NodeFactory().GetTest(0);
    const auto edge = EdgeFactory().GetTest(0,from,to);
    const auto qtfrom = qtconceptmap->AddNode(from);
    const auto qtto = qtconceptmap->AddNode(to);

    assert(qtfrom->isSelected());
    assert(qtto->isSelected());

    qtconceptmap->AddEdge(edge);

    assert(!qtfrom->isSelected());
    assert(!qtto->isSelected());
  }

  //Test Undo functionality of commands
  if (verbose) { TRACE("Undo CommandCreateNewNode"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const boost::shared_ptr<CommandCreateNewNode> command {
      new CommandCreateNewNode
    };
    assert(qtconceptmap->CanDoCommand(command));
    qtconceptmap->DoCommand(command);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);

    command->Undo();

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_again{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_again == n_nodes_before);
  }
  //QWidget Events; direct GUI responses. Note: these are done by Commands anyways,
  //so it may be hard to create a test that breaks here)
  if (verbose) { TRACE("CTRL-N creates a new QtNode"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == 0);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(qtconceptmap->GetQtNodes().size() == 1);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 1);
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N creates two QtNodes"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == 0);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(qtconceptmap->GetQtNodes().size() == 1);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 2);
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, delete, creates two QtNodes and deletes two"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == 0);

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    TRACE(conceptmap->GetNodes().size());
    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 2);
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);

    auto del = CreateDel();
    qtconceptmap->keyPressEvent(&del);

    assert(qtconceptmap->GetQtNodes().size() == 0);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 0);
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);
  }
  if (verbose) { TRACE("CTRL-N, CTRL-N, space, delete, creates two QtNodes, selects one and deletes one"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == 0);

    auto ctrl_n = CreateControlN();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 2);
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);

    auto space = CreateSpace();
    qtconceptmap->keyPressEvent(&space);

    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 1);
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);

    auto del = CreateDel();
    qtconceptmap->keyPressEvent(&del);

    assert(qtconceptmap->GetQtNodes().size() == 1);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 1);
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 0);
  }

  if (verbose) { TRACE("CTRL-N, CTRL-N, CTRL-E: new Edge should be selected"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(0);
    boost::shared_ptr<QtConceptMap> qtconceptmap(new QtConceptMap);
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == 0);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    auto ctrl_n = CreateControlN();
    auto ctrl_e = CreateControlE();
    qtconceptmap->keyPressEvent(&ctrl_n);
    qtconceptmap->keyPressEvent(&ctrl_n);

    TRACE("START");
    qtconceptmap->SetVerbosity(true);
    qtconceptmap->keyPressEvent(&ctrl_e);

    assert(qtconceptmap->GetQtNodes().size() == 2);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    assert(qtconceptmap->GetQtEdges().size() == 1);
    assert(qtconceptmap->GetQtEdges().size() == conceptmap->GetEdges().size());
    assert(qtconceptmap->GetConceptMap()->GetSelectedNodes().size() == 0);
    assert(qtconceptmap->GetConceptMap()->GetSelectedEdges().size() == 1);
  }
  assert(!"Green");



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
