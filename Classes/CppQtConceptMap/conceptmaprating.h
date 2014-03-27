//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
#ifndef QTCONCEPTMAPRATING_H
#define QTCONCEPTMAPRATING_H

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
  static int SuggestComplexity(const boost::shared_ptr<const ConceptMap> m_sub_concept_map);

  ///Calculate a suggested concreteness
  static int SuggestConcreteness(const int n_examples);

  ///Calculate a suggested concreteness
  static int SuggestConcreteness(const boost::shared_ptr<const ConceptMap> m_sub_concept_map);

  ///Calculate a suggested specificity
  static int SuggestSpecificity(const int n_examples);

  ///Calculate a suggested specificity
  static int SuggestSpecificity(const boost::shared_ptr<const ConceptMap> m_sub_concept_map);
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTCONCEPTMAPRATING_H
