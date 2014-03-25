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
#ifndef CONCEPTMAPEXAMPLEFACTORY_H
#define CONCEPTMAPEXAMPLEFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapcompetency.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct ExampleFactory
{
  ExampleFactory() {}

  ///Create an example from string and enum
  static const boost::shared_ptr<cmap::Example> Create(
    const std::string& text,
    const cmap::Competency& competency,
    const bool is_complex = true,   //DEFAULT
    const bool is_concrete = true,  //DEFAULT
    const bool is_specific = true); //DEFAULT

  ///Create examples for strings
  ///Note that all cmap::Competency values are set to uninitialized
  //static const std::vector<boost::shared_ptr<cmap::Example> > CreateExamples(const std::vector<std::string>& v);

  ///Create an example from XML
  static const boost::shared_ptr<cmap::Example> FromXml(const std::string& s);

  int GetNumberOfTests() const noexcept { return static_cast<int>(GetTests().size()); }
  const boost::shared_ptr<Example> GetTest(const int i) const noexcept;
  const std::vector<boost::shared_ptr<Example>> GetTests() const noexcept;

};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEXAMPLEFACTORY_H
