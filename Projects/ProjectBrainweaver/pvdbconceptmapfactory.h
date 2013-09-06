#ifndef PVDBCONCEPTMAPFACTORY_H
#define PVDBCONCEPTMAPFACTORY_H

#include <array>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///Class to create PvdB instances
struct ConceptMapFactory
{
  //Create an empty-as-can-get ConceptMap
  static const boost::shared_ptr<ribi::pvdb::ConceptMap> Create(
    const std::string& focal_question);

  static const boost::shared_ptr<ribi::pvdb::ConceptMap> CreateFromCluster(
    const std::string& question,
    const boost::shared_ptr<pvdb::Cluster>& cluster);

  static const boost::shared_ptr<ribi::pvdb::ConceptMap> Create(
    const std::vector<boost::shared_ptr<ribi::pvdb::Node> >& nodes,
    const std::vector<boost::shared_ptr<ribi::pvdb::Edge> >& edges = {});

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<ribi::pvdb::ConceptMap> DeepCopy(
    const boost::shared_ptr<const ribi::pvdb::ConceptMap> map);
  #endif

  ///Obtain a ConceptMap from an XML std::string
  static const boost::shared_ptr<ribi::pvdb::ConceptMap> FromXml(const std::string& s);

  ///Get all the other tests as one vector
  static const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > GetAllTests();

  ///Get the documented heteromorphous test concept maps
  static const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > GetHeteromorphousTestConceptMaps();

  ///Get the documented complex homomorphous test concept maps
  static const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > GetComplexHomomorphousTestConceptMaps();

  ///Get the documented simple homomorphous test concept maps
  static const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > GetSimpleHomomorphousTestConceptMaps();
};

} //~namespace pvdb

} //~namespace ribi

#endif // PVDBCONCEPTMAPFACTORY_H
