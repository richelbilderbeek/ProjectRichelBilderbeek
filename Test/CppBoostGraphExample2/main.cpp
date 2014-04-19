#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#pragma GCC diagnostic pop
int main()
{
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
    //All edges are relation of type std::string
    boost::property<boost::edge_name_t,std::string>
  > Graph;

  Graph  g;

  std::vector<std::string> names;
  names.push_back("Mr. A");
  names.push_back("Mrs. B");
  names.push_back("Dr. C");
  names.push_back("Prof. D");

  const Graph::vertex_descriptor v0 = boost::add_vertex(names[0],g);
  const Graph::vertex_descriptor v1 = boost::add_vertex(names[1],g);
  const Graph::vertex_descriptor v2 = boost::add_vertex(names[2],g);
  const Graph::vertex_descriptor v3 = boost::add_vertex(names[3],g);

  std::vector<std::string> relations;
  relations.push_back("Married");
  relations.push_back("Lovers");
  relations.push_back("Collegues");
  relations.push_back("Roommates");

  boost::add_edge(v0,v1,relations[0],g);
  boost::add_edge(v1,v2,relations[1],g);
  boost::add_edge(v2,v3,relations[2],g);
  boost::add_edge(v0,v3,relations[3],g);

  //Writing graph to file
  {
    std::ofstream f("test.dot");
    //Problems:
    //- All relationships are omitted
    boost::write_graphviz(
      f,
      g,
      boost::make_label_writer(&(names[0])));
    f.close();
  }

  //View the output directly using KGraphViewerer
  std::system("kgraphviewer test.dot");
}
