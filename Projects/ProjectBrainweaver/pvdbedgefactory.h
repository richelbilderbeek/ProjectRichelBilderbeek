#ifndef PVDBEDGEFACTORY_H
#define PVDBEDGEFACTORY_H

#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#include "pvdbedge.h"
#endif


namespace pvdb {

struct EdgeFactory
{
  static const boost::shared_ptr<pvdb::Edge> Create(
    const boost::shared_ptr<pvdb::Concept>& concept,
    const double concept_x,
    const double concept_y,
    const int from,
    const bool tail_arrow,
    const int to,
    const bool head_arrow);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<pvdb::Edge> DeepCopy(
    const boost::shared_ptr<const pvdb::Edge> edge);
  #endif

  static const std::vector<boost::shared_ptr<pvdb::Edge> > GetTests();
};

} //~namespace pvdb

#endif // PVDBEDGEFACTORY_H
