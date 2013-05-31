#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbcenternodeitem.h"

#include "qtpvdbconceptitem.h"
#include "qtpvdbbrushfactory.h"
#include "pvdbnode.h"
#include "qtpvdbdisplayconceptitem.h"

QtPvdbCenterNodeItem::QtPvdbCenterNodeItem(
  const boost::shared_ptr<pvdb::Node>& node)
  : QtPvdbNodeItem(node,CreateConceptItem(node))
{
  assert(node);
  assert(this->GetConceptItem());
  this->setFlags(QGraphicsItem::ItemIsFocusable);
  this->GetConceptItem()->SetMainBrush(QtPvdbBrushFactory::CreateGoldGradientBrush());
}

const boost::shared_ptr<QtPvdbConceptItem> QtPvdbCenterNodeItem::CreateConceptItem(
  const boost::shared_ptr<pvdb::Node>& node)
{
  assert(node);
  const boost::shared_ptr<QtPvdbConceptItem> item(new QtPvdbDisplayConceptItem(node->GetConcept()));
  assert(item);
  return item;
}
