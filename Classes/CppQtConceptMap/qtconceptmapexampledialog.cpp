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
#include "conceptmapexamplefactory.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::cmap::QtExampleDialog::QtExampleDialog(QWidget *parent) :
  ribi::QtHideAndShowDialog(parent),
  ui(new Ui::QtExampleDialog),
  m_example{ExampleFactory().GetTest(0)}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  {
    const auto v = Competencies().GetAllCompetencies();
    for (auto c: v)
    {
      const std::string s = Competencies().ToStrDutch(c);
      ui->box_competency->addItem(s.c_str());
    }
  }
}

ribi::cmap::QtExampleDialog::~QtExampleDialog()
{
  delete ui;
}

void ribi::cmap::QtExampleDialog::SetExample(const boost::shared_ptr<Example>& example)
{
  //Disconnect m_example
  m_example->m_signal_competency_changed.disconnect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnCompetencyChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_complex_changed.disconnect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsComplexChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_concrete_changed.disconnect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsConcreteChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_specific_changed.disconnect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsSpecificChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_text_changed.disconnect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnTextChanged,this,boost::lambda::_1)
  );

  //Replace m_example by the new one
  m_example = example;

  m_example->m_signal_competency_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnCompetencyChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_complex_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsComplexChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_concrete_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsConcreteChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_is_specific_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnIsSpecificChanged,this,boost::lambda::_1)
  );
  m_example->m_signal_text_changed.connect(
    boost::bind(&ribi::cmap::QtExampleDialog::OnTextChanged,this,boost::lambda::_1)
  );

  //Emit that everything has changed
  m_example->m_signal_competency_changed(m_example.get());
  m_example->m_signal_is_complex_changed(m_example.get());
  m_example->m_signal_is_concrete_changed(m_example.get());
  m_example->m_signal_is_specific_changed(m_example.get());
  m_example->m_signal_text_changed(m_example.get());
}

void ribi::cmap::QtExampleDialog::OnCompetencyChanged(const Example * const example)
{
  assert(example);
  const int index = Competencies().ToIndex(example->GetCompetency());
  assert(index >= 0);
  assert(index < static_cast<int>(Competencies().GetAllCompetencies().size()));
  ui->box_competency->setCurrentIndex(index);
}

void ribi::cmap::QtExampleDialog::OnIsComplexChanged(const Example * const example)
{
  assert(example);
  ui->box_is_complex->setChecked(example->GetIsComplex());
}

void ribi::cmap::QtExampleDialog::OnIsConcreteChanged(const Example * const example)
{
  assert(example);
  ui->box_is_concrete->setChecked(example->GetIsConcrete());
}

void ribi::cmap::QtExampleDialog::OnIsSpecificChanged(const Example * const example)
{
  assert(example);
  ui->box_is_specific->setChecked(example->GetIsSpecific());
}

void ribi::cmap::QtExampleDialog::OnTextChanged(const Example * const example)
{
  assert(example);
  ui->edit_text->setText(example->GetText().c_str());
}

#ifndef NDEBUG
void ribi::cmap::QtExampleDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtExampleDialog::Test");
  //QtExampleDialog d;
  TRACE("ribi::cmap::QtExampleDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtExampleDialog::on_box_competency_currentIndexChanged(int index)
{
  if(index < 0)
  {
    TRACE("ERROR");
  }
  assert(index >= 0);
  assert(index < static_cast<int>(Competencies().GetAllCompetencies().size()));
  const auto competency = Competencies().GetAllCompetencies()[index];
  m_example->SetCompetency(competency);
}

void ribi::cmap::QtExampleDialog::on_box_is_complex_stateChanged(int)
{
  m_example->SetIsComplex(ui->box_is_complex->isChecked());
}

void ribi::cmap::QtExampleDialog::on_box_is_concrete_stateChanged(int)
{
  m_example->SetIsConcrete(ui->box_is_concrete->isChecked());
}

void ribi::cmap::QtExampleDialog::on_box_is_specific_stateChanged(int)
{
  m_example->SetIsSpecific(ui->box_is_specific->isChecked());
}

void ribi::cmap::QtExampleDialog::on_edit_text_textChanged(const QString &arg1)
{
  m_example->SetText(arg1.toStdString());
}
