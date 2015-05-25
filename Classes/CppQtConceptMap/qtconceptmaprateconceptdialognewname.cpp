//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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
#include "qtconceptmaprateconceptdialognewname.h"

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "testtimer.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapexamples.h"
//#include "conceptmapfile.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtrateconceptmap.h"
#include "qtconceptmaprating.h"
#include "qtrateconceptmap.h"
#include "qtconceptmaprateconcepttallydialognewname.h"
#include "trace.h"
#include "ui_qtconceptmaprateconceptdialognewname.h"
#pragma GCC diagnostic pop

ribi::cmap::QtRateConceptDialogNewName::QtRateConceptDialogNewName(
  const boost::shared_ptr<ribi::cmap::ConceptMap> sub_concept_map,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtRateConceptDialogNewName),
    m_button_ok_clicked(false),
    m_concept(sub_concept_map
      ? sub_concept_map->GetFocalNode()->GetConcept()
      : boost::shared_ptr<Concept>() ),
    m_initial_complexity(sub_concept_map
      ? sub_concept_map->GetFocalNode()->GetConcept()->GetRatingComplexity()
      : -1 ),
    m_initial_concreteness(sub_concept_map
      ? sub_concept_map->GetFocalNode()->GetConcept()->GetRatingConcreteness()
      : -1),
    m_initial_specificity(sub_concept_map
      ? sub_concept_map->GetFocalNode()->GetConcept()->GetRatingSpecificity()
      : -1),

    m_sub_concept_map(sub_concept_map),
    m_widget(new QtRateConceptMap(sub_concept_map))
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  if (!m_sub_concept_map) return;
  assert(m_sub_concept_map);
  assert(!m_sub_concept_map->GetNodes().empty());

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
      + boost::lexical_cast<std::string>(cmap::Rating::SuggestComplexity(m_sub_concept_map));
    ui->box_complexity->setToolTip(s.c_str());
  }
  {
    const std::string s = "Formeel uitgangspunt: "
      + boost::lexical_cast<std::string>(cmap::Rating::SuggestConcreteness(m_sub_concept_map));
    ui->box_concreteness->setToolTip(s.c_str());
  }
  {
    const std::string s = "Formeel uitgangspunt: "
      + boost::lexical_cast<std::string>(cmap::Rating::SuggestSpecificity(m_sub_concept_map));
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
  //  boost::bind(&QtRateStrategyDialog::OnRatingComplexityChanged,this,boost::lambda::_1));
  //m_concept->m_signal_rating_concreteness_changed.connect(
  //  boost::bind(&QtRateStrategyDialog::OnRatingConcretenessChanged,this,boost::lambda::_1));
  //m_concept->m_signal_rating_specificity_changed.connect(
  //  boost::bind(&QtRateStrategyDialog::OnRatingSpecificityChanged,this,boost::lambda::_1));
}



ribi::cmap::QtRateConceptDialogNewName::~QtRateConceptDialogNewName() noexcept
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
  //    boost::bind(&QtRateStrategyDialog::OnRatingComplexityChanged,this,boost::lambda::_1));
  //  m_concept->m_signal_rating_concreteness_changed.disconnect(
  //    boost::bind(&QtRateStrategyDialog::OnRatingConcretenessChanged,this,boost::lambda::_1));
  //  m_concept->m_signal_rating_specificity_changed.disconnect(
  //    boost::bind(&QtRateStrategyDialog::OnRatingSpecificityChanged,this,boost::lambda::_1));
  //}
  delete ui;
}

void ribi::cmap::QtRateConceptDialogNewName::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_T)
  {
    //Translate
    this->setWindowTitle("Assess cluster");
    ui->button_ok->setText("OK");
    ui->button_tally_relevancies->setText("Evaluate illustrations");
    ui->label_complexity->setText("Complexity");
    ui->label_concreteness->setText("Concreteness");
    ui->label_specificity->setText("Specificity");
/*

De relevantie van voorbeelden en relaties		Relevance of illustrations
Voorbeelden/toelichting bij concept: Illustrations and relations of the cluster:

*/
    return;
  }

  //QDialog::keyPressEvent(e);
}

void ribi::cmap::QtRateConceptDialogNewName::on_button_ok_clicked()
{
  //Ratings already set by comboboxes
  m_button_ok_clicked = true;
  close();
}

void ribi::cmap::QtRateConceptDialogNewName::OnRatingComplexityChanged(const ribi::cmap::Concept* concept)
{
  assert(concept);
  if (ui->box_complexity->currentIndex() != concept->GetRatingComplexity())
  {
    ui->box_complexity->setCurrentIndex(concept->GetRatingComplexity());
  }
}

void ribi::cmap::QtRateConceptDialogNewName::OnRatingConcretenessChanged(const ribi::cmap::Concept* concept)
{
  assert(concept);
  if (ui->box_concreteness->currentIndex() != concept->GetRatingConcreteness())
  {
    ui->box_concreteness->setCurrentIndex(concept->GetRatingConcreteness());
  }
}

void ribi::cmap::QtRateConceptDialogNewName::OnRatingSpecificityChanged(const ribi::cmap::Concept* concept)
{
  assert(concept);
  if (ui->box_specificity->currentIndex() != concept->GetRatingSpecificity())
  {
    ui->box_specificity->setCurrentIndex(concept->GetRatingSpecificity());
  }
}

#ifndef NDEBUG
void ribi::cmap::QtRateConceptDialogNewName::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer{__func__,__FILE__,0.1};
  #ifdef RJCB_TODO //TODO RJCB: Put back in
  {
    const std::vector<boost::shared_ptr<ConceptMap> > concept_maps
      = ConceptMapFactory::GetAllTests();
    const std::size_t n_concept_maps = concept_maps.size();
    for (std::size_t i=0; i!=n_concept_maps; ++i)
    {
      const boost::shared_ptr<ConceptMap> concept_map = concept_maps[i];
      if (!concept_map)
      {
        QtRateConceptDialogNewName d(concept_map);
        continue;
      }
      assert(concept_map);
      const boost::shared_ptr<Concept> concept = concept_map->GetFocalNode()->GetConcept();
      assert(concept);
      const boost::shared_ptr<Concept> old_concept = ConceptFactory().DeepCopy(concept);
      assert(old_concept);
      assert(concept != old_concept);
      assert(*concept == *old_concept);
      {
        QtRateConceptDialogNewName d(concept_map);
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
      assert(*concept == *old_concept && "Without clicking OK, QtRateStrategyDialog must not change the concept");
    }
  }
  {
    const std::vector<boost::shared_ptr<ConceptMap> > concept_maps
      = ConceptMapFactory::GetAllTests();
    const std::size_t n_concept_maps = concept_maps.size();
    for (std::size_t i=0; i!=n_concept_maps; ++i)
    {
      const boost::shared_ptr<ConceptMap> concept_map = concept_maps[i];
      if (!concept_map)
      {
        QtRateConceptDialogNewName d(concept_map);
        continue;
      }
      assert(concept_map);
      const boost::shared_ptr<Concept> concept = concept_map->GetFocalNode()->GetConcept();
      assert(concept);
      const boost::shared_ptr<const Concept> old_concept = ConceptFactory().DeepCopy(concept);

      assert(old_concept);
      assert(concept != old_concept);
      assert(*concept == *old_concept);
      QtRateConceptDialogNewName d(concept_map);
      assert(concept->GetRatingComplexity()   == d.ui->box_complexity->currentIndex());
      assert(concept->GetRatingConcreteness() == d.ui->box_concreteness->currentIndex());
      assert(concept->GetRatingSpecificity()  == d.ui->box_specificity->currentIndex());
      //Change all boxes, in range [-1,2]
      d.ui->box_complexity->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
      d.ui->box_concreteness->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
      d.ui->box_specificity->setCurrentIndex(((d.ui->box_complexity->currentIndex() + 2) % 4) - 1);
      d.ui->button_ok->click();
      assert(*concept != *old_concept && "QtRateStrategyDialog must change the concept when clicked OK");
    }
  }
  #endif

}
#endif

void ribi::cmap::QtRateConceptDialogNewName::on_button_tally_relevancies_clicked()
{
  #ifndef NDEBUG
  const bool has_concept_map = m_sub_concept_map.get(); //.get() needed for crosscompiler
  #endif
   QtRateConceptTallyDialogNewName d(m_sub_concept_map);
  d.exec(); //Keep this dialog visible, as of 2013-08-30
  assert(has_concept_map == static_cast<bool>(m_sub_concept_map.get()));
  ui->box_complexity->setCurrentIndex(d.GetSuggestedComplexity());
  ui->box_concreteness->setCurrentIndex(d.GetSuggestedConcreteness());
  ui->box_specificity->setCurrentIndex(d.GetSuggestedSpecificity());
}

void ribi::cmap::QtRateConceptDialogNewName::on_box_complexity_currentIndexChanged(int)
{
  assert(m_concept);
  if (m_concept->GetRatingComplexity() != ui->box_complexity->currentIndex())
  {
    m_concept->SetRatingComplexity(ui->box_complexity->currentIndex());
  }
}

void ribi::cmap::QtRateConceptDialogNewName::on_box_concreteness_currentIndexChanged(int)
{
  assert(m_concept);
  if (m_concept->GetRatingConcreteness() != ui->box_concreteness->currentIndex())
  {
    m_concept->SetRatingConcreteness(ui->box_concreteness->currentIndex());
  }
}

void ribi::cmap::QtRateConceptDialogNewName::on_box_specificity_currentIndexChanged(int)
{
  assert(m_concept);
  if (m_concept->GetRatingSpecificity() != ui->box_specificity->currentIndex())
  {
    m_concept->SetRatingSpecificity(ui->box_specificity->currentIndex());
  }
}
