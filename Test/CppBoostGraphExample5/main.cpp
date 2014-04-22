#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#pragma GCC diagnostic pop

//Define the type of graph:
//boost::adjacency_list is the 'Swiss army knife' graph
typedef boost::adjacency_list
<
  //Store all edges as a std::vector
  boost::vecS,
  //Store all vertices in a std::vector
  boost::vecS,
  //Relations are both ways (in this example)
  //(note: but you can freely change it to boost::directedS)
  boost::undirectedS,
  //All vertices are person names of type std::string
  boost::property<boost::vertex_name_t,std::string>,
  //All edges are weights equal to the encounter frequencies
  boost::property<boost::edge_weight_t,double>,
  //Graph itself has a std::string name
  boost::property<boost::graph_name_t,std::string>
> Graph;


Graph Create()
{

  Graph g;

  //All vertex names
  //Note: cannot use spaces
  std::vector<std::string> names;
  names.push_back("Mr_A");
  names.push_back("Mrs_B");
  names.push_back("Dr_C");
  names.push_back("Prof_D");

  const Graph::vertex_descriptor v0 = boost::add_vertex(names[0],g);
  const Graph::vertex_descriptor v1 = boost::add_vertex(names[1],g);
  const Graph::vertex_descriptor v2 = boost::add_vertex(names[2],g);
  const Graph::vertex_descriptor v3 = boost::add_vertex(names[3],g);

  std::vector<double> frequencies;
  frequencies.push_back(0.9);
  frequencies.push_back(0.5);
  frequencies.push_back(0.6);
  frequencies.push_back(0.1);

  boost::add_edge(v0,v1,frequencies[0],g);
  boost::add_edge(v1,v2,frequencies[1],g);
  boost::add_edge(v2,v3,frequencies[2],g);
  boost::add_edge(v0,v3,frequencies[3],g);

  return g;
}


class custom_bfs_visitor : public boost::default_bfs_visitor
{
public:

  template < typename Vertex, typename Graph >
  void discover_vertex(Vertex u, const Graph & g) const
  {
    std::cout << u << std::endl;
  }
};

int main()
{
  const auto g(Create());
  Create().named_vertices()
  TODO: Iterate over nodes
}
