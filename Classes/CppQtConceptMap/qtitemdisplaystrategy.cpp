//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
#include "qtitemdisplaystrategy.h"

#include <string>
#include <boost/lexical_cast.hpp>

#include <QCursor>
#include <QFont>
#include <QKeyEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>

#include "fuzzy_equal_to.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapconcept.h"
#include "conceptmapedge.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapexamplesitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtItemDisplayStrategy::QtItemDisplayStrategy(
  const boost::shared_ptr<ribi::cmap::Concept>& concept)
  : m_signal_position_changed{},
    m_concept(concept),
    m_indicator_brush(QBrush(QColor(0,0,0,0))),
    m_indicator_pen(QPen(QColor(0,0,0)))
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(m_concept);
  assert(m_concept->GetExamples());

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsSelectable);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);

  this->SetPadding(Base::Padding(1.0,6.0,1.0,2.0));

  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&ribi::cmap::QtItemDisplayStrategy::OnConceptNameChanged,this)); //Obligatory

  //FIX? 2013-06-25
  //this->SetText("DUMMY TEXT");
  //assert(this->GetText() != m_concept->GetName()
  //  && "The text must be set, to get a resize");

  this->SetName(m_concept->GetName());
}

boost::shared_ptr<const ribi::cmap::Concept> ribi::cmap::QtItemDisplayStrategy::GetConcept() const noexcept
{
  boost::shared_ptr<const ribi::cmap::Concept> p(m_concept);
  assert(p);
  return p;
}

std::string ribi::cmap::QtItemDisplayStrategy::GetName() const noexcept
{
  return Unwordwrap(this->GetText());
}

void ribi::cmap::QtItemDisplayStrategy::hoverStartEvent(QGraphicsSceneHoverEvent *)
{
  std::exit(1); //Never called
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void ribi::cmap::QtItemDisplayStrategy::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void ribi::cmap::QtItemDisplayStrategy::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  Base::mouseMoveEvent(event);
  //this->m_signal_item_has_updated();
  m_signal_request_scene_update();
}

void ribi::cmap::QtItemDisplayStrategy::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
  Base::mousePressEvent(event);
  //this->m_signal_item_has_updated();
  m_signal_request_scene_update();
}

void ribi::cmap::QtItemDisplayStrategy::OnConceptNameChanged()
{
  assert(this);
  assert(m_concept);
  assert(m_concept->GetExamples());
  this->SetName(m_concept->GetName());
  //m_signal_item_changed(this); //Called by SetText
}

void ribi::cmap::QtItemDisplayStrategy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  assert(m_concept);
  assert(m_concept->GetExamples());
  //assert(!this->hasFocus()); //Can have focus when used as stand-alone
  //assert(!this->isSelected()); //Can have focus when used as stand-alone
  this->UpdateBrushesAndPens();

  Base::paint(painter,option,widget);

  if (!m_concept->GetExamples()->Get().empty())
  {
    painter->setBrush(m_indicator_brush);
    painter->setPen(m_indicator_pen);
    //Draw indicator that a concept has examples in it
    painter->drawRect(
      rect().right() - 5.0,
      rect().top() + 3.0,
      3.0,
      3.0
      );
  }
}

void ribi::cmap::QtItemDisplayStrategy::SetIndicatorBrush(const QBrush& brush)
{
  if (m_indicator_brush != brush)
  {
    m_indicator_brush = brush;
    this->update();
  }
}

void ribi::cmap::QtItemDisplayStrategy::SetIndicatorPen(const QPen& pen)
{
  if (m_indicator_pen != pen)
  {
    m_indicator_pen = pen;
    this->update();
  }
}

void ribi::cmap::QtItemDisplayStrategy::SetMainBrush(const QBrush& any_brush)
{

  if (this->brush() != any_brush)
  {
    this->setBrush(any_brush);
    this->update();
  }
  assert(this->brush() == any_brush);
}

void ribi::cmap::QtItemDisplayStrategy::SetPos(const double x, const double y)
{
  if (x != this->x() || y != this->y())
  {
    this->setPos(x,y);
    this->m_signal_position_changed(x,y);
  }
}

void ribi::cmap::QtItemDisplayStrategy::SetName(const std::string& s)
{
  //Set the text
  const std::vector<std::string> v { Wordwrap(s,40) };
  this->SetText(v);

  #ifndef NDEBUG
  if (this->GetName() != s)
  {
    TRACE(this->GetName());
  }
  #endif
  assert(this->GetName() == s);
}

/*
QPainterPath ribi::cmap::QtItemDisplayStrategy::shape() const
{
  const int click_easy_width = 5;
  QPainterPath path;
  QPainterPathStroker stroker;

  path.addRect(this->boundingRect());
  stroker.setWidth(click_easy_width);
  return stroker.createStroke(path);
}
*/

#ifndef NDEBUG
void ribi::cmap::QtItemDisplayStrategy::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtItemDisplayStrategy::Test()");

  TRACE("Successfully finished ribi::cmap::QtItemDisplayStrategy::Test()");
}
#endif
