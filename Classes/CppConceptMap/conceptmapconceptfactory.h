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
  ConceptFactory();

  //Default and complete Create method
  const boost::shared_ptr<Concept> Create(
    const std::string& name,
    const boost::shared_ptr<Examples>& examples,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specificity
  ) const noexcept;

  const boost::shared_ptr<Concept> Create(
    const std::string& name = "...",
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const bool is_complex = true,
    const int rating_complexity = -1,
    const int rating_concreteness = -1,
    const int rating_specificity = -1
  ) const noexcept;

  #ifndef NDEBUG
  ///Like a Concept deep-copy constructor
  ///DeepCopy is only used for debugging
  const boost::shared_ptr<Concept> DeepCopy(
    const boost::shared_ptr<const Concept>& concept
  ) const noexcept;
  #endif

  ///Read concept from a std::string read from file
  const boost::shared_ptr<Concept> FromXml(const std::string& s) const noexcept;

  ///Obtain some testing concepts
  const boost::shared_ptr<Concept> GetTest(const int i) const noexcept;
  const std::vector<boost::shared_ptr<Concept> > GetTests() const noexcept;
  int GetNumberOfTests() const noexcept { return static_cast<int>(GetTests().size()); }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCONCEPTFACTORY_H
