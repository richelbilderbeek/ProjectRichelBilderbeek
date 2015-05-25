//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaprating.h"

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
  assert(sub_concept_map->GetFocalNode()->GetConcept());
  assert(sub_concept_map->GetFocalNode()->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetFocalNode()->GetConcept()->GetExamples()->Get().size()
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
  assert(sub_concept_map->GetFocalNode()->GetConcept());
  assert(sub_concept_map->GetFocalNode()->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetFocalNode()->GetConcept()->GetExamples()->Get().size()
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
  assert(sub_concept_map->GetFocalNode()->GetConcept());
  assert(sub_concept_map->GetFocalNode()->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetFocalNode()->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestSpecificity(n_examples);
}
