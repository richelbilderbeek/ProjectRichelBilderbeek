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
#include "qteditconceptmap.h"

#include <chrono>

#include "qtconceptmapcollect.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::QtEditConceptMap::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer{__func__,__FILE__,0.2};
  TestTimer::SetMaxCnt(2); //Because the base class has to be tested as well
  const bool verbose{false};

  //SetConceptMap and GetConceptMap return the same
  {
    QtEditConceptMap m;
    const boost::shared_ptr<ConceptMap> concept_map{
      ConceptMapFactory().GetHeteromorphousTestConceptMap(2)
    };
    m.SetConceptMap(concept_map);
    assert(m.GetConceptMap() == concept_map);
  }
  //SetConceptMap, two nodes
  {
    QtEditConceptMap m;
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
  //SetConceptMap, 3 nodes, 1 edge
  {
    QtEditConceptMap m;
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
  //Test base class (after having tested cloning of derived class)
  {
    const boost::shared_ptr<ConceptMap> concept_map
      = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(15);
    assert(concept_map);
    assert(concept_map->IsValid());

    boost::shared_ptr<QtConceptMap> widget(new This_t);
    widget->SetConceptMap(concept_map);
    assert(widget);
    QtConceptMap::Test(widget);
  }
  //Deletion of nodes
  {
    const int concept_map_index{3};
    const std::size_t n_nodes = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(concept_map_index)->GetNodes().size();
    for (std::size_t j=0; j!=n_nodes; ++j)
    {
      boost::shared_ptr<ConceptMap> concept_map = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(concept_map_index);
      if (!concept_map) continue;
      assert(concept_map);
      assert(concept_map->GetNodes().size() == n_nodes);
      assert(j < concept_map->GetNodes().size());
      boost::shared_ptr<This_t> widget(new This_t);
      assert(widget);
      widget->SetConceptMap(concept_map);
      QtNode* const qtnode = widget->GetQtNodes()[j];
      assert(qtnode);
      widget->DeleteNode(qtnode);
      assert(widget->GetQtNodes().size() == n_nodes - 1
        && "Node must really be gone");
    }
  }
  //Deletion of edges
  {
    const int concept_map_index{3};
    const std::size_t n_edges = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(concept_map_index)->GetEdges().size();
    for (std::size_t j=0; j!=n_edges; ++j)
    {
      boost::shared_ptr<ConceptMap> concept_map = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(concept_map_index);
      if (!concept_map) continue;
      assert(concept_map);
      assert(concept_map->GetEdges().size() == n_edges);
      assert(j < concept_map->GetEdges().size());
      boost::shared_ptr<This_t> widget(new This_t);
      assert(widget);
      widget->SetConceptMap(concept_map);
      QtEdge* const qtedge = widget->GetQtEdges()[j];
      widget->DeleteEdge(qtedge);
      assert(widget->GetQtEdges().size() == n_edges - 1
        && "Edge must really be gone");
    }
  }

  if (verbose) { TRACE("AddNode: a Node added end up in both ConceptMap and QtConceptMap, by adding in both places"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtEditConceptMap> qtconceptmap(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
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
    boost::shared_ptr<QtEditConceptMap> qtconceptmap(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    qtconceptmap->SetConceptMap(conceptmap);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_before{static_cast<int>(qtconceptmap->GetQtNodes().size())};

    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node); //First Qt
    conceptmap->AddNode(node);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
    const int n_nodes_after{static_cast<int>(qtconceptmap->GetQtNodes().size())};
    assert(n_nodes_after == n_nodes_before + 1);
  }
  assert(!"Works, but awkward UI");


  if (verbose) { TRACE("AddNode: a Node added gets a QtNode to be found in QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtEditConceptMap> qtconceptmap(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    qtconceptmap->SetConceptMap(conceptmap);
    const auto node = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node);
    assert(qtconceptmap->FindQtNode(node.get()));
  }
  if (verbose) { TRACE("DeleteNode: a Node added gets a QtNode to be found in QtConceptMap"); }
  {
    boost::shared_ptr<ConceptMap> conceptmap = ribi::cmap::ConceptMapFactory().GetHeteromorphousTestConceptMap(1);
    boost::shared_ptr<QtEditConceptMap> qtconceptmap(new QtEditConceptMap(QtEditConceptMap::Mode::simple));
    qtconceptmap->SetConceptMap(conceptmap);


    const auto node1 = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node1);

    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    const auto node2 = NodeFactory().GetTest(0);
    qtconceptmap->AddNode(node2);

    const int n_items_before = qtconceptmap->GetScene()->items().count();
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());

    qtconceptmap->DeleteNode( qtconceptmap->FindQtNode(node1.get() ) );

    const int n_items_after = qtconceptmap->GetScene()->items().count();
    assert(n_items_before - n_items_after == 1);
    assert(qtconceptmap->GetQtNodes().size() == conceptmap->GetNodes().size());
  }
  TestTimer::SetMaxCnt(1); //Because the base class has been tested now
}
#endif
