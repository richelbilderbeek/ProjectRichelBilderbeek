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
//#ifdef NOT_NOW_2014_08_11

#ifndef CONCEPTMAPCONCEPTMAPFACTORY_H
#define CONCEPTMAPCONCEPTMAPFACTORY_H

#include <array>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace cmap {

///Factory class to create ConceptMaps
///ConceptMapFactory is the only class using the ConceptMap constructor
struct ConceptMapFactory
{
  typedef std::vector<boost::shared_ptr<Node>> Nodes;
  typedef std::vector<boost::shared_ptr<Edge>> Edges;
  typedef std::vector<boost::shared_ptr<ConceptMap>> ConceptMaps;

  ConceptMapFactory() noexcept;

  boost::shared_ptr<ConceptMap> Create(
    const Nodes& nodes = {},
    const Edges& edges = {}
  ) const noexcept;

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  boost::shared_ptr<ConceptMap> DeepCopy(
    const boost::shared_ptr<const ConceptMap> map
  ) const noexcept;
  #endif

  ///Obtain a ConceptMap from an XML std::string
  boost::shared_ptr<ConceptMap> FromXml(const std::string& s) const noexcept;

  ///Get all the other tests as one vector
  ConceptMaps GetAllTests() const noexcept;

  ///Get the documented heteromorphous test concept maps
  ConceptMaps GetHeteromorphousTestConceptMaps() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap(const int index) const noexcept;

  ///Get the documented complex homomorphous test concept maps
  ConceptMaps GetComplexHomomorphousTestConceptMaps() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap(const int index) const noexcept;
  int GetNumberOfComplexHomomorphousTestConceptMaps() const noexcept { return 12; }

  ///Get the documented simple homomorphous test concept maps
   ConceptMaps GetSimpleHomomorphousTestConceptMaps() const noexcept;

  private:
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap0() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap1() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap2() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap3() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap4() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap5() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap6() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap7() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap8() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap9() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap10() const noexcept;
  boost::shared_ptr<ConceptMap> GetComplexHomomorphousTestConceptMap11() const noexcept;

  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap0() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap1() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap2() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap3() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap4() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap5() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap6() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap7() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap8() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap9() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap10() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap11() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap12() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap13() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap14() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap15() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap16() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap17() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap18() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap19() const noexcept;
  boost::shared_ptr<ConceptMap> GetHeteromorphousTestConceptMap20() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPCONCEPTMAPFACTORY_H

//#endif // NOT_NOW_2014_08_11
