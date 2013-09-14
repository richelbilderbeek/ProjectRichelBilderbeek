#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbcenternodeitem.h"

#include "pvdbcenternode.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbbrushfactory.h"
#include "pvdbnode.h"
#include "qtpvdbdisplayconceptitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbCenterNodeItem::QtPvdbCenterNodeItem(
  const boost::shared_ptr<ribi::pvdb::Node> node)
  : QtPvdbNodeItem(node,CreateConceptItem(node))
{
  assert( ( boost::dynamic_pointer_cast<pvdb::CenterNode>(node)
        || !boost::dynamic_pointer_cast<pvdb::CenterNode>(node) )
    && "Both Nodes and CenterNodes can be put in QtCenterNodeItem"
    && "CenterNode: this QtNode is the center of a ConceptMap"
    && "Node: this QtNode is the focal node of a sub ConceptMap");
  assert(node);
  assert(this->GetConceptItem());
  this->setFlags(QGraphicsItem::ItemIsFocusable);
  this->GetConceptItem()->SetMainBrush(QtPvdbBrushFactory::CreateGoldGradientBrush());
}

const boost::shared_ptr<ribi::pvdb::QtPvdbConceptItem> ribi::pvdb::QtPvdbCenterNodeItem::CreateConceptItem(
  const boost::shared_ptr<ribi::pvdb::Node> node)
{
  assert(node);
  const boost::shared_ptr<QtPvdbConceptItem> item(new QtPvdbDisplayConceptItem(node->GetConcept()));
  assert(item);
  return item;
}
