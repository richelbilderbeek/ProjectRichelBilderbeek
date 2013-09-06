#ifndef PVDBEDGEFACTORY_H
#define PVDBEDGEFACTORY_H

#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

struct EdgeFactory
{
  static const boost::shared_ptr<ribi::pvdb::Edge> Create(
    const boost::shared_ptr<ribi::pvdb::Concept>& concept,
    const double concept_x,
    const double concept_y,
    const boost::shared_ptr<ribi::pvdb::Node> from,
    const bool tail_arrow,
    const boost::shared_ptr<ribi::pvdb::Node> to,
    const bool head_arrow);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  ///The nodes need to be the deepcopied ones
  static const boost::shared_ptr<ribi::pvdb::Edge> DeepCopy(
    const boost::shared_ptr<const pvdb::Edge> edge,
    const boost::shared_ptr<ribi::pvdb::Node> from,
    const boost::shared_ptr<ribi::pvdb::Node> to);
  #endif

  ///Obtain an Edge from an XML std::string
  ///You need the real nodes to connect the edge to
  static const boost::shared_ptr<ribi::pvdb::Edge> FromXml(
    const std::string& s,
    const std::vector<boost::shared_ptr<ribi::pvdb::Node> >& nodes);

  ///Get testing edges connecting the two supplied nodes
  static const std::vector<boost::shared_ptr<ribi::pvdb::Edge> > GetTests(
    const boost::shared_ptr<ribi::pvdb::Node> from,
    const boost::shared_ptr<ribi::pvdb::Node> to);
};

} //~namespace pvdb

} //~namespace ribi

#endif // PVDBEDGEFACTORY_H
