#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapratestrategy.h"

#include <cstdlib>

#include <QKeyEvent>

#include "conceptmaphelper.h"
#include "conceptmapexample.h"
#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapcompetency.h"
#include "qtconceptmapbrushfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtRateStrategy::QtRateStrategy(const boost::shared_ptr<ribi::cmap::Concept>& concept)
  : QtItemDisplayStrategy(concept),
    m_signal_request_rate_concept{},
    m_signal_request_rate_examples{}
{
  #ifndef NDEBUG
  Test();
  assert(concept);
  assert(GetConcept());
  #endif

  UpdateBrushesAndPens();

  //?FIX 2013-01-06 22:47
  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&ribi::cmap::QtRateStrategy::OnConceptNameChanged,this)); //Obligatory

  GetConcept()->m_signal_examples_changed.connect( //FIX 2013-01-06 22:32
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_complexity_changed.connect(
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_concreteness_changed.connect(
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_specificity_changed.connect(
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );

}


ribi::cmap::QtRateStrategy::~QtRateStrategy() noexcept
{
  GetConcept()->m_signal_rating_complexity_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_concreteness_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_specificity_changed.disconnect(
      boost::bind(
        &ribi::cmap::QtRateStrategy::UpdateBrushesAndPens,
        this
      )
    );
}

void ribi::cmap::QtRateStrategy::keyPressEvent(QKeyEvent *event)
{

  switch (event->key())
  {
    case Qt::Key_F1:
      m_signal_request_rate_concept(this);
      return;
    case Qt::Key_F2:
      m_signal_request_rate_examples(this); //Dialog will handle empty examples
      return; //Always return, otherwise F2 in QtConceptMapNodeConcept will cause an edit
  }
}

#ifndef NDEBUG
void ribi::cmap::QtRateStrategy::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtRateStrategy::Test started");
  //Check brush comparison
  {
    assert(QtBrushFactory::CreateRedGradientBrush() != QtBrushFactory::CreateYellowGradientBrush());
    assert(QtBrushFactory::CreateRedGradientBrush() != QtBrushFactory::CreateGreenGradientBrush());
  }
  {
    const boost::shared_ptr<Concept> concept = ConceptFactory::Create();
    QtRateStrategy a(concept);
    const auto v {
      "1234567890",
      "1234567890 1234567890",
      "1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890"
    };
    for (const auto s: v) { a.SetName(s); } //SetName tests GetName
  }
  TRACE("ribi::cmap::QtRateStrategy::Test finished successfully");
}
#endif

void ribi::cmap::QtRateStrategy::UpdateBrushesAndPens()
{
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
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
    this->m_signal_request_scene_update(); //Obligatory
    #pragma GCC diagnostic pop
  }

}
