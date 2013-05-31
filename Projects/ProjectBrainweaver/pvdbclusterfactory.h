#ifndef PVDBCLUSTERFACTORY_H
#define PVDBCLUSTERFACTORY_H

#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbcluster.h"
#endif

namespace pvdb {

///Factory for creating Cluster instances
struct ClusterFactory
{
  static const boost::shared_ptr<pvdb::Cluster> Create(const std::vector<boost::shared_ptr<pvdb::Concept> >& v);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<pvdb::Cluster> DeepCopy(const boost::shared_ptr<const pvdb::Cluster> cluster);
  #endif

  ///Obtain a single test, a combination of testing node indices
  static const boost::shared_ptr<pvdb::Cluster> GetTest(const std::vector<int>& test_node_indices);

  static const std::vector<boost::shared_ptr<pvdb::Cluster> > GetTests();
};

} //~namespace pvdb

#endif // PVDBCLUSTERFACTORY_H
