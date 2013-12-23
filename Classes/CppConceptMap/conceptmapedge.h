#ifndef CONCEPTMAPEDGE_H
#define CONCEPTMAPEDGE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "conceptmapfwd.h"
#include "conceptmapelement.h"
#pragma GCC diagnostic pop


namespace ribi {
namespace cmap {

struct EdgeFactory;

///An Edge is the GUI-independent part of the edges used in QtConceptMap.
///An Edge goes from one Node to another, which must a different Node
struct Edge : public Element
{
  Edge(const Edge&) = delete;
  Edge& operator=(const Edge&) = delete;
  const boost::shared_ptr<const ribi::cmap::Concept> GetConcept() const { return m_concept; }
  const boost::shared_ptr< ribi::cmap::Concept> GetConcept() { return m_concept; }

  ///Get the Node this edge originates from
  const boost::shared_ptr<const cmap::Node> GetFrom() const { return m_from; }
  const boost::shared_ptr< cmap::Node> GetFrom() { return m_from; }

  ///Get the Node index this edge goes to
  const boost::shared_ptr<const cmap::Node> GetTo() const { return m_to; }
  const boost::shared_ptr< cmap::Node> GetTo() { return m_to; }

  ///Get the x coordinat
  double GetX() const { return m_x; }

  ///Get the y coordinat
  double GetY() const { return m_y; }

  ///Does the edge have an arrow at the head?
  bool HasHeadArrow() const { return m_head_arrow; }

  //Similar to operator==, except that the coordinats are not checked
  static bool HasSameContent(const boost::shared_ptr<const cmap::Edge>& lhs, const boost::shared_ptr<const cmap::Edge>& rhs);

  ///Does the edge have an arrow at the tail?
  bool HasTailArrow() const { return m_tail_arrow; }

  ///Set the concept
  void SetConcept(const boost::shared_ptr<ribi::cmap::Concept> concept) { m_concept = concept; }

  ///Set the Node index this edge originates from
  void SetFrom(const boost::shared_ptr<ribi::cmap::Node> from);

  ///Set if the head has an arrow
  void SetHeadArrow(const bool has_head_arrow);

  ///Set the coordinat of the concept at the center of the node
  void SetPos(const double x, const double y) { SetX(x); SetY(y); }

  ///Set if the tail has an arrow
  void SetTailArrow(const bool has_tail_arrow);

  ///Set the Node index this edge goes to
  void SetTo(const boost::shared_ptr<ribi::cmap::Node> to);

  ///Set the x coordinat of the concept at the center of the node
  void SetX(const double x);

  ///Set the y coordinat of the concept at the center of the node
  void SetY(const double y);

  ///Convert an Edge from an XML std::string
  ///The container of nodes is needed to convert the 'to' and 'from'
  ///field to indices
  static const std::string ToXml(
    const boost::shared_ptr<const cmap::Edge>& c,
    const std::vector<boost::shared_ptr<const cmap::Node> >& nodes
    );

  ///Emitted when an Edge attribute has changed
  boost::signals2::signal<void (const Edge*)> m_signal_edge_changed;

  private:

  ///The Concept on the Edge
  boost::shared_ptr<ribi::cmap::Concept> m_concept;

  ///The Node index this edge originates from
  ///Cannot be an index, see [1] below
  boost::shared_ptr<ribi::cmap::Node> m_from;

  ///Is there an arrowhead at the 'to' node?
  bool m_head_arrow;

  ///Is there an arrowhead at the 'from' node?
  bool m_tail_arrow;

  ///The Node index this edge goes to
  ///Cannot be an index, see [1] below
  boost::shared_ptr<ribi::cmap::Node> m_to;

  ///The x-coordinat
  double m_x;

  ///The y-coordinat
  double m_y;

  void EmitSignalEdgeChanged();

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  Edge() = delete;

  ///Block destructor, except for the friend boost::checked_delete
  ~Edge() {}
  friend void boost::checked_delete<>(Edge* x);

  ///Block constructor, except for EdgeFactory
  friend EdgeFactory;
  Edge(
    const boost::shared_ptr<ribi::cmap::Concept> & concept,
    const double concept_x,
    const double concept_y,
    const boost::shared_ptr<ribi::cmap::Node> from,
    const bool tail_arrow,
    const boost::shared_ptr<ribi::cmap::Node> to,
    const bool head_arrow);

};

bool operator==(const cmap::Edge& lhs, const cmap::Edge& rhs);

///Notes:
/// [1] Node::m_from and Node::m_to cannot be indices, because of the desired copying behavior
/// of Edge: when copying an edge, it is natural that it keeps pointing to the same nodes.
/// When using pointers, this will work. Indices, on the other hand, are context-specific:
/// Example: imagine a concept map like this:
///
/// NodeA Edge1 NodeB Edge2 NodeC
/// [0] [1] [2]
///
/// In this example, Edge2 goes from [1] to [2]
///
/// A sub-concept map will be (when NodeC is the focal node):
///
/// NodeB Edge2 NodeC
/// [0] [1]
///
/// In this example, Edge2 goes from [0] to [1]! Due to this, the same Edge2 cannot behave identical in the different contexts
///
/// Indices are only used when saving and loading

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEDGE_H
