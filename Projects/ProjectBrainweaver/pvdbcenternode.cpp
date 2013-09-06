#include "pvdbcenternode.h"

ribi::pvdb::CenterNode::CenterNode(
    const boost::shared_ptr<ribi::pvdb::Concept>& concept,
    const double x,
    const double y)
  : Node(concept,x,y)
{

}
