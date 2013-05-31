#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconceptitem.h"

#include <cstdlib>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <QKeyEvent>

#include "pvdbhelper.h"
#include "pvdbexample.h"
#include "pvdbconcept.h"
#include "pvdbexamples.h"
#include "pvdbconceptfactory.h"
#include "pvdbcompetency.h"
#include "qtpvdbbrushfactory.h"
#include "trace.h"

QtPvdbRateConceptItem::QtPvdbRateConceptItem(const boost::shared_ptr<pvdb::Concept>& concept)
  : QtPvdbConceptItem(concept)
{
  #ifndef NDEBUG
  Test();
  assert(concept);
  assert(GetConcept());
  #endif

  UpdateBrushesAndPens();

  //?FIX 2013-01-06 22:47
  GetConcept()->m_signal_name_changed.connect(
    boost::bind(&QtPvdbRateConceptItem::OnConceptNameChanged,this)); //Obligatory

  GetConcept()->m_signal_examples_changed.connect( //FIX 2013-01-06 22:32
      boost::bind(
        &QtPvdbRateConceptItem::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_complexity_changed.connect(
      boost::bind(
        &QtPvdbRateConceptItem::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_concreteness_changed.connect(
      boost::bind(
        &QtPvdbRateConceptItem::UpdateBrushesAndPens,
        this
      )
    );
  GetConcept()->m_signal_rating_specificity_changed.connect(
      boost::bind(
        &QtPvdbRateConceptItem::UpdateBrushesAndPens,
        this
      )
    );

}

void QtPvdbRateConceptItem::keyPressEvent(QKeyEvent *event)
{

  switch (event->key())
  {
    case Qt::Key_F1:
      m_signal_request_rate_concept(this);
      return;
    case Qt::Key_F2:
      m_signal_request_rate_examples(this); //Dialog will handle empty examples
      return; //Always return, otherwise F2 in QtPvdbNodeConcept will cause an edit
  }
}

void QtPvdbRateConceptItem::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  TRACE("QtPvdbRateConceptItem::Test started");
  //Check brush comparison
  {
    assert(QtPvdbBrushFactory::CreateRedGradientBrush() != QtPvdbBrushFactory::CreateYellowGradientBrush());
    assert(QtPvdbBrushFactory::CreateRedGradientBrush() != QtPvdbBrushFactory::CreateGreenGradientBrush());
  }
  ///Check if the correct brushes are used when rating the concept
  {
    TRACE("TODO");
    /*
    const boost::shared_ptr<pvdb::Concept> concept = pvdb::ConceptFactory::GetTests().at(4);
    concept->SetRatingComplexity(-1);
    concept->SetRatingConcreteness(-1);
    concept->SetRatingSpecificity(-1);
    QtPvdbRateConceptItem item(concept);
    assert(item.brush() ==  QtPvdbBrushFactory::CreateRedGradientBrush());
    concept->SetRatingComplexity(0);
    concept->SetRatingConcreteness(1);
    assert(item.brush() ==  QtPvdbBrushFactory::CreateYellowGradientBrush());
    concept->SetRatingSpecificity(2);
    assert(item.brush() ==  QtPvdbBrushFactory::CreateGreenGradientBrush());
    */
  }
  ///Check that if the examples are changed, the brushes changed
  {
  }
  TRACE("QtPvdbRateConceptItem::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}

void QtPvdbRateConceptItem::UpdateBrushesAndPens()
{
  //Brush for the concept being rated
  const int n_rated
    = (GetConcept()->GetRatingComplexity()   != -1 ? 1 : 0)
    + (GetConcept()->GetRatingConcreteness() != -1 ? 1 : 0)
    + (GetConcept()->GetRatingSpecificity()  != -1 ? 1 : 0);

  switch (n_rated)
  {
    case 0:
      this->SetMainBrush(QtPvdbBrushFactory::CreateRedGradientBrush());
      break;
    case 1:
    case 2:
      this->SetMainBrush(QtPvdbBrushFactory::CreateYellowGradientBrush());
      break;
    case 3:
      this->SetMainBrush(QtPvdbBrushFactory::CreateGreenGradientBrush());
      break;
    default: assert(!"Should not get here");
  }
  //Brush and pen for the examples being rated
  if (GetConcept()->GetExamples()->Get().empty())
  {
    //No examples
    this->SetIndicatorBrush(QBrush(QColor(0,0,0)));
    this->SetIndicatorPen(QPen(QColor(0,0,0)));
  }
  else
  {
    const std::vector<boost::shared_ptr<const pvdb::Example> > v = AddConst(GetConcept()->GetExamples()->Get());
    const int n_examples = boost::numeric_cast<int>(v.size());
    const int n_judged
      = std::count_if(v.begin(),v.end(),
        [](const boost::shared_ptr<const pvdb::Example>& p)
        {
          assert(p);
          const pvdb::Competency this_competency = p->GetCompetency();
          return this_competency != pvdb::Competency::uninitialized;
        }
      );
    if (n_judged == 0)
    {
      this->SetIndicatorBrush(QBrush(QColor(255,128,128)  )); //Red
      this->SetIndicatorPen(  QPen(  QColor(255,  0,  0),3)); //Thick pen
    }
    else if (n_judged < n_examples)
    {
      this->SetIndicatorBrush(QBrush(QColor(255,196,128)  )); //Orange
      this->SetIndicatorPen(  QPen(  QColor(255,196,  0),2)); //Less thick pen
    }
    else
    {
      assert(n_judged == n_examples);
      this->SetIndicatorBrush(QBrush(QColor(128,255,128)  )); //Green
      this->SetIndicatorPen(  QPen(  QColor(  0,255,  0),1)); //Thin pen
    }
  }
  //this->update(); //FIX 2013-01-17
  //this->m_signal_item_has_updated(this); //FIX 2013-01-17
  //this->m_signal_request_scene_update(); //FIX 2013-01-17
}
