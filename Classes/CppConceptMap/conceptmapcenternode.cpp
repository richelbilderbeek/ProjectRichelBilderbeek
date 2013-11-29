#include "conceptmapcenternode.h"

ribi::cmap::CenterNode::CenterNode(
    const boost::shared_ptr<ribi::cmap::Concept>& concept,
    const double x,
    const double y)
  : Node(concept,x,y)
{

}
