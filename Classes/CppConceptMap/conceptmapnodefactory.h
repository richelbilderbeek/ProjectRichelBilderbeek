//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
#ifndef CONCEPTMAPNODEFACTORY_H
#define CONCEPTMAPNODEFACTORY_H

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

struct Node;

///Factory for creating Node instances
struct NodeFactory
{
  NodeFactory();

  boost::shared_ptr<Node> Create(
    const boost::shared_ptr<Concept>& concept,
    const double x = 0.0,
    const double y = 0.0
  ) const noexcept;

  boost::shared_ptr<Node> CreateFromStrings(
    const std::string& name,
    const std::vector<std::pair<std::string,Competency> >& examples = {},
    const double x = 0.0,
    const double y = 0.0
  ) const noexcept;

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  boost::shared_ptr<Node> DeepCopy(
    const boost::shared_ptr<const cmap::Node>& node
  ) const noexcept;
  #endif

  ///Obtain a Node or CenterNode from an XML std::string
  boost::shared_ptr<Node> FromXml(const std::string& s) const noexcept;

  ///Obtain testing nodes
  int GetNumberOfTests() const noexcept;
  std::vector<boost::shared_ptr<Node>> GetTests() const noexcept;
  boost::shared_ptr<Node> GetTest(const int test) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPNODEFACTORY_H
