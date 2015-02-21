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
#include "qteditconceptmap.h"

#include "conceptmapfactory.h"
#include "conceptmap.h"
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
  const TestTimer test_timer{__func__,__FILE__,0.1};
  //Test cloning
  {
  }
  //Test base class (after having tested cloning of derived class)
  {
    const auto v = ribi::cmap::ConceptMapFactory().GetAllTests();
    for (const boost::shared_ptr<ConceptMap> concept_map: v)
    {
      if (!concept_map) continue;
      assert(concept_map);
      assert(concept_map->IsValid());

      boost::shared_ptr<QtConceptMap> widget(new This_t(concept_map));
      assert(widget);
      QtConceptMap::Test(widget);
    }
  }
  //Deletion of nodes
  {
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory().GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory().GetAllTests()[i]) continue;
      const std::size_t n_nodes = ribi::cmap::ConceptMapFactory().GetAllTests()[i]->GetNodes().size();
      for (std::size_t j=0; j!=n_nodes; ++j)
      {
        boost::shared_ptr<ConceptMap> concept_map = ribi::cmap::ConceptMapFactory().GetAllTests()[i];
        if (!concept_map) continue;
        assert(concept_map);
        assert(concept_map->GetNodes().size() == n_nodes);
        assert(j < concept_map->GetNodes().size());
        boost::shared_ptr<This_t> widget(new This_t(concept_map));
        assert(widget);
        QtNode* const qtnode = widget->GetQtNodes()[j];
        assert(qtnode);
        widget->DeleteNode(qtnode);
        assert(widget->GetQtNodes().size() == n_nodes - 1
          && "Node must really be gone");
      }
    }
  }
  //Deletion of edges
  {
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory().GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory().GetAllTests()[i]) continue;
      const std::size_t n_edges = ribi::cmap::ConceptMapFactory().GetAllTests()[i]->GetEdges().size();
      for (std::size_t j=0; j!=n_edges; ++j)
      {
        boost::shared_ptr<ConceptMap> concept_map = ribi::cmap::ConceptMapFactory().GetAllTests()[i];
        if (!concept_map) continue;
        assert(concept_map);
        assert(concept_map->GetEdges().size() == n_edges);
        assert(j < concept_map->GetEdges().size());
        boost::shared_ptr<This_t> widget(new This_t(concept_map));
        assert(widget);
        QtEdge* const qtedge = widget->GetQtEdges()[j];
        widget->DeleteEdge(qtedge);
        assert(widget->GetQtEdges().size() == n_edges - 1
          && "Edge must really be gone");
      }
    }
  }

}
#endif
