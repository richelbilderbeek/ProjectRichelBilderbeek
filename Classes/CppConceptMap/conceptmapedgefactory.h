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
#ifndef CONCEPTMAPEDGEFACTORY_H
#define CONCEPTMAPEDGEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct EdgeFactory
{
  EdgeFactory() noexcept;

  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef boost::shared_ptr<const Edge> ReadOnlyEdge;
  typedef boost::shared_ptr<Node> NodePtr;
  typedef boost::shared_ptr<const Node> ReadOnlyNode;
  typedef std::vector<EdgePtr> Edges;
  typedef std::vector<NodePtr> Nodes;

  EdgePtr Create(
    const NodePtr& from,
    const NodePtr& to
  ) const noexcept;

  EdgePtr Create(
    const NodePtr& node,
    const NodePtr& from,
    const bool tail_arrow,
    const NodePtr& to,
    const bool head_arrow
  ) const noexcept;

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  ///The nodes need to be the deepcopied ones
  EdgePtr DeepCopy(
    const ReadOnlyEdge& edge,
    const NodePtr& from,
    const NodePtr& to
  ) const noexcept;
  #endif

  ///Obtain an Edge from an XML std::string
  ///You need the real nodes to connect the edge to
  EdgePtr FromXml(
    const std::string& s,
    const Nodes& nodes
  ) const noexcept;


  int GetNumberOfTests() const noexcept;

  EdgePtr GetTest(
    const int index,
    const NodePtr& from,
    const NodePtr& to
 ) const noexcept;

  ///Get testing edges connecting the two supplied nodes
  Edges GetTests(
    const NodePtr& from,
    const NodePtr& to
  ) const noexcept;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEDGEFACTORY_H
