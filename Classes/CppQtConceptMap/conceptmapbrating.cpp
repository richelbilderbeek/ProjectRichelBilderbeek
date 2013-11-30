#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmaprating.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

#include "conceptmap.h"
#include "conceptmapnode.h"
#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#pragma GCC diagnostic pop

int ribi::cmap::Rating::SuggestComplexity(const int n_edges, const int n_examples)
{
  const int complexity
    = n_edges == 0  || (n_edges == 1 && n_examples == 0)
    ? 0
    : (n_edges == 1 && n_examples > 0) || (n_edges == 2 && n_examples == 0)
      ? 1
      : 2;
  return complexity;
}

int ribi::cmap::Rating::SuggestComplexity(const boost::shared_ptr<const ribi::cmap::ConceptMap> sub_concept_map)
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

int ribi::cmap::Rating::SuggestConcreteness(const int n_examples)
{
  const int concreteness
    = n_examples < 2
    ? 0
    : n_examples > 1 && n_examples < 4
      ? 1
      : 2;
  return concreteness;
}

int ribi::cmap::Rating::SuggestConcreteness(const boost::shared_ptr<const ribi::cmap::ConceptMap> sub_concept_map)
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

int ribi::cmap::Rating::SuggestSpecificity(const int n_examples)
{
  const int specificity = SuggestConcreteness(n_examples);
  return specificity;
}

int ribi::cmap::Rating::SuggestSpecificity(const boost::shared_ptr<const ribi::cmap::ConceptMap> sub_concept_map)
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
