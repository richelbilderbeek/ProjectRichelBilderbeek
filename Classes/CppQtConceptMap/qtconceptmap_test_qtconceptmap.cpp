#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmap.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

#include "conceptmap.h"
#include "conceptmapfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::cmap::QtConceptMap::Test(const boost::shared_ptr<const QtConceptMap>& concept_map) noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtConceptMap::Test");
  assert(concept_map);
  //#define I_REALLY_WANT_TO_TEST_THIS_82374983758937459347623958634948603
  #ifdef  I_REALLY_WANT_TO_TEST_THIS_82374983758937459347623958634948603
  //Test conversion between widget and concept map for simple homomorphous concept maps
  {
    const auto v = ribi::cmap::ConceptMapFactory::GetSimpleHomomorphousTestConceptMaps();
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; i++)
    {
      auto w = widget->CreateNewDerived();
      assert(w);
      //w->ReadFromConceptMap(v[i]);
      const boost::shared_ptr<ribi::cmap::ConceptMap> n = w->GetConceptMap();
      if (!cmap::ConceptMap::HasSameContent(*v[i],*n))
      {
        TRACE(i);
        TRACE("GetSimpleHomomorphousTestConceptMaps");
      }
      assert(cmap::ConceptMap::HasSameContent(*v[i],*n));
    }
  }
  //Test conversion between widget and concept map for complex homomorphous concept maps
  {
    const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > v = ribi::cmap::ConceptMapFactory::GetComplexHomomorphousTestConceptMaps();
    const int sz = v.size();
    for (int i=0; i!=sz; i++)
    {
      auto w = widget->CreateNewDerived();
      assert(w);
      //w->ReadFromConceptMap(v[i]);
      const boost::shared_ptr<ribi::cmap::ConceptMap> n = w->GetConceptMap();
      if (!cmap::ConceptMap::HasSameContent(*v[i],*n))
      {
        TRACE(i);
        TRACE("GetComplexHomomorphousTestConceptMaps");
      }
      assert(cmap::ConceptMap::HasSameContent(*v[i],*n));
    }
  }
  //Test conversion between widget and concept map for heteromorphous concept maps
  {
    const auto v = ribi::cmap::ConceptMapFactory::GetHeteromorphousTestConceptMaps();
    const int sz = v.size();
    for (int i=0; i!=sz; i++)
    {
      auto w = widget->CreateNewDerived();
      //w->ReadFromConceptMap(v[i]);
      const boost::shared_ptr<ribi::cmap::ConceptMap> n = w->GetConceptMap();
      if (!cmap::ConceptMap::HasSameContent(*v[i],*n))
      {
        TRACE(i);
        TRACE("GetHeteromorphousTestConceptMaps");
      }
      assert(cmap::ConceptMap::HasSameContent(*v[i],*n));
    }
  }
  //Test conversion between widget and concept map for brute-force concept map
  {
    const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > maps = ribi::cmap::ConceptMapFactory::GetAllTests();
    std::for_each(maps.begin(),maps.end(),
      [widget](const boost::shared_ptr<ribi::cmap::ConceptMap>& m)
      {
        auto w = widget->CreateNewDerived();
        //w->ReadFromConceptMap(m);
        const boost::shared_ptr<ribi::cmap::ConceptMap> n = w->GetConceptMap();
        assert(cmap::ConceptMap::HasSameContent(*m,*n));
      }
    );
  }
  #endif
  TRACE("ribi::cmap::QtConceptMap::Test finished successfully");
}
#endif

