#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbcluster.h"

#include <algorithm>
#include <cassert>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <vector>
#include <boost/shared_ptr.hpp>

#include "pvdbcompetency.h"
#include "pvdbcluster.h"
#include "pvdbclusterfactory.h"
#include "pvdbhelper.h"
#include "pvdbconcept.h"
#include "pvdbexamples.h"
#include "pvdbexample.h"
#include "pvdbconceptfactory.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

void pvdb::Cluster::Test()
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
    const std::vector<boost::shared_ptr<pvdb::Cluster> > tmp_tests_1 = pvdb::ClusterFactory::GetTests();
    const int sz = static_cast<int>(tmp_tests_1.size());
    for (int i=0; i!=sz; ++i)
    {
      const std::vector<boost::shared_ptr<pvdb::Cluster> > tmp_tests_a = pvdb::ClusterFactory::GetTests(); //For crosscompiler
      const boost::shared_ptr<const pvdb::Cluster> a = tmp_tests_a.at(i);
      if (!a) continue;
      assert(a);
      const std::vector<boost::shared_ptr<pvdb::Cluster> > tmp_tests_b = pvdb::ClusterFactory::GetTests(); //For crosscompiler
      const boost::shared_ptr<pvdb::Cluster> b = tmp_tests_b.at(i);
      if (!b) continue;
      assert(a); assert(b);
      assert(IsEqual(*a,*a));
      assert(IsEqual(*a,*b));
      assert(IsEqual(*b,*a));
      assert(IsEqual(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        const std::vector<boost::shared_ptr<pvdb::Cluster> > tmp_tests_c = pvdb::ClusterFactory::GetTests(); //For crosscompiler
        const std::vector<boost::shared_ptr<pvdb::Cluster> > tmp_tests_d = pvdb::ClusterFactory::GetTests(); //For crosscompiler
        const boost::shared_ptr<const pvdb::Cluster> c = tmp_tests_c.at(j);
        if (!c) continue;
        assert(c);
        const boost::shared_ptr<      pvdb::Cluster> d = tmp_tests_d.at(j);
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
    const std::vector<std::vector<boost::shared_ptr<pvdb::Concept> > > v
      = GetCombinations(pvdb::ConceptFactory::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const std::vector<boost::shared_ptr<pvdb::Concept> >& concepts)
      {
        const boost::shared_ptr<pvdb::Cluster> c(new pvdb::Cluster(concepts));
        assert(c);
        const std::string s = ToXml(c);
        const boost::shared_ptr<pvdb::Cluster> d = FromXml(s);
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

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
