#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapcenternode.h"

#include "conceptmapcenternode.h"
#include "qtitemdisplaystrategy.h"
#include "qtconceptmapbrushfactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapdisplaystrategy.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtCenterNode::QtCenterNode(
  const boost::shared_ptr<ribi::cmap::CenterNode> node)
  : QtNode(node,CreateConceptItem(node))
{
  assert(node);
  assert(this->GetDisplayStrategy());
  this->setFlags(QGraphicsItem::ItemIsFocusable);
  this->GetDisplayStrategy()->SetMainBrush(QtBrushFactory::CreateGoldGradientBrush());
}

const boost::shared_ptr<ribi::cmap::QtItemDisplayStrategy> ribi::cmap::QtCenterNode::CreateConceptItem(
  const boost::shared_ptr<Node> node)
{
  assert(node);
  const boost::shared_ptr<QtDisplayStrategy> item(new QtDisplayStrategy(node->GetConcept()));
  assert(item);
  return item;
}
