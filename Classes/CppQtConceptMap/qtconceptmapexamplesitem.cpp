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

#include <QFont>
#include <QPainter>

#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapedge.h"
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
    m_item{}
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

void ribi::cmap::QtExamplesItem::OnItemUpdated()
{
  this->update();
  this->m_signal_request_scene_update();
}

void ribi::cmap::QtExamplesItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) noexcept
{
  #ifdef NOT_NOW_20140801
  this->SetExamples(this->m_item->GetNode()->GetConcept()->GetExamples());
  #endif // NOT_NOW_20140801

  const QPointF p = m_item->GetPos();
  const QRectF r = m_item->GetRect();
  this->SetPos(
    p.x() + (0.5 * r.width() ) + 4.0 + (0.5 * this->GetRect().width() ),
    p.y() + (0.5 * r.height()) + 4.0 + (0.5 * GetRect().height())
  );

  QtRoundedEditRectItem::paint(painter,option,widget);
}

void ribi::cmap::QtExamplesItem::SetBuddyItem(const QtConceptMapElement* const item)
{
  if (m_item != item)
  {
    m_item = item;
    #ifdef NOT_NOW_20140801
    if (m_item && !m_item->GetNode()->GetConcept()->GetExamples()->Get().empty())
    {
      m_item->m_signal_pos_changed.connect(
        boost::bind(
          &ribi::cmap::QtExamplesItem::OnItemUpdated,this
        )
      );
      this->SetExamples(item->GetNode()->GetConcept()->GetExamples());
      this->setVisible(true);
    }
    #endif // NOT_NOW_20140801
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


