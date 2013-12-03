#ifndef CONCEPTMAPRATING_H
#define CONCEPTMAPRATING_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Functions to help with rating
struct Rating
{
  ///Calculate a suggested complexity
  static int SuggestComplexity(const int n_edges, const int n_examples);

  ///Calculate a suggested complexity
  static int SuggestComplexity(const boost::shared_ptr<const ribi::cmap::ConceptMap> m_sub_concept_map);

  ///Calculate a suggested concreteness
  static int SuggestConcreteness(const int n_examples);

  ///Calculate a suggested concreteness
  static int SuggestConcreteness(const boost::shared_ptr<const ribi::cmap::ConceptMap> m_sub_concept_map);

  ///Calculate a suggested specificity
  static int SuggestSpecificity(const int n_examples);

  ///Calculate a suggested specificity
  static int SuggestSpecificity(const boost::shared_ptr<const ribi::cmap::ConceptMap> m_sub_concept_map);
};

} //~namespace pvdb
} //~namespace ribi

#endif // CONCEPTMAPRATING_H
