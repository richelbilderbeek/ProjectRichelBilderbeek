#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapcenternodeitem.h"

#include "conceptmapcenternode.h"
#include "qtconceptitem.h"
#include "qtconceptmapbrushfactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapdisplayconceptitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtCenterNode::QtCenterNode(
  const boost::shared_ptr<ribi::cmap::Node> node)
  : QtNode(node,CreateConceptItem(node))
{
  assert( ( boost::dynamic_pointer_cast<cmap::CenterNode>(node)
        || !boost::dynamic_pointer_cast<cmap::CenterNode>(node) )
    && "Both Nodes and CenterNodes can be put in QtCenterNodeItem"
    && "CenterNode: this QtNode is the center of a ConceptMap"
    && "Node: this QtNode is the focal node of a sub ConceptMap");
  assert(node);
  assert(this->GetConceptItem());
  this->setFlags(QGraphicsItem::ItemIsFocusable);
  this->GetConceptItem()->SetMainBrush(QtBrushFactory::CreateGoldGradientBrush());
}

const boost::shared_ptr<ribi::cmap::QtConceptItem> ribi::cmap::QtCenterNode::CreateConceptItem(
  const boost::shared_ptr<ribi::cmap::Node> node)
{
  assert(node);
  const boost::shared_ptr<QtConceptMapDisplayConceptItem> item(new QtConceptMapDisplayConceptItem(node->GetConcept()));
  assert(item);
  return item;
}
