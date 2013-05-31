//---------------------------------------------------------------------------
/*
TicTacToeValuer, tool to solve TicTacToe
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTicTacToeValuer.htm
//---------------------------------------------------------------------------
#ifndef STATEVALUEGRAPH_H
#define STATEVALUEGRAPH_H
//---------------------------------------------------------------------------
#include <iosfwd>
//---------------------------------------------------------------------------
#include <boost/graph/adjacency_list.hpp>
//---------------------------------------------------------------------------
#include "statevalueedge.h"
#include "statevaluevertex.h"
//---------------------------------------------------------------------------
struct StateValueGraph
{
  StateValueGraph();
  int GetNumEdges() const;
  int GetNumVertices() const;
  void AddEdge(
    const int state,
    const int move,
    const int next_state);

  private:

  typedef boost::adjacency_list
  <
    //Store all edges as a std::vector
    boost::vecS,
    //Store all vertices in a std::vector
    boost::vecS,
    //Relations are both ways (in this example)
    //(note: but you can freely change it to boost::directedS)
    boost::directedS,
    //All vertices are of state StateValueVertex
    StateValueVertex,
    //All edges are simple
    StateValueEdge,
    //Graph itself has a std::string name
    boost::no_property
  > Graph;

  Graph m_graph;

  bool EdgeExists(const int state, const int state_next) const;

  bool VertexExists(const int state) const;

  friend std::ostream& operator<<(std::ostream&,const StateValueGraph&);
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const StateValueGraph& s);
//---------------------------------------------------------------------------
#endif // STATEVALUEGRAPH_H
