#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtlabeledquadbezierarrowitem.h"

#include <cassert>
#include <sstream>
#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <QInputDialog>
#include <QPainter>

#include "qtquadbezierarrowitem.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtLabeledQuadBezierArrowItem::QtLabeledQuadBezierArrowItem(
    const QGraphicsItem *const from,
    const bool tail,
    const std::string& text,
    const bool head,
    const QGraphicsItem *const to,
    QGraphicsItem *parent)
  : QtRoundedEditRectItem( {text} ,QtRoundedEditRectItem::Padding(),QFont("monospace",9),parent),
    m_arrow(new QtQuadBezierArrowItem(from,tail,this,head,to))
{
  assert(from);
  assert(to);
  assert(m_arrow);
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->SetPos(
    (from->pos().x() + to->pos().x()) * 0.49,
    (from->pos().y() + to->pos().y()) * 0.49
  );
  assert(m_arrow->GetMidItem());
  assert(m_arrow->GetMidItem()->pos() == this->GetPos());
  assert(m_arrow->GetFromItem()->pos() == from->pos());
  assert(m_arrow->GetToItem()->pos() == to->pos());
}

QRectF ribi::QtLabeledQuadBezierArrowItem::boundingRect() const noexcept
{
  return QtRoundedEditRectItem::boundingRect()
    .united(m_arrow->boundingRect().translated(-this->GetPos()));
}

std::string ribi::QtLabeledQuadBezierArrowItem::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtLabeledQuadBezierArrowItem::GetVersionHistory() noexcept
{
  return {
    "2013-01-01: version 1.0: initial version"
  };
}

void ribi::QtLabeledQuadBezierArrowItem::keyPressEvent(QKeyEvent *event) noexcept
{
  QtRoundedEditRectItem::keyPressEvent(event);
  m_arrow->keyPressEvent(event);
}

void ribi::QtLabeledQuadBezierArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept
{
  assert(m_arrow->GetMidItem());
  assert(this->GetPos() == m_arrow->GetMidItem()->pos());
  painter->translate(-this->GetPos());
  m_arrow->paint(painter,option,widget);
  painter->translate(this->GetPos());
  QtRoundedEditRectItem::paint(painter,option,widget);
}
