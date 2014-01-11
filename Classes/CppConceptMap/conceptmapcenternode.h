#ifndef CONCEPTMAPCENTERNODE_H
#define CONCEPTMAPCENTERNODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapnode.h"
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct CenterNodeFactory;

///The focal question of a ConceptMap
///In a full ConceptMap, GetNodes()[0] results in finding a CenterNode
///In a sub-ConceptMap, GetNodes()[0] will be a regular Node
struct CenterNode : public Node
{
  ///Block destructor, except for the friend boost::checked_delete
  ~CenterNode() noexcept {}
  friend void boost::checked_delete<>(CenterNode* x);

  ///Block construction, except for NodeFactory
  friend CenterNodeFactory;
  CenterNode() = delete;
  explicit CenterNode(
    const boost::shared_ptr<Concept>& concept,
    const double x = 0.0,
    const double y = 0.0);
};

///Returns true if Node is of derived class type CenterNode
///Returns true if Node is Node
bool IsCenterNode(const boost::shared_ptr<const Node> node) noexcept;

} //~namespace cmap

} //~namespace ribi

#endif // CONCEPTMAPCENTERNODE_H
