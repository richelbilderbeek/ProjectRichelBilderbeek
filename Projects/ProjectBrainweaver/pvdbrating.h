#ifndef PVDBRATING_H
#define PVDBRATING_H

#include <boost/shared_ptr.hpp>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif

namespace pvdb {

///Functions to help with rating
struct Rating
{
  ///Calculate a suggested complexity
  static int SuggestComplexity(const int n_edges, const int n_examples);

  ///Calculate a suggested complexity
  static int SuggestComplexity(const boost::shared_ptr<const pvdb::ConceptMap> m_sub_concept_map);

  ///Calculate a suggested concreteness
  static int SuggestConcreteness(const int n_examples);

  ///Calculate a suggested concreteness
  static int SuggestConcreteness(const boost::shared_ptr<const pvdb::ConceptMap> m_sub_concept_map);

  ///Calculate a suggested specificity
  static int SuggestSpecificity(const int n_example);

  ///Calculate a suggested specificity
  static int SuggestSpecificity(const boost::shared_ptr<const pvdb::ConceptMap> m_sub_concept_map);
};

} //~namespace pvdb

#endif // PVDBRATING_H
