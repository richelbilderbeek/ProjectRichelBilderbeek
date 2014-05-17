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
#include "qtconceptmapexampledialog.h"
#include "ui_qtconceptmapexampledialog.h"

#include <cassert>
#include <boost/bind/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "conceptmapcompetencies.h"
#include "conceptmapexample.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapExampleDialog::QtConceptMapExampleDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtConceptMapExampleDialog),
  m_example{}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  ///The competency, as might be judged by an assessor
  //Competency m_competency;

  ///Has an assessor rated this example as being an addition to the complexity?
  //bool m_is_complex;

  ///Has an assessor rated this example as being an addition to the concreteness?
  //bool m_is_concrete;

  ///Has an assessor rated this example as being an addition to the specificity?
  //bool m_is_specific;

  ///The text of the example
  ///For example: 'Plato', 'When I was a kid', 'As I did on holiday'
  //std::string m_text;

}

ribi::cmap::QtConceptMapExampleDialog::~QtConceptMapExampleDialog()
{
  delete ui;
}

void ribi::cmap::QtConceptMapExampleDialog::SetExample(const boost::shared_ptr<Example>& example)
{
  //Disconnect m_example

  //Replace m_example by the new one
  m_example = example;

  m_example->m_signal_competency_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapExampleDialog::OnCompetencyChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_complex_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapExampleDialog::OnIsComplexChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_concrete_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapExampleDialog::OnIsConcreteChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_specific_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapExampleDialog::OnIsSpecificChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_text_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapExampleDialog::OnTextChanged,this,boost::lambda::_1)
  );
}

void ribi::cmap::QtConceptMapExampleDialog::OnCompetencyChanged(const Example * const example)
{
  assert(example);
  ui->box_competency->setCurrentIndex(
    Competencies().ToIndex(example->GetCompetency())
  );
}

void ribi::cmap::QtConceptMapExampleDialog::OnIsComplexChanged(const Example * const example)
{
  assert(example);
  ui->box_is_complex->setChecked(example->GetIsComplex());
}

void ribi::cmap::QtConceptMapExampleDialog::OnIsConcreteChanged(const Example * const example)
{
  assert(example);
  ui->box_is_concrete->setChecked(example->GetIsConcrete());
}

void ribi::cmap::QtConceptMapExampleDialog::OnIsSpecificChanged(const Example * const example)
{
  assert(example);
  ui->box_is_specific->setChecked(example->GetIsSpecific());
}

void ribi::cmap::QtConceptMapExampleDialog::OnTextChanged(const Example * const example)
{
  assert(example);
  ui->edit_text->setText(example->GetText().c_str());

}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapExampleDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtConceptMapExampleDialog::Test");
  TRACE("ribi::cmap::QtConceptMapExampleDialog::Test finished successfully");
}
#endif
