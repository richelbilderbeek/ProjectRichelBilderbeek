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
#ifdef USE_ITEMDISPLAYSTRATEGY_20140622

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapdisplaystrategy.h"

#include <cstdlib>
#include <sstream>

#include <QKeyEvent>

#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapconcept.h"
#include "conceptmapcompetency.h"
#include "conceptmapconceptfactory.h"
#include "qtconceptmapbrushfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtDisplayStrategy::QtDisplayStrategy(const boost::shared_ptr<ribi::cmap::Concept>& concept)
  : QtItemDisplayStrategy(concept)
{
  #ifndef NDEBUG
  Test();
  assert(concept);
  assert(GetConcept());
  #endif

  UpdateBrushesAndPens(); //NEVER CALL VIRTUAL FUNCTIONS IN CONSTRUCTORS

  //?FIX 2013-01-06 22:47
  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&ribi::cmap::QtDisplayStrategy::OnConceptNameChanged,this)); //Obligatory

  GetConcept()->m_signal_examples_changed.connect( //FIX 2013-01-06 22:32
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );

  GetConcept()->m_signal_rating_complexity_changed.connect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_concreteness_changed.connect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_specificity_changed.connect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );
}

ribi::cmap::QtDisplayStrategy::~QtDisplayStrategy() noexcept
{
  GetConcept()->m_signal_examples_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );

  //Obligatory: because concepts live longer than DisplayConceptItems,
  //these Concepts will signal Items when the Item is destroyed,
  //which results in a segmentation fault
  GetConcept()->m_signal_rating_complexity_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_concreteness_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_specificity_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens,
        this
      )
    );
}

#ifndef NDEBUG
void ribi::cmap::QtDisplayStrategy::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtDisplayStrategy::Test()");
  TRACE("Successfully finished ribi::cmap::QtDisplayStrategy::Test()");
}
#endif


void ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens() noexcept
{
  //TRACE("Start of void ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens()");
  assert(GetConcept());
  assert(GetConcept()->GetExamples());

  //Brush for the concept being rated
  QBrush new_main_brush = this->brush();
  {
    const int n_rated
      = (GetConcept()->GetRatingComplexity()   != -1 ? 1 : 0)
      + (GetConcept()->GetRatingConcreteness() != -1 ? 1 : 0)
      + (GetConcept()->GetRatingSpecificity()  != -1 ? 1 : 0);
    switch (n_rated)
    {
      case 0:
        new_main_brush = QtBrushFactory::CreateRedGradientBrush();
        break;
      case 1:
      case 2:
        new_main_brush = QtBrushFactory::CreateYellowGradientBrush();
        break;
      case 3:
        new_main_brush = QtBrushFactory::CreateGreenGradientBrush();
        break;
      default: assert(!"Should not get here");
    }
  }
  //Brush and pen for the examples being rated
  QBrush new_indicator_brush = this->GetIndicatorBrush();
  QPen new_indicator_pen = this->GetIndicatorPen();
  if (GetConcept()->GetExamples()->Get().empty())
  {
    //No examples
    new_indicator_brush = QBrush(QColor(0,0,0));
    new_indicator_pen = QPen(QColor(0,0,0));
  }
  else
  {
    const std::vector<boost::shared_ptr<const cmap::Example> > v = AddConst(GetConcept()->GetExamples()->Get());
    const int n_examples = boost::numeric_cast<int>(v.size());
    const int n_judged
      = std::count_if(v.begin(),v.end(),
        [](const boost::shared_ptr<const cmap::Example>& p)
        {
          assert(p);
          const cmap::Competency this_competency = p->GetCompetency();
          return this_competency != cmap::Competency::uninitialized;
        }
      );
    if (n_judged == 0)
    {
      new_indicator_brush = QBrush(QColor(255,128,128)); //Red
    }
    else if (n_judged < n_examples)
    {
      new_indicator_brush = QBrush(QColor(255,196,128)); //Orange
    }
    else
    {
      assert(n_judged == n_examples);
      new_indicator_brush = QBrush(QColor(128,255,128)); //Green
    }
    if (n_judged == 0)
    {
      new_indicator_pen = QPen(QColor(255,0,0),3); //Thick pen
    }
    else if (n_judged < n_examples)
    {
      new_indicator_pen = QPen(QColor(255,196,0),2); //Less thick pen
    }
    else
    {
      assert(n_judged == n_examples);
      new_indicator_pen = QPen(QColor(0,255,0),1); //Thin pen
    }
  }
  if (this->brush() != new_main_brush
    || this->GetIndicatorBrush() != new_indicator_brush
    || this->GetIndicatorPen() != new_indicator_pen)
  {
    this->setBrush(new_main_brush);
    this->SetIndicatorBrush(new_indicator_brush);
    this->SetIndicatorPen(new_indicator_pen);
    assert(this->brush() == new_main_brush);
    assert(this->GetIndicatorBrush() == new_indicator_brush);
    assert(this->GetIndicatorPen() == new_indicator_pen);
    //TRACE(std::rand()); //GOOD: Detects infinite recursion
    //this->update();
    this->m_signal_item_has_updated(this); //Obligatory
    this->m_signal_request_scene_update(); //Obligatory
  }
  //TRACE("End of void ribi::cmap::QtDisplayStrategy::UpdateBrushesAndPens()");
}

#endif // USE_ITEMDISPLAYSTRATEGY_20140622
