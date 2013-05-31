#ifndef PVDBCONCEPTMAPFACTORY_H
#define PVDBCONCEPTMAPFACTORY_H

#include <array>
#include <vector>
#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconceptmap.h"
#include "pvdbcluster.h"
#endif

namespace pvdb {

///Class to create PvdB instances
struct ConceptMapFactory
{
  //Create an empty-as-can-get ConceptMap
  static const boost::shared_ptr<pvdb::ConceptMap> Create(
    const std::string& focal_question);

  static const boost::shared_ptr<pvdb::ConceptMap> CreateFromCluster(
    const std::string& question,
    const boost::shared_ptr<pvdb::Cluster>& cluster);

  static const boost::shared_ptr<pvdb::ConceptMap> Create(
    const std::vector<boost::shared_ptr<pvdb::Node> >& nodes,
    const std::vector<boost::shared_ptr<pvdb::Edge> >& edges = {});

  static const boost::shared_ptr<pvdb::ConceptMap> DeepCopy(
    const boost::shared_ptr<const pvdb::ConceptMap>& map);

  ///Get all the other tests as one vector
  static const std::vector<boost::shared_ptr<pvdb::ConceptMap> > GetAllTests();

  ///Get the documented heteromorphous test concept maps
  static const std::vector<boost::shared_ptr<pvdb::ConceptMap> > GetHeteromorphousTestConceptMaps();

  ///Get the documented complex homomorphous test concept maps
  static const std::vector<boost::shared_ptr<pvdb::ConceptMap> > GetComplexHomomorphousTestConceptMaps();

  ///Get the documented simple homomorphous test concept maps
  static const std::vector<boost::shared_ptr<pvdb::ConceptMap> > GetSimpleHomomorphousTestConceptMaps();
};

} //~namespace pvdb

#endif // PVDBCONCEPTMAPFACTORY_H
