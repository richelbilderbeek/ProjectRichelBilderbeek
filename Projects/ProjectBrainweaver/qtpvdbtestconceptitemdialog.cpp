#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbtestconceptitemdialog.h"

#include <cassert>
#include <stdexcept>

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbbrushfactory.h"
#include "pvdbconcept.h"
#include "qtpvdbrateconceptitem.h"
#include "pvdbexamples.h"
#include "pvdbexample.h"
#include "ui_qtpvdbtestconceptitemdialog.h"
#include "pvdbconceptfactory.h"
#include "trace.h"

QtPvdbTestConceptItemDialog::QtPvdbTestConceptItemDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestConceptItemDialog),
  m_concept(pvdb::ConceptFactory::GetTests().at(1)),
  m_display_concept(nullptr),
  m_edit_concept(nullptr),
  m_rate_concept(nullptr)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  assert(ui->view->scene());

  //Node is used in: m_node
  assert(m_concept.use_count() == 1);

  m_display_concept = new QtPvdbDisplayConceptItem(m_concept);
  assert(m_display_concept);

  //Node is used in: m_node and QtPvdbNodeConcept::m_node
  assert(m_concept.use_count() == 2);
  //Concept is used in: m_node::m_concept, QtPvdbDisplayConcept::m_node::m_concept and QtPvdbConcept::m_concept
  assert(m_concept.get() == m_display_concept->GetConcept().get());
  assert(m_concept.get() == m_display_concept->GetConcept().get());
  assert(m_concept.use_count() == 2);

  //Node is used in: m_node, QtPvdbNodeConcept::m_node
  m_edit_concept = new QtPvdbEditConceptItem(m_concept);

  assert(m_edit_concept);
  assert(m_concept.use_count() == 3);

  m_rate_concept = new QtPvdbRateConceptItem(m_concept);

  assert(m_rate_concept);
  assert(m_concept.use_count() == 4);
  assert(m_display_concept->GetConcept().get() == m_concept.get());
  assert(m_edit_concept->GetConcept().get()    == m_concept.get());
  assert(m_rate_concept->GetConcept().get()    == m_concept.get());

  //QtPvdbConceptItems are not aware of their surroundings, so put them into place manually
  m_display_concept->setPos(0.0,-40.0);
  m_edit_concept->setPos(   0.0,  0.0);
  m_rate_concept->setPos(   0.0, 40.0);

  ui->view->scene()->addItem(m_display_concept);
  ui->view->scene()->addItem(m_edit_concept);
  ui->view->scene()->addItem(m_rate_concept);

  assert(ui->view->scene()->items().size() == 3);
  assert(dynamic_cast<QtPvdbConceptItem*>(ui->view->scene()->items()[0]));
  assert(dynamic_cast<QtPvdbConceptItem*>(ui->view->scene()->items()[1]));
  assert(dynamic_cast<QtPvdbConceptItem*>(ui->view->scene()->items()[2]));

  {
    const std::vector<pvdb::Competency> v = pvdb::GetAllCompetencies();
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      ui->box_competency->addItem(pvdb::CompetencyToDutchStr(v[i]).c_str());
    }
  }

  assert(this->GetChosenConcept()->GetExamples());
  assert(this->GetChosenConcept()->GetExamples()->Get().size() == 1);

  ui->box_complexity->setCurrentIndex(this->GetChosenConcept()->GetRatingComplexity() + 1);
  ui->box_concreteness->setCurrentIndex(this->GetChosenConcept()->GetRatingConcreteness() + 1);
  ui->box_specificity->setCurrentIndex(this->GetChosenConcept()->GetRatingSpecificity() + 1);

  ui->edit_name->setText(this->GetChosenConcept()->GetName().c_str());
  ui->edit_example_text->setText(this->GetChosenConcept()->GetExamples()->Get().at(0)->GetText().c_str());

  ui->box_competency->setCurrentIndex(static_cast<int>(this->GetChosenConcept()->GetExamples()->Get().at(0)->GetCompetency()));
}

QtPvdbTestConceptItemDialog::~QtPvdbTestConceptItemDialog()
{
  delete ui;
}

const boost::shared_ptr<pvdb::Concept> QtPvdbTestConceptItemDialog::GetChosenConcept()
{
  switch(ui->box_edit->currentIndex())
  {
    case 0: return m_concept;
    case 1:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](QGraphicsItem * const item)
        {
          return dynamic_cast<QtPvdbDisplayConceptItem*>(item);
        }
      );
      assert(iter!=v.end());
      QtPvdbDisplayConceptItem * const qtconcept = dynamic_cast<QtPvdbDisplayConceptItem*>(*iter);
      assert(qtconcept);
      return qtconcept->GetConcept();
    }
    case 2:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](QGraphicsItem * const item)
        {
          return dynamic_cast<QtPvdbEditConceptItem*>(item);
        }
      );
      assert(iter!=v.end());
      QtPvdbEditConceptItem * const qtconcept = dynamic_cast<QtPvdbEditConceptItem*>(*iter);
      assert(qtconcept);
      return qtconcept->GetConcept();
    }
    case 3:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](QGraphicsItem * const item)
        {
          return dynamic_cast<QtPvdbRateConceptItem*>(item);
        }
      );
      assert(iter!=v.end());
      QtPvdbRateConceptItem * const qtconcept = dynamic_cast<QtPvdbRateConceptItem*>(*iter);
      assert(qtconcept);
      return qtconcept->GetConcept();
    }
    default:
      assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("QtPvdbTestConceptItemDialog::GetChosenConcept: chosen concept unknown");
}

void QtPvdbTestConceptItemDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtPvdbTestConceptItemDialog::on_box_competency_currentIndexChanged(int index)
{
  const pvdb::Competency c = static_cast<pvdb::Competency>(index);
  this->GetChosenConcept()->GetExamples()->Get().at(0)->SetCompetency(c);
}

void QtPvdbTestConceptItemDialog::on_edit_name_textChanged(const QString &arg1)
{
  assert(GetChosenConcept());
  this->GetChosenConcept()->SetName(arg1.toStdString());
}

void QtPvdbTestConceptItemDialog::on_box_complexity_currentIndexChanged(const QString &arg1)
{
  const int rating_complexity = boost::lexical_cast<int>(arg1.toStdString());
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);
  this->GetChosenConcept()->SetRatingComplexity(rating_complexity);
}

void QtPvdbTestConceptItemDialog::on_box_concreteness_currentIndexChanged(const QString &arg1)
{
  this->GetChosenConcept()->SetRatingConcreteness(boost::lexical_cast<int>(arg1.toStdString()));
}

void QtPvdbTestConceptItemDialog::on_box_specificity_currentIndexChanged(const QString &arg1)
{
  this->GetChosenConcept()->SetRatingSpecificity(boost::lexical_cast<int>(arg1.toStdString()));
}

void QtPvdbTestConceptItemDialog::on_edit_example_text_textChanged(const QString &arg1)
{
  this->GetChosenConcept()->GetExamples()->Get().at(0)->SetText(arg1.toStdString());
}

void QtPvdbTestConceptItemDialog::Test()
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
  TRACE("QtPvdbTestConceptItemDialog::Test started");
  QtPvdbTestConceptItemDialog d;
  assert(d.m_concept.get() == d.m_display_concept->GetConcept().get());
  assert(d.m_concept.get() == d.m_edit_concept->GetConcept().get());
  assert(d.m_concept.get() == d.m_rate_concept->GetConcept().get());

  //Test resizing due to text being changed
  {
    TRACE("TODO");
    /*
    const std::string s = d.m_concept->GetName();
    assert(d.m_display_concept->boundingRect().width() == d.m_edit_concept->boundingRect().width());
    assert(d.m_display_concept->boundingRect().width() == d.m_rate_concept->boundingRect().width());
    const double w = d.m_display_concept->boundingRect().width();
    d.m_concept->SetName(s + "*");
    assert(d.m_display_concept->boundingRect().width() > w);
    assert(d.m_edit_concept->boundingRect().width() > w);
    assert(d.m_rate_concept->boundingRect().width() > w);
    */
  }
  //Test brushes being changed when ratings are given
  {
    TRACE("TODO");
    /*
    const boost::shared_ptr<pvdb::Concept> concept = d.m_concept;
    concept->SetRatingComplexity(-1);
    concept->SetRatingConcreteness(-1);
    concept->SetRatingSpecificity(-1);
    assert(d.m_edit_concept->brush()    == QtPvdbBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_concept->brush() == QtPvdbBrushFactory::CreateRedGradientBrush());
    assert(d.m_rate_concept->brush()    == QtPvdbBrushFactory::CreateRedGradientBrush());

    concept->SetRatingComplexity(0);
    concept->SetRatingConcreteness(1);

    assert(d.m_edit_concept->brush()     == QtPvdbBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_concept->brush()  == QtPvdbBrushFactory::CreateYellowGradientBrush());
    assert(d.m_rate_concept->brush()     == QtPvdbBrushFactory::CreateYellowGradientBrush());

    concept->SetRatingSpecificity(2);

    assert(d.m_edit_concept->brush()    == QtPvdbBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_concept->brush() == QtPvdbBrushFactory::CreateGreenGradientBrush());
    assert(d.m_rate_concept->brush()    == QtPvdbBrushFactory::CreateGreenGradientBrush());
    */
  }
  TRACE("QtPvdbTestConceptItemDialog::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
