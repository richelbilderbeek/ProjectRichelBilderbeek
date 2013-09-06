#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconceptdialog.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "pvdbconceptfactory.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbedge.h"
#include "pvdbexamplesfactory.h"
#include "pvdbexamples.h"
#include "pvdbfile.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "pvdbrating.h"
#include "qtpvdbconceptmapratewidget.h"
#include "qtpvdbrateconcepttallydialog.h"
#include "trace.h"
#include "ui_qtpvdbrateconceptdialog.h"

ribi::pvdb::QtPvdbRateConceptDialog::QtPvdbRateConceptDialog(
  const boost::shared_ptr<ribi::pvdb::ConceptMap> sub_concept_map,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRateConceptDialog),
    m_button_ok_clicked(false),
    m_concept(sub_concept_map
      ? sub_concept_map->GetNodes().at(0)->GetConcept()
      : boost::shared_ptr<ribi::pvdb::Concept>() ),
    m_initial_complexity(sub_concept_map
      ? sub_concept_map->GetNodes().at(0)->GetConcept()->GetRatingComplexity()
      : -1 ),
    m_initial_concreteness(sub_concept_map
      ? sub_concept_map->GetNodes().at(0)->GetConcept()->GetRatingConcreteness()
      : -1),
    m_initial_specificity(sub_concept_map
      ? sub_concept_map->GetNodes().at(0)->GetConcept()->GetRatingSpecificity()
      : -1),

    m_sub_concept_map(sub_concept_map),
    m_widget(new QtPvdbConceptMapRateWidget(sub_concept_map))
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  if (!m_sub_concept_map) return;
  assert(m_sub_concept_map);
  assert(!m_sub_concept_map->GetNodes().empty());
  assert(m_sub_concept_map->GetNodes()[0]);

  assert(m_widget);
  assert(ui->concept_map_layout);

  ui->concept_map_layout->addWidget(m_widget.get());

  assert(m_concept);

  ui->box_complexity->setCurrentIndex(m_initial_complexity);
  ui->box_concreteness->setCurrentIndex(m_initial_concreteness);
  ui->box_specificity->setCurrentIndex(m_initial_specificity);
  ui->box_complexity->setFocus();

  //Set suggestions
  {
    const std::string s = "Formeel uitgangspunt: "
      + boost::lexical_cast<std::string>(pvdb::Rating::SuggestComplexity(m_sub_concept_map));
    ui->box_complexity->setToolTip(s.c_str());
  }
  {
    const std::string s = "Formeel uitgangspunt: "
      + boost::lexical_cast<std::string>(pvdb::Rating::SuggestConcreteness(m_sub_concept_map));
    ui->box_concreteness->setToolTip(s.c_str());
  }
  {
    const std::string s = "Formeel uitgangspunt: "
      + boost::lexical_cast<std::string>(pvdb::Rating::SuggestSpecificity(m_sub_concept_map));
    ui->box_specificity->setToolTip(s.c_str());
  }

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }
  //The rating by the Tally dialog must be visible as of 2013-08-30
  //so let this dialog follow the ratings done by the tally dialog
  //DOES NOT WORK
  //m_concept->m_signal_rating_complexity_changed.connect(
  //  boost::bind(&ribi::pvdb::QtPvdbRateConceptDialog::OnRatingComplexityChanged,this,boost::lambda::_1));
  //m_concept->m_signal_rating_concreteness_changed.connect(
  //  boost::bind(&ribi::pvdb::QtPvdbRateConceptDialog::OnRatingConcretenessChanged,this,boost::lambda::_1));
  //m_concept->m_signal_rating_specificity_changed.connect(
  //  boost::bind(&ribi::pvdb::QtPvdbRateConceptDialog::OnRatingSpecificityChanged,this,boost::lambda::_1));
}



ribi::pvdb::QtPvdbRateConceptDialog::~QtPvdbRateConceptDialog()
{
  //If user clicked OK, keep the current ratings (which are updated by the comboboxes)
  //else the user cancelled, so put back the initial ratings
  if (!m_button_ok_clicked && m_concept)
  {
    m_concept->SetRatingComplexity(m_initial_complexity);
    m_concept->SetRatingConcreteness(m_initial_concreteness);
    m_concept->SetRatingSpecificity(m_initial_specificity);
  }
  //if (m_concept)
  //{
  //  //Just to be sure
  //  m_concept->m_signal_rating_complexity_changed.disconnect(
  //    boost::bind(&ribi::pvdb::QtPvdbRateConceptDialog::OnRatingComplexityChanged,this,boost::lambda::_1));
  //  m_concept->m_signal_rating_concreteness_changed.disconnect(
  //    boost::bind(&ribi::pvdb::QtPvdbRateConceptDialog::OnRatingConcretenessChanged,this,boost::lambda::_1));
  //  m_concept->m_signal_rating_specificity_changed.disconnect(
  //    boost::bind(&ribi::pvdb::QtPvdbRateConceptDialog::OnRatingSpecificityChanged,this,boost::lambda::_1));
  //}
  delete ui;
}

void ribi::pvdb::QtPvdbRateConceptDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  //QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbRateConceptDialog::on_button_ok_clicked()
{
  //Ratings already set by comboboxes
  m_button_ok_clicked = true;
  close();
}

void ribi::pvdb::QtPvdbRateConceptDialog::OnRatingComplexityChanged(const ribi::pvdb::Concept* concept)
{
  assert(concept);
  if (ui->box_complexity->currentIndex() != concept->GetRatingComplexity())
  {
    ui->box_complexity->setCurrentIndex(concept->GetRatingComplexity());
  }
}

void ribi::pvdb::QtPvdbRateConceptDialog::OnRatingConcretenessChanged(const ribi::pvdb::Concept* concept)
{
  assert(concept);
  if (ui->box_concreteness->currentIndex() != concept->GetRatingConcreteness())
  {
    ui->box_concreteness->setCurrentIndex(concept->GetRatingConcreteness());
  }
}

void ribi::pvdb::QtPvdbRateConceptDialog::OnRatingSpecificityChanged(const ribi::pvdb::Concept* concept)
{
  assert(concept);
  if (ui->box_specificity->currentIndex() != concept->GetRatingSpecificity())
  {
    ui->box_specificity->setCurrentIndex(concept->GetRatingSpecificity());
  }
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbRateConceptDialog::Test()
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
  TRACE("Started ribi::pvdb::QtPvdbRateConceptDialog::Test");

  {
    const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > concept_maps
      = ribi::pvdb::ConceptMapFactory::GetAllTests();
    const std::size_t n_concept_maps = concept_maps.size();
    for (std::size_t i=0; i!=n_concept_maps; ++i)
    {
      const boost::shared_ptr<ribi::pvdb::ConceptMap> concept_map = concept_maps[i];
      if (!concept_map)
      {
        QtPvdbRateConceptDialog d(concept_map);
        continue;
      }
      assert(concept_map);
      const boost::shared_ptr<ribi::pvdb::Concept> concept = concept_map->GetNodes().at(0)->GetConcept();
      assert(concept);
      const boost::shared_ptr<ribi::pvdb::Concept> old_concept = ribi::pvdb::ConceptFactory::DeepCopy(concept);
      assert(old_concept);
      assert(concept != old_concept);
      assert(IsEqual(*concept,*old_concept));
      {
        QtPvdbRateConceptDialog d(concept_map);
        assert(concept->GetRatingComplexity() == d.ui->box_complexity->currentIndex());
        assert(concept->GetRatingConcreteness() == d.ui->box_concreteness->currentIndex());
        assert(concept->GetRatingSpecificity() == d.ui->box_specificity->currentIndex());
        //Change all boxes
        d.ui->box_complexity->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
        d.ui->box_concreteness->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
        d.ui->box_specificity->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
        //But do not click OK
        d.close();
        //Need to call the destructor
      }
      assert(IsEqual(*concept,*old_concept) && "Without clicking OK, QtPvdbRateConceptDialog must not change the concept");
    }
  }
  {
    const std::vector<boost::shared_ptr<ribi::pvdb::ConceptMap> > concept_maps
      = ribi::pvdb::ConceptMapFactory::GetAllTests();
    const std::size_t n_concept_maps = concept_maps.size();
    for (std::size_t i=0; i!=n_concept_maps; ++i)
    {
      const boost::shared_ptr<ribi::pvdb::ConceptMap> concept_map = concept_maps[i];
      if (!concept_map)
      {
        QtPvdbRateConceptDialog d(concept_map);
        continue;
      }
      assert(concept_map);
      const boost::shared_ptr<ribi::pvdb::Concept> concept = concept_map->GetNodes().at(0)->GetConcept();
      assert(concept);
      const boost::shared_ptr<const ribi::pvdb::Concept> old_concept = ribi::pvdb::ConceptFactory::DeepCopy(concept);

      assert(old_concept);
      assert(concept != old_concept);
      assert(IsEqual(*concept,*old_concept));
      QtPvdbRateConceptDialog d(concept_map);
      assert(concept->GetRatingComplexity()   == d.ui->box_complexity->currentIndex());
      assert(concept->GetRatingConcreteness() == d.ui->box_concreteness->currentIndex());
      assert(concept->GetRatingSpecificity()  == d.ui->box_specificity->currentIndex());
      //Change all boxes, in range [-1,2]
      d.ui->box_complexity->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
      d.ui->box_concreteness->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
      d.ui->box_specificity->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
      d.ui->button_ok->click();
      assert(!IsEqual(*concept,*old_concept) && "QtPvdbRateConceptDialog must change the concept when clicked OK");
    }
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
  TRACE("Finished ribi::pvdb::QtPvdbRateConceptDialog::Test successfully");
}
#endif

void ribi::pvdb::QtPvdbRateConceptDialog::on_button_tally_relevancies_clicked()
{
  #ifndef NDEBUG
  const bool has_concept_map = m_sub_concept_map.get(); //.get() needed for crosscompiler
  #endif
  QtPvdbRateConceptTallyDialog d(m_sub_concept_map);
  d.exec(); //Keep this dialog visible, as of 2013-08-30
  assert(has_concept_map == static_cast<bool>(m_sub_concept_map.get()));
  ui->box_complexity->setCurrentIndex(d.GetSuggestedComplexity());
  ui->box_concreteness->setCurrentIndex(d.GetSuggestedConcreteness());
  ui->box_specificity->setCurrentIndex(d.GetSuggestedSpecificity());
}

void ribi::pvdb::QtPvdbRateConceptDialog::on_box_complexity_currentIndexChanged(int)
{
  assert(m_concept);
  if (m_concept->GetRatingComplexity() != ui->box_complexity->currentIndex())
  {
    m_concept->SetRatingComplexity(ui->box_complexity->currentIndex());
  }
}

void ribi::pvdb::QtPvdbRateConceptDialog::on_box_concreteness_currentIndexChanged(int)
{
  assert(m_concept);
  if (m_concept->GetRatingConcreteness() != ui->box_concreteness->currentIndex())
  {
    m_concept->SetRatingConcreteness(ui->box_concreteness->currentIndex());
  }
}

void ribi::pvdb::QtPvdbRateConceptDialog::on_box_specificity_currentIndexChanged(int)
{
  assert(m_concept);
  if (m_concept->GetRatingSpecificity() != ui->box_specificity->currentIndex())
  {
    m_concept->SetRatingSpecificity(ui->box_specificity->currentIndex());
  }
}
