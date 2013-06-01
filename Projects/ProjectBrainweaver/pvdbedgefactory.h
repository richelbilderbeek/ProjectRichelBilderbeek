#ifndef PVDBEDGEFACTORY_H
#define PVDBEDGEFACTORY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

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
    const boost::shared_ptr<pvdb::Node> from,
    const bool tail_arrow,
    const boost::shared_ptr<pvdb::Node> to,
    const bool head_arrow);

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  ///The nodes need to be the deepcopied ones
  static const boost::shared_ptr<pvdb::Edge> DeepCopy(
    const boost::shared_ptr<const pvdb::Edge> edge,
    const boost::shared_ptr<pvdb::Node> from,
    const boost::shared_ptr<pvdb::Node> to);
  #endif

  ///Obtain an Edge from an XML std::string
  ///You need the real nodes to connect the edge to
  static const boost::shared_ptr<pvdb::Edge> FromXml(
    const std::string& s,
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes);

  ///Get testing edges connecting the two supplied nodes
  static const std::vector<boost::shared_ptr<pvdb::Edge> > GetTests(
    const boost::shared_ptr<pvdb::Node> from,
    const boost::shared_ptr<pvdb::Node> to);
};

} //~namespace pvdb

#endif // PVDBEDGEFACTORY_H
