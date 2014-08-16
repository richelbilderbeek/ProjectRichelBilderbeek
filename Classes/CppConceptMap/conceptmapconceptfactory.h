//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
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
  ConceptFactory() noexcept;

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
