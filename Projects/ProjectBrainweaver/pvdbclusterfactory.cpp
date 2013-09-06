#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbclusterfactory.h"

#include <cassert>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "pvdbcluster.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "trace.h"

const boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::ClusterFactory::Create(const std::vector<boost::shared_ptr<ribi::pvdb::Concept> >& v)
{
  assert(std::count_if(v.begin(),v.end(),[](const boost::shared_ptr<ribi::pvdb::Concept>& p) { return !p; } ) == 0); //FIX 2012-01-02
  //assert(std::all_of(v.begin(),v.end(),[](const boost::shared_ptr<ribi::pvdb::Concept>& p) { return p; } ));
  const boost::shared_ptr<pvdb::Cluster> p(new pvdb::Cluster(v));
  assert(p);
  return p;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::ClusterFactory::DeepCopy(const boost::shared_ptr<const pvdb::Cluster> cluster)
{
  const std::vector<boost::shared_ptr<const ribi::pvdb::Concept> > v = cluster->Get();
  std::vector<boost::shared_ptr<ribi::pvdb::Concept> > w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const boost::shared_ptr<const ribi::pvdb::Concept>& c)
    {
      assert(c);
      const boost::shared_ptr<ribi::pvdb::Concept> d = ribi::pvdb::ConceptFactory::DeepCopy(c);
      assert(d);
      assert(c != d);
      assert(IsEqual(*c,*d));
      return d;
    }
  );

  boost::shared_ptr<pvdb::Cluster> p(new Cluster(w));
  assert(p);
  assert(p != cluster);
  assert(IsEqual(*p,*cluster));
  return p;
}
#endif

const boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::ClusterFactory::GetTest(const std::vector<int>& test_node_indices)
{
  std::vector<boost::shared_ptr<ribi::pvdb::Concept> > concepts;
  std::transform(test_node_indices.begin(),test_node_indices.end(),std::back_inserter(concepts),
    [](const int index)
    {
      const std::vector<boost::shared_ptr<ribi::pvdb::Concept> > tmp = ConceptFactory::GetTests();
      const boost::shared_ptr<ribi::pvdb::Concept> concept = tmp.at(index);
      assert(concept);
      return concept;
    }
  );
  assert(std::count_if(concepts.begin(),concepts.end(),[](const boost::shared_ptr<ribi::pvdb::Concept>& p) { return !p; } ) == 0);
  boost::shared_ptr<pvdb::Cluster> cluster(new Cluster(concepts));
  assert(cluster);
  return cluster;
}

const std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > ribi::pvdb::ClusterFactory::GetTests()
{
  std::vector<boost::shared_ptr<pvdb::Cluster> > v(6);
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {0} );
    assert(p);
    v[0] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {1} );
    assert(p);
    v[1] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {0,1} );
    assert(p);
    v[2] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {0,1,2} );
    assert(p);
    v[3] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {} );
    assert(p);
    v[4] = p;
  }
  {
    //NULLPTR
    const boost::shared_ptr<pvdb::Cluster> p;
    assert(!p);
    v[5] = p;
  }
  /* DO NOT DO THIS FOR WINE
  const std::vector<boost::shared_ptr<pvdb::Cluster> > v
    =
    {
      GetTest( {0} ),
      GetTest( {1} ),
      GetTest( {0,1} ),
      GetTest( {0,1,2} ),
      GetTest( { } )
    };
  */
  return v;
}

