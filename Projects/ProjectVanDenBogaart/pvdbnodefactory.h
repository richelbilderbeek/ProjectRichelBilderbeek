#ifndef PVDBNODEFACTORY_H
#define PVDBNODEFACTORY_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "pvdbcompetency.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif

namespace pvdb {

struct Node;

///Factory for creating Node instances
struct NodeFactory
{
  static const boost::shared_ptr<pvdb::Node> Create(
    const boost::shared_ptr<pvdb::Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);

  static const boost::shared_ptr<pvdb::Node> Create(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0);

  static const boost::shared_ptr<pvdb::Node> DeepCopy(
    const boost::shared_ptr<const pvdb::Node>& node);

  ///Obtain testing nodes
  static const std::vector<boost::shared_ptr<pvdb::Node> > GetTests();
};

} //~namespace pvdb

#ifndef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbnode.h"
#endif


#endif // PVDBNODEFACTORY_H
