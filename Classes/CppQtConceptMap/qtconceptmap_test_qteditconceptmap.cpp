#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qteditconceptmap.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include "conceptmapfactory.h"
#include "conceptmap.h"
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
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  //Test cloning
  {
  }
  //Test base class (after having tested cloning of derived class)
  {
    const auto v = ribi::cmap::ConceptMapFactory::GetAllTests();
    for (const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map: v)
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
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory::GetAllTests()[i]) continue;
      const std::size_t n_nodes = ribi::cmap::ConceptMapFactory::GetAllTests()[i]->GetNodes().size();
      for (std::size_t j=0; j!=n_nodes; ++j)
      {
        boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = ribi::cmap::ConceptMapFactory::GetAllTests()[i];
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
    const std::size_t n_concept_maps = ribi::cmap::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!cmap::ConceptMapFactory::GetAllTests()[i]) continue;
      const std::size_t n_edges = ribi::cmap::ConceptMapFactory::GetAllTests()[i]->GetEdges().size();
      for (std::size_t j=0; j!=n_edges; ++j)
      {
        boost::shared_ptr<ribi::cmap::ConceptMap> concept_map = ribi::cmap::ConceptMapFactory::GetAllTests()[i];
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
  TRACE("ribi::cmap::QtEditConceptMap::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif
