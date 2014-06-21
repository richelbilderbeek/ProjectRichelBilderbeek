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
#include "qtconceptmapconceptdialog.h"

#include <cassert>
#include <boost/bind/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "conceptmapcompetencies.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapexamples.h"
#include "conceptmapexamplesfactory.h"
#include "qtconceptmapexamplesdialog.h"
#include "trace.h"
#include "ui_qtconceptmapconceptdialog.h"

#pragma GCC diagnostic pop

ribi::cmap::QtConceptDialog::QtConceptDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtConceptDialog),
  m_concept{},
  m_qtexamplesdialog{new QtExamplesDialog}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  {
    assert(layout());
    layout()->addWidget(m_qtexamplesdialog.get());

  }

  const auto concept
    = ConceptFactory().Create("QtConceptDialog initial concept",
        ExamplesFactory().GetTest(2),true,-1,-1,-1);
  this->SetConcept(concept);
}

ribi::cmap::QtConceptDialog::~QtConceptDialog() noexcept
{
  delete ui;
}

int ribi::cmap::QtConceptDialog::GetMinimumHeight(const Concept& concept) noexcept
{
  return
      QtExamplesDialog::GetMinimumHeight(*concept.GetExamples())
    + 197
  ;
}

void ribi::cmap::QtConceptDialog::SetConcept(const boost::shared_ptr<Concept>& concept) noexcept
{
  const bool verbose = false;

  assert(concept);
  if (m_concept == concept)
  {
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting concept '" << concept->ToStr() << "'\n";
  }
  const auto examples_after = concept->GetExamples();
  const auto is_complex_after = concept->GetIsComplex();
  const auto name_after = concept->GetName();
  const auto rating_complexity_after = concept->GetRatingComplexity();
  const auto rating_concreteness_after = concept->GetRatingConcreteness();
  const auto rating_specificity_after = concept->GetRatingSpecificity();

  bool examples_changed  = true;
  bool is_complex_changed  = true;
  bool name_changed = true;
  bool rating_complexity_changed = true;
  bool rating_concreteness_changed = true;
  bool rating_specificity_changed = true;

  if (m_concept)
  {
    const auto examples_before = m_concept->GetExamples();
    const auto is_complex_before = m_concept->GetIsComplex();
    const auto name_before = m_concept->GetName();
    const auto rating_complexity_before = m_concept->GetRatingComplexity();
    const auto rating_concreteness_before = m_concept->GetRatingConcreteness();
    const auto rating_specificity_before = m_concept->GetRatingSpecificity();

    examples_changed  = examples_before != examples_after;
    is_complex_changed  = is_complex_before != is_complex_after;
    name_changed = name_before != name_after;
    rating_complexity_changed = rating_complexity_before != rating_complexity_after;
    rating_concreteness_changed = rating_concreteness_before != rating_concreteness_after;
    rating_specificity_changed = rating_specificity_before != rating_specificity_after;


    if (verbose)
    {
      if (examples_changed)
      {
        std::stringstream s;
        s
          << "Examples will change from "
          << examples_before->ToStr()
          << " to "
          << examples_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
      if (is_complex_changed)
      {
        std::stringstream s;
        s << "IsComplex will change from " << is_complex_before
          << " to " << is_complex_after << '\n';
        TRACE(s.str());
      }
      if (name_changed)
      {
        std::stringstream s;
        s << "Name will change from " << name_before
          << " to " << name_after << '\n';
        TRACE(s.str());
      }
      if (rating_complexity_changed)
      {
        std::stringstream s;
        s << "Rating_complexity will change from " << rating_complexity_before
          << " to " << rating_complexity_after << '\n';
        TRACE(s.str());
      }
      if (rating_concreteness_changed)
      {
        std::stringstream s;
        s << "Rating_concreteness_changed will change from '"
          << rating_concreteness_before
          << "' to '" << rating_concreteness_after
          << "'\n";
        TRACE(s.str());
      }
      if (rating_specificity_changed)
      {
        std::stringstream s;
        s << "Rating_specificity will change from '" << rating_specificity_before
          << "' to '" << rating_specificity_after << "'\n";
        TRACE(s.str());
      }
    }
    //Disconnect m_concept
    m_concept->m_signal_examples_changed.disconnect(
      boost::bind(&ribi::cmap::QtConceptDialog::OnExamplesChanged,this,boost::lambda::_1)
    );
    m_concept->m_signal_is_complex_changed.disconnect(
      boost::bind(&ribi::cmap::QtConceptDialog::OnIsComplexChanged,this,boost::lambda::_1)
    );
    m_concept->m_signal_name_changed.disconnect(
      boost::bind(&ribi::cmap::QtConceptDialog::OnNameChanged,this,boost::lambda::_1)
    );
    m_concept->m_signal_rating_complexity_changed.disconnect(
      boost::bind(&ribi::cmap::QtConceptDialog::OnRatingComplexityChanged,this,boost::lambda::_1)
    );
    m_concept->m_signal_rating_concreteness_changed.disconnect(
      boost::bind(&ribi::cmap::QtConceptDialog::OnRatingConcretenessChanged,this,boost::lambda::_1)
    );
    m_concept->m_signal_rating_specificity_changed.disconnect(
      boost::bind(&ribi::cmap::QtConceptDialog::OnRatingSpecificityChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_concept = concept;

  assert(m_concept->GetExamples() == examples_after );
  assert(m_concept->GetIsComplex()  == is_complex_after );
  assert(m_concept->GetName() == name_after);
  assert(m_concept->GetRatingComplexity() == rating_complexity_after);
  assert(m_concept->GetRatingConcreteness() == rating_concreteness_after);
  assert(m_concept->GetRatingSpecificity() == rating_specificity_after);

  m_concept->m_signal_examples_changed.connect(
    boost::bind(&ribi::cmap::QtConceptDialog::OnExamplesChanged,this,boost::lambda::_1)
  );
  m_concept->m_signal_is_complex_changed.connect(
    boost::bind(&ribi::cmap::QtConceptDialog::OnIsComplexChanged,this,boost::lambda::_1)
  );
  m_concept->m_signal_name_changed.connect(
    boost::bind(&ribi::cmap::QtConceptDialog::OnNameChanged,this,boost::lambda::_1)
  );
  m_concept->m_signal_rating_complexity_changed.connect(
    boost::bind(&ribi::cmap::QtConceptDialog::OnRatingComplexityChanged,this,boost::lambda::_1)
  );
  m_concept->m_signal_rating_concreteness_changed.connect(
    boost::bind(&ribi::cmap::QtConceptDialog::OnRatingConcretenessChanged,this,boost::lambda::_1)
  );
  m_concept->m_signal_rating_specificity_changed.connect(
    boost::bind(&ribi::cmap::QtConceptDialog::OnRatingSpecificityChanged,this,boost::lambda::_1)
  );

  //Emit everything that has changed
  if (examples_changed)
  {
    m_concept->m_signal_examples_changed(m_concept.get());
  }
  if (is_complex_changed)
  {
    m_concept->m_signal_is_complex_changed(m_concept.get());
  }
  if (name_changed)
  {
    m_concept->m_signal_name_changed(m_concept.get());
  }
  if (rating_complexity_changed)
  {
    m_concept->m_signal_rating_complexity_changed(m_concept.get());
  }
  if (rating_concreteness_changed)
  {
    m_concept->m_signal_rating_concreteness_changed(m_concept.get());
  }
  if (rating_specificity_changed)
  {
    m_concept->m_signal_rating_specificity_changed(m_concept.get());
  }

  setMinimumHeight(GetMinimumHeight(*m_concept));

  assert( concept ==  m_concept);
  assert(*concept == *m_concept);
}

void ribi::cmap::QtConceptDialog::OnExamplesChanged(Concept * const concept) noexcept
{
  const bool verbose = false;
  assert(concept);

  const auto examples_before = m_qtexamplesdialog->GetExamples();
  const boost::shared_ptr<Examples> examples_after = concept->GetExamples();

  if (verbose)
  {
    std::stringstream s;
    s << "Change examples from "
    << (examples_before ? examples_before->ToStr() : "[NONE]")
    << " to " << examples_after->ToStr();
    TRACE(s.str());
  }

  m_qtexamplesdialog->SetExamples(examples_after);

  assert(m_qtexamplesdialog->GetExamples() == examples_after);
}

void ribi::cmap::QtConceptDialog::OnIsComplexChanged(Concept * const concept) noexcept
{
  assert(concept);
  ui->box_is_complex->setChecked(concept->GetIsComplex());
}

void ribi::cmap::QtConceptDialog::OnNameChanged(Concept * const concept) noexcept
{
  assert(concept);
  ui->edit_name->setText(concept->GetName().c_str());
}

void ribi::cmap::QtConceptDialog::OnRatingComplexityChanged(Concept * const concept) noexcept
{
  assert(concept);
  ui->box_rating_complexity->setValue(
    concept->GetRatingComplexity()
  );
}

void ribi::cmap::QtConceptDialog::OnRatingConcretenessChanged(Concept * const concept) noexcept
{
  assert(concept);
  ui->box_rating_concreteness->setValue(
    concept->GetRatingConcreteness()
  );
}

void ribi::cmap::QtConceptDialog::OnRatingSpecificityChanged(Concept * const concept) noexcept
{
  assert(concept);
  ui->box_rating_specificity->setValue(
    concept->GetRatingSpecificity()
  );
}


#ifndef NDEBUG
void ribi::cmap::QtConceptDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtConceptDialog::Test");
  //QtConceptDialog d;
  TRACE("ribi::cmap::QtConceptDialog::Test finished successfully");
}
#endif

/*
void ribi::cmap::QtConceptDialog::on_box_competency_currentIndexChanged(int index)
{
  const bool verbose = false;

  if (!m_concept)
  {
    //Used in construction
    return;
  }

  assert(index >= 0);
  assert(index < static_cast<int>(Competencies().GetAllCompetencies().size()));
  const auto competency = Competencies().GetAllCompetencies()[index];

  if (verbose)
  {
    std::stringstream s;
    s << "QtConceptDialog will set competency " << Competencies().ToStr(competency)
      << " (index " << index << ", current competency is "
      << (m_concept ? Competencies().ToStr(m_concept->GetCompetency()) : "[nullptr]")
      << ")";
    TRACE(s.str());
  }
  //Let the Concept figure out itself if this changes anything;
  //Allow setting a new competency if it equals the current
  m_concept->SetCompetency(competency);

  assert(m_concept->GetCompetency() == competency);
}
*/

void ribi::cmap::QtConceptDialog::on_box_is_complex_stateChanged(int) noexcept
{
  //OK
  m_concept->SetIsComplex(ui->box_is_complex->isChecked());
}

void ribi::cmap::QtConceptDialog::on_edit_name_textChanged(const QString &arg1) noexcept
{
  //OK
  m_concept->SetName(arg1.toStdString());
}

void ribi::cmap::QtConceptDialog::on_box_rating_complexity_valueChanged(int arg1) noexcept
{
  m_concept->SetRatingComplexity(arg1);
}

void ribi::cmap::QtConceptDialog::on_box_rating_concreteness_valueChanged(int arg1) noexcept
{
  m_concept->SetRatingConcreteness(arg1);
}

void ribi::cmap::QtConceptDialog::on_box_rating_specificity_valueChanged(int arg1) noexcept
{
  m_concept->SetRatingSpecificity(arg1);
}
