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
#ifndef CONCEPTMAPCOMMANDSETSELECTEDWITHCOORDINAT_H
#define CONCEPTMAPCOMMANDSETSELECTEDWITHCOORDINAT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>

#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Set selected with a coordinat
///- opposite of LoseSelected
///- SetSelected does not care if there currently something else is selected
struct CommandSetSelectedWithCoordinat : public Command
{
  using ConstEdges = std::vector<boost::shared_ptr<const Edge>>;
  using ConstNodes = std::vector<boost::shared_ptr<const Node>>;
  using Edges = std::vector<boost::shared_ptr<Edge>>;
  using Nodes = std::vector<boost::shared_ptr<Node>>;
  using EdgesAndNodes = std::pair<Edges,Nodes>;
  using ConstEdgesAndNodes = std::pair<ConstEdges,ConstNodes>;

  CommandSetSelectedWithCoordinat(const int x, const int y)
    : m_prev_selected{}, m_widget{}, m_x(x), m_y(y) {}
  CommandSetSelectedWithCoordinat(const CommandSetSelectedWithCoordinat&) = delete;
  CommandSetSelectedWithCoordinat& operator=(const CommandSetSelectedWithCoordinat&) = delete;
  ~CommandSetSelectedWithCoordinat() noexcept {}

  std::string ToStr() const noexcept final { return "set focus with coordinat"; }

  private:
  ConstEdgesAndNodes m_prev_selected;
  ConceptMap * m_widget;

  const int m_x;
  const int m_y;

  bool CanDoCommandSpecific(const ConceptMap * const widget) const noexcept final;
  void DoCommandSpecific(ConceptMap * const widget) noexcept final;
  void UndoSpecific() noexcept final;
};

} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMANDSETSELECTEDWITHCOORDINAT_H
