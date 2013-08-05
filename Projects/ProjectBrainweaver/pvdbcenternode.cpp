#include "pvdbcenternode.h"

namespace pvdb {

CenterNode::CenterNode(
    const boost::shared_ptr<pvdb::Concept>& concept,
    const double x,
    const double y)
  : Node(concept,x,y)
{

}

} //~namespace pvdb
