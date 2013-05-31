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
#include <cassert>
//---------------------------------------------------------------------------
#include <boost/graph/graphviz.hpp>
//---------------------------------------------------------------------------
#include "statevaluegraph.h"
//---------------------------------------------------------------------------
StateValueGraph::StateValueGraph()

{
  assert(GetNumEdges()==0);
  assert(GetNumVertices()==0);
}
//---------------------------------------------------------------------------
void StateValueGraph::AddEdge(
  const int state,
  const int move,
  const int next_state)
{
  if (!VertexExists(state))
  {
    //Add vertex
    const Graph::vertex_descriptor i = boost::add_vertex(m_graph);
    m_graph[i] = StateValueVertex(state,0.0);
  }
  if (!VertexExists(next_state))
  {
    //Add vertex
    const Graph::vertex_descriptor i = boost::add_vertex(m_graph);
    m_graph[i] = StateValueVertex(next_state,0.0);
  }
  if (!EdgeExists(state,next_state))
  {
    const std::pair<Graph::vertex_iterator,Graph::vertex_iterator>
      p = boost::vertices(m_graph);
    const int sz = std::distance(p.first,p.second);

    Graph::vertex_descriptor v_state = 0;

    for (int i=0; i!=sz; ++i)
    {
      if (m_graph[i].m_state == state)
      {
        v_state = i;
        break;
      }
    }

    //Find next_state
    Graph::vertex_descriptor v_next_state = 0;
    for (int i=0; i!=sz; ++i)
    {
      if (m_graph[i].m_state == next_state)
      {
        v_next_state = i;
        break;
      }
    }
    //Add the edge
    boost::add_edge(v_state,v_next_state,StateValueEdge(move),m_graph);
  }
}
//---------------------------------------------------------------------------
bool StateValueGraph::EdgeExists(
  const int state,
  const int state_next) const
{
  assert(VertexExists(state));
  assert(VertexExists(state_next));
  const std::pair<Graph::edge_iterator,Graph::edge_iterator>
    p = boost::edges(m_graph);

  for (Graph::edge_iterator i = p.first; i!=p.second; ++i)
  {
    if ( m_graph[ boost::source(*i,m_graph) ].m_state == state
      && m_graph[ boost::target(*i,m_graph) ].m_state == state_next)
    {
      return true;
    }
  }
  return false;
  //for (int i=0; i!=sz; ++i)
  //{
  //  if (m_graph[i].m_state == state) return true;
  //}
  //return false;

}
//---------------------------------------------------------------------------
int StateValueGraph::GetNumEdges() const
{
  const std::pair<Graph::edge_iterator,Graph::edge_iterator>
    p = boost::edges(m_graph);
  return std::distance(p.first,p.second);
}
//---------------------------------------------------------------------------
int StateValueGraph::GetNumVertices() const
{
  const std::pair<Graph::vertex_iterator,Graph::vertex_iterator>
    p = boost::vertices(m_graph);
  return std::distance(p.first,p.second);
}
//---------------------------------------------------------------------------
bool StateValueGraph::VertexExists(const int state) const
{
  const std::pair<Graph::vertex_iterator,Graph::vertex_iterator>
    p = boost::vertices(m_graph);
  const int sz = std::distance(p.first,p.second);
  for (int i=0; i!=sz; ++i)
  {
    if (m_graph[i].m_state == state) return true;
  }
  return false;

}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const StateValueGraph& s)
{
  StateValueGraph& g = const_cast<StateValueGraph&>(s);
  boost::dynamic_properties p;
  p.property("label", boost::get(&StateValueEdge::m_move, g.m_graph));
  p.property("label", boost::get(&StateValueVertex::m_state, g.m_graph));
  //p.property("label", boost::get(&StateValueVertex::m_value, g.m_graph));
  p.property("node_id", boost::get(&StateValueVertex::m_state, g.m_graph));
  boost::write_graphviz(os,g.m_graph,p);
  return os;
}
//---------------------------------------------------------------------------
