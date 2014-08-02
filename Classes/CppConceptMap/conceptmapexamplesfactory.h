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
#ifndef CONCEPTMAPEXAMPLESFACTORY_H
#define CONCEPTMAPEXAMPLESFACTORY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapcompetency.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace cmap {

struct ExamplesFactory
{
  ExamplesFactory() noexcept;

  ///Constructor like
  static const boost::shared_ptr<Examples> Create();

  ///Copy-constructor like
  static const boost::shared_ptr<Examples> Create(
    const boost::shared_ptr<const cmap::Examples>& examples);

  static const boost::shared_ptr<Examples> Create(
    const std::vector<boost::shared_ptr<cmap::Example> >& v);

  static const boost::shared_ptr<Examples> Create(
    const std::vector<boost::shared_ptr<const cmap::Example> >& v);

  static const boost::shared_ptr<Examples> Create(
    const std::vector<std::pair<std::string,Competency> >& v);

  ///Create an Examples from XML
  const boost::shared_ptr<Examples> FromXml(const std::string& s) const;

  int GetNumberOfTests() const noexcept { return static_cast<int>(GetTests().size()); }
  const boost::shared_ptr<Examples> GetTest(const int i) const noexcept;
  const std::vector<boost::shared_ptr<Examples>> GetTests() const noexcept;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif // NDEBUG
};

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPEXAMPLESFACTORY_H
