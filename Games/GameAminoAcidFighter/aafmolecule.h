#ifndef AAFMOLECULE_H
#define AAFMOLECULE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/graph/adjacency_list.hpp>
#include <boost/shared_ptr.hpp>

#include "aafatom.h"
#include "aafbond.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace aaf {

struct Molecule
{
  typedef boost::adjacency_list
  <
    //Store all edges as a std::vector
    boost::vecS,
    //Store all vertices in a std::vector
    boost::vecS,
    //Relations are both ways
    boost::undirectedS,
    //All vertices are person names of type std::string
    //boost::property<boost::vertex_name_t,std::string>,
    boost::property<boost::vertex_name_t,Atom>,
    //All edges are weights equal to the encounter frequencies
    boost::property<boost::edge_name_t,Bond>,
    //Graph itself has a std::string name
    boost::property<boost::graph_name_t,std::string>
  > Graph;

  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  //private:
  Molecule(const Graph& graph) : m_graph(graph) {}

  Graph m_graph;
};



} //~namespace aaf {
} //~namespace ribi {

#endif // AAFMOLECULE_H
