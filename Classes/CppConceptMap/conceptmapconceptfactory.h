#ifndef CONCEPTMAPCONCEPTFACTORY_H
#define CONCEPTMAPCONCEPTFACTORY_H

#include <array>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include "conceptmapcompetency.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Creates Concepts
struct ConceptFactory
{
  //Default and complete Create method
  static const boost::shared_ptr<Concept> Create(
    const std::string& name,
    const boost::shared_ptr<Examples>& examples,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specificity);

  static const boost::shared_ptr<Concept> Create(
    const std::string& name = "...",
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const bool is_complex = true,
    const int rating_complexity = -1,
    const int rating_concreteness = -1,
    const int rating_specificity = -1
    );

  #ifndef NDEBUG
  ///Like a Concept deep-copy constructor
  ///DeepCopy is only used for debugging
  static const boost::shared_ptr<Concept> DeepCopy(
    const boost::shared_ptr<const Concept>& concept);
  #endif

  ///Obtain some testing concepts
  static const std::vector<boost::shared_ptr<Concept> > GetTests();
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCONCEPTFACTORY_H
