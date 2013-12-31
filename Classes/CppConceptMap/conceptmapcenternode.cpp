#include "conceptmapcenternode.h"

#include <cassert>

ribi::cmap::CenterNode::CenterNode(
    const boost::shared_ptr<ribi::cmap::Concept>& concept,
    const double x,
    const double y)
  : Node(concept,x,y)
{

}

bool ribi::cmap::IsCenterNode(const boost::shared_ptr<const ribi::cmap::Node> node) noexcept
{
  assert(node);
  return boost::dynamic_pointer_cast<const CenterNode>(node).get();
}
