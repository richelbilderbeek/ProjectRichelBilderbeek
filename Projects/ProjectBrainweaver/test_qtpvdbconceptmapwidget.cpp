#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbconceptmapwidget.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

#include "pvdbconceptmap.h"
#include "pvdbconceptmapfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapWidget::Test(const boost::shared_ptr<const QtPvdbConceptMapWidget>& widget)
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::pvdb::QtPvdbConceptMapWidget::Test");
  assert(widget);
  //#define I_REALLY_WANT_TO_TEST_THIS_82374983758937459347623958634948603
  #ifdef  I_REALLY_WANT_TO_TEST_THIS_82374983758937459347623958634948603
  //Test conversion between widget and concept map for simple homomorphous concept maps
  {
    const auto v = ribi::pvdb::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps();
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; i++)
    {
      auto w = widget->CreateNewDerived();
      assert(w);
      //w->ReadFromConceptMap(v[i]);
      const boost::shared_ptr<ribi::pvdb::ConceptMap> n = w->GetConceptMap();
      if (!pvdb::ConceptMap::HasSameContent(*v[i],*n))
      {
        TRACE(i);
        TRACE("GetSimpleHomomorphousTestConceptMaps");
      }
      assert(pvdb::ConceptMap::HasSameContent(*v[i],*n));
    }
  }
  //Test conversion between widget and concept map for complex homomorphous concept maps
  {
    const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > v = ribi::pvdb::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps();
    const int sz = v.size();
    for (int i=0; i!=sz; i++)
    {
      auto w = widget->CreateNewDerived();
      assert(w);
      //w->ReadFromConceptMap(v[i]);
      const boost::shared_ptr<ribi::pvdb::ConceptMap> n = w->GetConceptMap();
      if (!pvdb::ConceptMap::HasSameContent(*v[i],*n))
      {
        TRACE(i);
        TRACE("GetComplexHomomorphousTestConceptMaps");
      }
      assert(pvdb::ConceptMap::HasSameContent(*v[i],*n));
    }
  }
  //Test conversion between widget and concept map for heteromorphous concept maps
  {
    const auto v = ribi::pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
    const int sz = v.size();
    for (int i=0; i!=sz; i++)
    {
      auto w = widget->CreateNewDerived();
      //w->ReadFromConceptMap(v[i]);
      const boost::shared_ptr<ribi::pvdb::ConceptMap> n = w->GetConceptMap();
      if (!pvdb::ConceptMap::HasSameContent(*v[i],*n))
      {
        TRACE(i);
        TRACE("GetHeteromorphousTestConceptMaps");
      }
      assert(pvdb::ConceptMap::HasSameContent(*v[i],*n));
    }
  }
  //Test conversion between widget and concept map for brute-force concept map
  {
    const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > maps = ribi::pvdb::ConceptMapFactory::GetAllTests();
    std::for_each(maps.begin(),maps.end(),
      [widget](const boost::shared_ptr<ribi::pvdb::ConceptMap>& m)
      {
        auto w = widget->CreateNewDerived();
        //w->ReadFromConceptMap(m);
        const boost::shared_ptr<ribi::pvdb::ConceptMap> n = w->GetConceptMap();
        assert(pvdb::ConceptMap::HasSameContent(*m,*n));
      }
    );
  }
  #endif
  TRACE("ribi::pvdb::QtPvdbConceptMapWidget::Test finished successfully");
}
#endif

