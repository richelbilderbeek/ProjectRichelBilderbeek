#ifndef PVDBNODEFACTORY_H
#define PVDBNODEFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "pvdbcompetency.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct Node;

///Factory for creating Node instances
struct NodeFactory
{
  static const boost::shared_ptr<ribi::pvdb::Node> Create(
    const boost::shared_ptr<ribi::pvdb::Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);

  static const boost::shared_ptr<ribi::pvdb::Node> Create(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<ribi::pvdb::Node> DeepCopy(
    const boost::shared_ptr<const pvdb::Node>& node);
  #endif

  ///Obtain testing nodes
  static const std::vector<boost::shared_ptr<ribi::pvdb::Node> > GetTests();
};

} //~namespace pvdb
} //~namespace ribi

#endif // PVDBNODEFACTORY_H
