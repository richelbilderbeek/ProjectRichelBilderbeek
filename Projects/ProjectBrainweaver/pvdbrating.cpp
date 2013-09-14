#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "pvdbrating.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

#include "pvdbconceptmap.h"
#include "pvdbnode.h"
#include "pvdbconcept.h"
#include "pvdbexamples.h"
#pragma GCC diagnostic pop

int ribi::pvdb::Rating::SuggestComplexity(const int n_edges, const int n_examples)
{
  const int complexity
    = n_edges == 0  || (n_edges == 1 && n_examples == 0)
    ? 0
    : (n_edges == 1 && n_examples > 0) || (n_edges == 2 && n_examples == 0)
      ? 1
      : 2;
  return complexity;
}

int ribi::pvdb::Rating::SuggestComplexity(const boost::shared_ptr<const ribi::pvdb::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  const int n_edges = boost::numeric_cast<int>(sub_concept_map->GetEdges().size());
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestComplexity(n_edges,n_examples);
}

int ribi::pvdb::Rating::SuggestConcreteness(const int n_examples)
{
  const int concreteness
    = n_examples < 2
    ? 0
    : n_examples > 1 && n_examples < 4
      ? 1
      : 2;
  return concreteness;
}

int ribi::pvdb::Rating::SuggestConcreteness(const boost::shared_ptr<const ribi::pvdb::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestConcreteness(n_examples);
}

int ribi::pvdb::Rating::SuggestSpecificity(const int n_examples)
{
  const int specificity = SuggestConcreteness(n_examples);
  return specificity;
}

int ribi::pvdb::Rating::SuggestSpecificity(const boost::shared_ptr<const ribi::pvdb::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestSpecificity(n_examples);
}
