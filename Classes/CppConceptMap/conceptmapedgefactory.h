#ifndef CONCEPTMAPEDGEFACTORY_H
#define CONCEPTMAPEDGEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct EdgeFactory
{
  static const boost::shared_ptr<Edge> Create(
    const boost::shared_ptr<Concept>& concept,
    const double concept_x,
    const double concept_y,
    const boost::shared_ptr<Node> from,
    const bool tail_arrow,
    const boost::shared_ptr<Node> to,
    const bool head_arrow);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  ///The nodes need to be the deepcopied ones
  static const boost::shared_ptr<Edge> DeepCopy(
    const boost::shared_ptr<const cmap::Edge> edge,
    const boost::shared_ptr<Node> from,
    const boost::shared_ptr<Node> to);
  #endif

  ///Obtain an Edge from an XML std::string
  ///You need the real nodes to connect the edge to
  static const boost::shared_ptr<Edge> FromXml(
    const std::string& s,
    const std::vector<boost::shared_ptr<Node> >& nodes);

  ///Get testing edges connecting the two supplied nodes
  static const std::vector<boost::shared_ptr<Edge> > GetTests(
    const boost::shared_ptr<Node> from,
    const boost::shared_ptr<Node> to);
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEDGEFACTORY_H
