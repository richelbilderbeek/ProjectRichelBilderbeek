#ifndef CONCEPTMAPNODEFACTORY_H
#define CONCEPTMAPNODEFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapcompetency.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct Node;

///Factory for creating Node instances
struct NodeFactory
{
  static const boost::shared_ptr<Node> Create(
    const boost::shared_ptr<Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);

  static const boost::shared_ptr<Node> Create(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<Node> DeepCopy(
    const boost::shared_ptr<const cmap::Node>& node);
  #endif

  ///Obtain testing nodes
  static const std::vector<boost::shared_ptr<Node> > GetTests();
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPNODEFACTORY_H
