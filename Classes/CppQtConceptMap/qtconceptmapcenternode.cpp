//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
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
  const boost::shared_ptr<CenterNode> node
)
  : QtNode(node)
{
  assert(node);
  //assert(this->GetDisplayStrategy());
  this->setFlags(QGraphicsItem::ItemIsFocusable);
  //this->GetDisplayStrategy()->SetMainBrush(QtBrushFactory::CreateGoldGradientBrush());
}

/*
const boost::shared_ptr<ribi::cmap::QtItemDisplayStrategy> ribi::cmap::QtCenterNode::CreateConceptItem(
  const boost::shared_ptr<Node> node)
{
  assert(node);
  const boost::shared_ptr<QtDisplayStrategy> item(new QtDisplayStrategy(node->GetConcept()));
  assert(item);
  return item;
}
*/
