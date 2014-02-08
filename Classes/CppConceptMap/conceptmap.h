#ifndef CONCEPTMAPCONCEPTMAP_H
#define CONCEPTMAPCONCEPTMAP_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct ConceptMapFactory;

///A concept map
///Its interface is based on nodes and edges
///Use ConceptMapWidget to work with commands
struct ConceptMap
{
  ConceptMap(const ConceptMap&) = delete;
  ConceptMap& operator=(const ConceptMap&) = delete;

  //Add an Edge, assumes that the nodes it points to are in the concept map
  void AddEdge(const boost::shared_ptr<Edge> edge);

  //Add a node, always works
  void AddNode(const boost::shared_ptr<Node> node);

  ///Test if this ConceptMap can be constructed successfully
  static bool CanConstruct(
    const std::vector<boost::shared_ptr<Node> >& nodes,
    const std::vector<boost::shared_ptr<Edge> >& edges);

  ///Prepend the question as a first node, before adding the supplied nodes
  static const std::vector<boost::shared_ptr<Node> > CreateNodes(
    const std::string& question,
    const std::vector<boost::shared_ptr<Node> >& nodes);

  ///Create all sub-conceptmaps
  ///Note that CreateSubs()[0] is the concept map around the focal question
  const std::vector<boost::shared_ptr<ConceptMap> > CreateSubs() const;

  ///Delete an edge
  void DeleteEdge(const boost::shared_ptr<Edge> edge);

  ///Delete a node and all the edges connected to it
  void DeleteNode(const boost::shared_ptr<Node> node);

  ///Check if the ConceptMap is empty
  bool Empty() const;

  ///Find the CenterNode, if any
  const boost::shared_ptr<const CenterNode> FindCenterNode() const noexcept;
  const boost::shared_ptr<      CenterNode> FindCenterNode()       noexcept;

  ///Get the edges
  const std::vector<boost::shared_ptr<const Edge> >  GetEdges() const;
  const std::vector<boost::shared_ptr<      Edge> >& GetEdges() { return m_edges; }

  ///Get the focal node (always at index zero)
  const boost::shared_ptr<const Node> GetFocalNode() const noexcept;
  const boost::shared_ptr<      Node> GetFocalNode()       noexcept;

  ///Get the nodes
  const std::vector<boost::shared_ptr<const Node> >  GetNodes() const;
  const std::vector<boost::shared_ptr<      Node> >& GetNodes() { return m_nodes; }

  ///Get the focus question
  ///TODO: remove this member function, use GetCenterNode instead
  const std::string GetQuestion() const noexcept;

  ///Obtain the version
  static const std::string GetVersion() noexcept;

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Similar to operator==, except that the GUI member variables aren't checked for equality
  static bool HasSameContent(const ConceptMap& lhs, const ConceptMap& rhs);

  #ifndef NDEBUG
  ///Check if there are no nulls in the edges and nodes
  bool IsValid() const;
  #endif

  ///Convert a ConceptMap from an XML std::string
  static const std::string ToXml(const boost::shared_ptr<const ConceptMap> c);

private:

  ///The edges
  std::vector<boost::shared_ptr<Edge> > m_edges;

  ///The nodes
  std::vector<boost::shared_ptr<Node> > m_nodes;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Block constructor, except for the friend ConceptMapFactory
  ConceptMap(const std::string& question);
  //Nodes[0] must be the focal question
  ConceptMap(
    const std::vector<boost::shared_ptr<Node> >& nodes = {},
    const std::vector<boost::shared_ptr<Edge> >& edges = {});
  ///Create a concept map from a cluster
  #ifdef TO_ADD_TO_PROJECTBRAINWEAVER
  ConceptMap(
    const std::string& question,
    const boost::shared_ptr<cmap::Cluster>& cluster);
  #endif

  ///To make the compiler use the const version
  const boost::shared_ptr<const CenterNode> FindCenterNodeConst() const noexcept { return FindCenterNode(); }
  ///To make the compiler use the const version
  const boost::shared_ptr<const Node> GetFocalNodeConst() const noexcept { return GetFocalNode(); }

  friend ConceptMapFactory;
  ///Block destructor, except for the friend boost::checked_delete
  ~ConceptMap() {}
  friend void boost::checked_delete<>(ConceptMap* x);
};

///Count the number of CenterNodes
///- regular concept map: 1, the focus
///- sub-concept map: 0 or 1, if the focus is connected to the sub's focus node
int CountCenterNodes(const boost::shared_ptr<const ConceptMap> conceptmap) noexcept;

///Count the number of Edges connected to a CenterNodes
int CountCenterNodeEdges(const boost::shared_ptr<const ConceptMap> conceptmap) noexcept;

bool operator==(const ConceptMap& lhs, const ConceptMap& rhs);
bool operator!=(const ConceptMap& lhs, const ConceptMap& rhs);

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCONCEPTMAP_H
