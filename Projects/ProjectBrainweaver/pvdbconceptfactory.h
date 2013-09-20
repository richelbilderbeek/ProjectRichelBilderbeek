#ifndef PVDBCONCEPTFACTORY_H
#define PVDBCONCEPTFACTORY_H

#include <array>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include "pvdbcompetency.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

///Creates ribi::pvdb::Concepts
struct ConceptFactory
{
  //Default and complete Create method
  static const boost::shared_ptr<ribi::pvdb::Concept> Create(
    const std::string& name,
    const boost::shared_ptr<ribi::pvdb::Examples>& examples,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specificity);

  static const boost::shared_ptr<ribi::pvdb::Concept> Create(
    const std::string& name = "...", //2013-09-18
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const bool is_complex = true,
    const int rating_complexity = -1,
    const int rating_concreteness = -1,
    const int rating_specificity = -1
    );

  #ifndef NDEBUG
  ///Like a Concept deep-copy constructor
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<ribi::pvdb::Concept> DeepCopy(
    const boost::shared_ptr<const ribi::pvdb::Concept>& concept);
  #endif

  ///Obtain some testing concepts
  static const std::vector<boost::shared_ptr<ribi::pvdb::Concept> > GetTests();
};

} //~namespace pvdb
} //~namespace ribi

#endif // PVDBCONCEPTFACTORY_H
