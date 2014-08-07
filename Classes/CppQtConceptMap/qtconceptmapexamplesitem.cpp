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
#include "qtconceptmapexamplesitem.h"

#include <boost/lambda/lambda.hpp>

#include <QFont>
#include <QPainter>

#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapnode.h"
#include "qtconceptmapelement.h"
#include "qtconceptmapelement.h"
#include "qtitemdisplaystrategy.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtExamplesItem::QtExamplesItem(
  QGraphicsItem* parent)
  : QtRoundedEditRectItem(
      { "..." },
      QtRoundedEditRectItem::Padding(),
      QFont("monospace",9),
      parent
    ),
    m_signal_request_scene_update{},
    m_item{nullptr},
    m_qtedge{nullptr},
    m_qtnode{nullptr}
{
  #ifndef NDEBUG
  Test();
  #endif
  this->setPen(QPen(QColor(255,0,0)));
  this->setBrush(QtBrushFactory::CreateWhiteGradientBrush());
  this->setFlags(0);
  this->setZValue(2.0);
  this->setVisible(false);
  //this->SetBuddyItem(concept);
}

void ribi::cmap::QtExamplesItem::OnItemUpdated(
  // const QGraphicsItem * const item
)
{
  this->update();
  this->m_signal_request_scene_update();
}

void ribi::cmap::QtExamplesItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) noexcept
{
  //this->SetExamples(this->m_item->GetNode()->GetConcept()->GetExamples());
  const auto qtnode = m_qtedge ? m_qtedge->GetQtNode().get() : m_qtnode;

  const QPointF p = qtnode->GetOuterPos();
  const QRectF r = qtnode->GetOuterRect();
  this->SetOuterPos(
    p.x() + (0.5 * r.width() ) + 4.0 + (0.5 * this->GetInnerRect().width() ),
    p.y() + (0.5 * r.height()) + 4.0 + (0.5 * GetInnerRect().height())
  );

  QtRoundedEditRectItem::paint(painter,option,widget);
}

void ribi::cmap::QtExamplesItem::SetBuddyItem(const QGraphicsItem * const item)
{
  if (m_item != item)
  {
    m_item = item;
    m_qtedge = dynamic_cast<const QtEdge*>(item);
    m_qtnode = dynamic_cast<const QtNode*>(item);
    if (m_qtedge && !m_qtedge->GetQtNode()->GetNode()->GetConcept()->GetExamples()->Get().empty())
    {
      m_qtedge->m_signal_edge_changed.connect(
        boost::bind(
          &ribi::cmap::QtExamplesItem::OnItemUpdated,this // ,boost::lambda::_1
        )
      );
      this->SetExamples(m_qtedge->GetQtNode()->GetNode()->GetConcept()->GetExamples());
      this->setVisible(true);
    }
    if (m_qtnode && !m_qtnode->GetNode()->GetConcept()->GetExamples()->Get().empty())
    {
      m_qtnode->m_signal_node_changed.connect(
        boost::bind(
          &ribi::cmap::QtExamplesItem::OnItemUpdated,this //,boost::lambda::_1
        )
      );
      this->SetExamples(m_qtnode->GetNode()->GetConcept()->GetExamples());
      this->setVisible(true);
    }
    m_signal_request_scene_update();
  }
  else
  {
    if (this->isVisible())
    {
      this->setVisible(false);
      m_signal_request_scene_update();
    }
  }
}

void ribi::cmap::QtExamplesItem::SetExamples(const boost::shared_ptr<const ribi::cmap::Examples>& examples)
{
  std::vector<std::string> v;
  for (const boost::shared_ptr<const Example>& example: examples->Get())
  {
    const std::string s {example->GetText()};
    const std::size_t wordwrap_length{40};
    const std::vector<std::string> w {Wordwrap(s,wordwrap_length)};
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  this->SetText(v);
}

#ifndef NDEBUG
void ribi::cmap::QtExamplesItem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtRoundedEditRectItem();

  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif


