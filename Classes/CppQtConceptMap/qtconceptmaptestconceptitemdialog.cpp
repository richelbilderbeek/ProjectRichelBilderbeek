#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaptestconceptitemdialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapbrushfactory.h"
#include "conceptmapconcept.h"
#include "qtconceptmapratestrategy.h"
#include "conceptmapexamples.h"
#include "conceptmapexample.h"
#include "ui_qtconceptmaptestconceptitemdialog.h"
#include "conceptmapconceptfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapTestConceptItemDialog::QtConceptMapTestConceptItemDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtConceptMapTestConceptItemDialog),
  m_concept(cmap::ConceptFactory().GetTests().at(1)),
  m_display_concept(nullptr),
  m_edit_concept(nullptr),
  m_rate_concept(nullptr)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(ui->view->scene());

  //Node is used in: m_node
  assert(m_concept.use_count() == 1);

  m_display_concept = new cmap::QtDisplayStrategy(m_concept);
  assert(m_display_concept);

  //Node is used in: m_node and QtConceptMapNodeConcept::m_node
  assert(m_concept.use_count() == 2);
  //Concept is used in: m_node::m_concept, QtDisplayStrategy::m_node::m_concept and QtConceptMapConcept::m_concept
  assert(m_concept.get() == m_display_concept->GetConcept().get());
  assert(m_concept.get() == m_display_concept->GetConcept().get());
  assert(m_concept.use_count() == 2);

  //Node is used in: m_node, QtConceptMapNodeConcept::m_node
  m_edit_concept = new cmap::QtEditStrategy(m_concept);

  assert(m_edit_concept);
  assert(m_concept.use_count() == 3);

  m_rate_concept = new cmap::QtRateStrategy(m_concept);

  assert(m_rate_concept);
  assert(m_concept.use_count() == 4);
  assert(m_display_concept->GetConcept().get() == m_concept.get());
  assert(m_edit_concept->GetConcept().get()    == m_concept.get());
  assert(m_rate_concept->GetConcept().get()    == m_concept.get());

  //QtConceptMapConceptItems are not aware of their surroundings, so put them into place manually
  m_display_concept->SetPos(0.0,-40.0);
  m_edit_concept->SetPos(   0.0,  0.0);
  m_rate_concept->SetPos(   0.0, 40.0);

  assert(!m_display_concept->scene());
  assert(!m_edit_concept->scene());
  assert(!m_rate_concept->scene());
  ui->view->scene()->addItem(m_display_concept);
  ui->view->scene()->addItem(m_edit_concept);
  ui->view->scene()->addItem(m_rate_concept);

  assert(ui->view->scene()->items().size() == 3);
  assert(dynamic_cast<cmap::QtItemDisplayStrategy*>(ui->view->scene()->items()[0]));
  assert(dynamic_cast<cmap::QtItemDisplayStrategy*>(ui->view->scene()->items()[1]));
  assert(dynamic_cast<cmap::QtItemDisplayStrategy*>(ui->view->scene()->items()[2]));

  {
    const std::vector<cmap::Competency> v = cmap::GetAllCompetencies();
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      ui->box_competency->addItem(cmap::CompetencyToDutchStr(v[i]).c_str());
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

ribi::cmap::QtConceptMapTestConceptItemDialog::~QtConceptMapTestConceptItemDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::cmap::Concept> ribi::cmap::QtConceptMapTestConceptItemDialog::GetChosenConcept()
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
          return dynamic_cast<cmap::QtDisplayStrategy*>(item);
        }
      );
      assert(iter!=v.end());
      cmap::QtDisplayStrategy * const qtconcept {
        dynamic_cast<cmap::QtDisplayStrategy*>(*iter)
      };
      assert(qtconcept);
      return qtconcept->GetConcept();
    }
    case 2:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](QGraphicsItem * const item)
        {
          return dynamic_cast<cmap::QtEditStrategy*>(item);
        }
      );
      assert(iter!=v.end());
      cmap::QtEditStrategy * const qtconcept {
        dynamic_cast<cmap::QtEditStrategy*>(*iter)
      };
      assert(qtconcept);
      return qtconcept->GetConcept();
    }
    case 3:
    {
      const auto v = ui->view->scene()->items();
      const auto iter = std::find_if(v.begin(),v.end(),
        [](QGraphicsItem * const item)
        {
          return dynamic_cast<cmap::QtRateStrategy*>(item);
        }
      );
      assert(iter!=v.end());
      cmap::QtRateStrategy * const qtconcept {
        dynamic_cast<cmap::QtRateStrategy*>(*iter)
      };
      assert(qtconcept);
      return qtconcept->GetConcept();
    }
    default:
      assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::cmap::QtConceptMapTestConceptItemDialog::GetChosenConcept: chosen concept unknown");
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::on_box_competency_currentIndexChanged(int index)
{
  const cmap::Competency c = static_cast<cmap::Competency>(index);
  this->GetChosenConcept()->GetExamples()->Get().at(0)->SetCompetency(c);
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::on_edit_name_textChanged(const QString &arg1)
{
  assert(GetChosenConcept());
  this->GetChosenConcept()->SetName(arg1.toStdString());
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::on_box_complexity_currentIndexChanged(const QString &arg1)
{
  const int rating_complexity = boost::lexical_cast<int>(arg1.toStdString());
  assert(rating_complexity >= -1);
  assert(rating_complexity <=  2);
  this->GetChosenConcept()->SetRatingComplexity(rating_complexity);
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::on_box_concreteness_currentIndexChanged(const QString &arg1)
{
  this->GetChosenConcept()->SetRatingConcreteness(boost::lexical_cast<int>(arg1.toStdString()));
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::on_box_specificity_currentIndexChanged(const QString &arg1)
{
  this->GetChosenConcept()->SetRatingSpecificity(boost::lexical_cast<int>(arg1.toStdString()));
}

void ribi::cmap::QtConceptMapTestConceptItemDialog::on_edit_example_text_textChanged(const QString &arg1)
{
  this->GetChosenConcept()->GetExamples()->Get().at(0)->SetText(arg1.toStdString());
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapTestConceptItemDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtConceptMapTestConceptItemDialog::Test started");
  QtConceptMapTestConceptItemDialog d;
  assert(d.m_concept.get() == d.m_display_concept->GetConcept().get());
  assert(d.m_concept.get() == d.m_edit_concept->GetConcept().get());
  assert(d.m_concept.get() == d.m_rate_concept->GetConcept().get());

  //Test resizing due to text being changed
  {
    const std::string s = d.m_concept->GetName();
    assert(d.m_display_concept->boundingRect().width() == d.m_edit_concept->boundingRect().width());
    assert(d.m_display_concept->boundingRect().width() == d.m_rate_concept->boundingRect().width());
    const double w = d.m_display_concept->boundingRect().width();
    const double h = d.m_display_concept->boundingRect().height();
    const double a = w * h;
    d.m_concept->SetName(s + "*");

    assert(d.m_display_concept->boundingRect().width()
      * d.m_display_concept->boundingRect().height()
      >= a);
    assert(d.m_edit_concept->boundingRect().width()
      * d.m_edit_concept->boundingRect().height()
      >= a);
    assert(d.m_rate_concept->boundingRect().width()
      * d.m_rate_concept->boundingRect().height()
      >= a);
  }
  //Test brushes being changed when ratings are given
  {
    const boost::shared_ptr<Concept> concept = d.m_concept;
    concept->SetRatingComplexity(-1);
    concept->SetRatingConcreteness(-1);
    concept->SetRatingSpecificity(-1);
    assert(d.m_edit_concept->brush()    == QtBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_concept->brush() == QtBrushFactory::CreateRedGradientBrush());
    assert(d.m_rate_concept->brush()    == QtBrushFactory::CreateRedGradientBrush());

    concept->SetRatingComplexity(0);
    concept->SetRatingConcreteness(1);

    assert(d.m_edit_concept->brush()     == QtBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_concept->brush()  == QtBrushFactory::CreateYellowGradientBrush());
    assert(d.m_rate_concept->brush()     == QtBrushFactory::CreateYellowGradientBrush());

    concept->SetRatingSpecificity(2);

    assert(d.m_edit_concept->brush()    == QtBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_concept->brush() == QtBrushFactory::CreateGreenGradientBrush());
    assert(d.m_rate_concept->brush()    == QtBrushFactory::CreateGreenGradientBrush());
  }
  TRACE("ribi::cmap::QtConceptMapTestConceptItemDialog::Test finished successfully");
}
#endif
