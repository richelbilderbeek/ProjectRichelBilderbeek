#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtlabeledquadbezierarrowitem.h"

#include <cassert>
#include <sstream>
#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <QInputDialog>
#include <QPainter>

#include "trace.h"

QtLabeledQuadBezierArrowItem::QtLabeledQuadBezierArrowItem(
    const QGraphicsItem *const from,
    const bool tail,
    const std::string& text,
    const bool head,
    const QGraphicsItem *const to,
    QGraphicsItem *parent,
    QGraphicsScene *scene)
  : QtRoundedTextRectItem(text,QtRoundedTextRectItem::Padding(),QFont("monospace",9),parent,scene),
    m_arrow(new QtQuadBezierArrowItem(from,tail,this,head,to))
{
  assert(from);
  assert(to);
  assert(m_arrow);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->setPos(
    (from->pos().x() + to->pos().x()) * 0.49,
    (from->pos().y() + to->pos().y()) * 0.49
  );
  assert(m_arrow->GetMidItem()->pos() == this->pos());
  assert(m_arrow->GetFromItem()->pos() == from->pos());
  assert(m_arrow->GetToItem()->pos() == to->pos());
}

QRectF QtLabeledQuadBezierArrowItem::boundingRect() const
{
  return QtRoundedTextRectItem::boundingRect()
    .united(m_arrow->boundingRect().translated(-this->pos()));
}

const std::string QtLabeledQuadBezierArrowItem::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtLabeledQuadBezierArrowItem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-01-01: version 1.0: initial version");
  return v;
}

void QtLabeledQuadBezierArrowItem::keyPressEvent(QKeyEvent *event)
{
  QtRoundedTextRectItem::keyPressEvent(event);
  m_arrow->keyPressEvent(event);
}

void QtLabeledQuadBezierArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  assert(this->pos() == m_arrow->GetMidItem()->pos());
  painter->translate(-this->pos());
  m_arrow->paint(painter,option,widget);
  painter->translate(this->pos());
  QtRoundedTextRectItem::paint(painter,option,widget);
}
