#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "pvdbcluster.h"

#include <algorithm>
#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <vector>
#include <boost/shared_ptr.hpp>

#include "conceptmapcompetency.h"
#include "pvdbcluster.h"
#include "pvdbclusterfactory.h"
#include "pvdbhelper.h"
#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "conceptmapexample.h"
#include "conceptmapconceptfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

void ribi::pvdb::Cluster::Test()
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

  TRACE("Cluster::Test started");
  //Test operator== and operator!=
  {
    const std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > tmp_tests_1 = ribi::pvdb::ClusterFactory::GetTests();
    const int sz = static_cast<int>(tmp_tests_1.size());
    for (int i=0; i!=sz; ++i)
    {
      const std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > tmp_tests_a = ribi::pvdb::ClusterFactory::GetTests(); //For crosscompiler
      const boost::shared_ptr<const ribi::pvdb::Cluster> a = tmp_tests_a.at(i);
      if (!a) continue;
      assert(a);
      const std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > tmp_tests_b = ribi::pvdb::ClusterFactory::GetTests(); //For crosscompiler
      const boost::shared_ptr<ribi::pvdb::Cluster> b = tmp_tests_b.at(i);
      if (!b) continue;
      assert(a); assert(b);
      assert(IsEqual(*a,*a));
      assert(IsEqual(*a,*b));
      assert(IsEqual(*b,*a));
      assert(IsEqual(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        const std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > tmp_tests_c = ribi::pvdb::ClusterFactory::GetTests(); //For crosscompiler
        const std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > tmp_tests_d = ribi::pvdb::ClusterFactory::GetTests(); //For crosscompiler
        const boost::shared_ptr<const ribi::pvdb::Cluster> c = tmp_tests_c.at(j);
        if (!c) continue;
        assert(c);
        const boost::shared_ptr<ribi::pvdb::Cluster> d = tmp_tests_d.at(j);
        if (!d) continue;
        assert(c); assert(d);
        assert(IsEqual(*c,*c));
        assert(IsEqual(*c,*d));
        assert(IsEqual(*d,*c));
        assert(IsEqual(*d,*d));
        if (i==j)
        {
          assert(IsEqual(*a,*c)); assert(IsEqual(*a,*d));
          assert(IsEqual(*b,*c)); assert(IsEqual(*b,*d));
          assert(IsEqual(*c,*a)); assert(IsEqual(*c,*b));
          assert(IsEqual(*d,*a)); assert(IsEqual(*d,*b));
        }
        else
        {
          assert(!IsEqual(*a,*c)); assert(!IsEqual(*a,*d));
          assert(!IsEqual(*b,*c)); assert(!IsEqual(*b,*d));
          assert(!IsEqual(*c,*a)); assert(!IsEqual(*c,*b));
          assert(!IsEqual(*d,*a)); assert(!IsEqual(*d,*b));
        }
      }
    }
  }
  //Test all Clusters with each combination of Concepts
  {
    const std::vector<std::vector<boost::shared_ptr<ribi::cmap::Concept> > > v
      = GetCombinations(cmap::ConceptFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const std::vector<boost::shared_ptr<ribi::cmap::Concept> >& concepts)
      {
        const boost::shared_ptr<ribi::pvdb::Cluster> c(new ribi::pvdb::Cluster(concepts));
        assert(c);
        const std::string s = ToXml(c);
        const boost::shared_ptr<ribi::pvdb::Cluster> d = FromXml(s);
        assert(d);
        assert(c != d);
        assert(IsEqual(*c,*d));
      }
    );
  }
  TRACE("Cluster::Test finished successfully");

  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
