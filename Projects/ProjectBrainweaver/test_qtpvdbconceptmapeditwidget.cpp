#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapeditwidget.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "trace.h"

#ifndef NDEBUG
void QtPvdbConceptMapEditWidget::Test()
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
    const auto v = pvdb::ConceptMapFactory::GetAllTests();
    for (const boost::shared_ptr<pvdb::ConceptMap> concept_map: v)
    {
      if (!concept_map) continue;
      assert(concept_map);
      assert(concept_map->IsValid());

      boost::shared_ptr<QtPvdbConceptMapWidget> widget(new This_t(concept_map));
      assert(widget);
      QtPvdbConceptMapWidget::Test(widget);
    }
  }
  //Deletion of nodes
  {
    const std::size_t n_concept_maps = pvdb::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!pvdb::ConceptMapFactory::GetAllTests()[i]) continue;
      const std::size_t n_nodes = pvdb::ConceptMapFactory::GetAllTests()[i]->GetNodes().size();
      for (std::size_t j=0; j!=n_nodes; ++j)
      {
        boost::shared_ptr<pvdb::ConceptMap> concept_map = pvdb::ConceptMapFactory::GetAllTests()[i];
        if (!concept_map) continue;
        assert(concept_map);
        assert(concept_map->GetNodes().size() == n_nodes);
        assert(j < concept_map->GetNodes().size());
        boost::shared_ptr<This_t> widget(new This_t(concept_map));
        assert(widget);
        QtPvdbNodeItem* const qtnode = widget->GetQtNodes()[j];
        assert(qtnode);
        widget->DeleteNode(qtnode);
        assert(widget->GetQtNodes().size() == n_nodes - 1
          && "Node must really be gone");
      }
    }
  }
  //Deletion of edges
  {
    const std::size_t n_concept_maps = pvdb::ConceptMapFactory::GetAllTests().size();
    for (std::size_t i = 0; i!=n_concept_maps; ++i)
    {
      if (!pvdb::ConceptMapFactory::GetAllTests()[i]) continue;
      const std::size_t n_edges = pvdb::ConceptMapFactory::GetAllTests()[i]->GetEdges().size();
      for (std::size_t j=0; j!=n_edges; ++j)
      {
        boost::shared_ptr<pvdb::ConceptMap> concept_map = pvdb::ConceptMapFactory::GetAllTests()[i];
        if (!concept_map) continue;
        assert(concept_map);
        assert(concept_map->GetEdges().size() == n_edges);
        assert(j < concept_map->GetEdges().size());
        boost::shared_ptr<This_t> widget(new This_t(concept_map));
        assert(widget);
        QtPvdbEdgeItem* const qtedge = widget->GetQtEdges()[j];
        widget->DeleteEdge(qtedge);
        assert(widget->GetQtEdges().size() == n_edges - 1
          && "Edge must really be gone");
      }
    }
  }
  TRACE("QtPvdbConceptMapEditWidget::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif
