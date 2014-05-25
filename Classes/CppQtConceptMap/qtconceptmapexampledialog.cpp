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
  m_example{}
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

  const auto example
    = ExampleFactory().Create("QtExampleDialog initial example",Competency::uninitialized,false,false,false);
  this->SetExample(example);
}

ribi::cmap::QtExampleDialog::~QtExampleDialog()
{
  delete ui;
}

void ribi::cmap::QtExampleDialog::SetExample(const boost::shared_ptr<Example>& example)
{
  const bool verbose = true;

  assert(example);
  if (m_example == example)
  {
    assert(!"?Should not get here");
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting example '" << example->ToStr() << "'\n";
  }

  const Competency competency_after = example->GetCompetency();
  const bool is_complex_after = example->GetIsComplex();
  const bool is_concrete_after = example->GetIsConcrete();
  const bool is_specific_after = example->GetIsSpecific();
  const std::string text_after = example->GetText();


  bool competency_changed  = true;
  bool is_complex_changed  = true;
  bool is_concrete_changed = true;
  bool is_specific_changed = true;
  bool text_changed = true;

  if (m_example)
  {
    const Competency competency_before = m_example->GetCompetency();
    const bool is_complex_before = m_example->GetIsComplex();
    const bool is_concrete_before = m_example->GetIsConcrete();
    const bool is_specific_before = m_example->GetIsSpecific();
    const std::string text_before = m_example->GetText();

    competency_changed  = competency_before != competency_after;
    is_complex_changed  = is_complex_before != is_complex_after;
    is_concrete_changed = is_concrete_before != is_concrete_after;
    is_specific_changed = is_specific_before != is_specific_after;
    text_changed = text_before != text_after;


    if (verbose)
    {
      if (competency_changed)
      {
        std::stringstream s;
        s
          << "Competency will change from "
          << Competencies().ToStr(competency_before)
          << " to "
          << Competencies().ToStr(competency_after)
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
      if (is_concrete_changed)
      {
        std::stringstream s;
        s << "IsConcrete will change from " << is_concrete_before
          << " to " << is_concrete_after << '\n';
        TRACE(s.str());
      }
      if (is_specific_changed)
      {
        std::stringstream s;
        s << "IsSpecific will change from " << is_specific_before
          << " to " << is_specific_after << '\n';
        TRACE(s.str());
      }
      if (text_changed)
      {
        std::stringstream s;
        s << "Text will change from '" << text_before
          << "' to '" << text_after << "'\n";
        TRACE(s.str());
      }
    }

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
  }

  //Replace m_example by the new one
  m_example = example;


  assert(m_example->GetCompetency() == competency_after );
  assert(m_example->GetIsComplex()  == is_complex_after );
  assert(m_example->GetIsConcrete() == is_concrete_after);
  assert(m_example->GetIsSpecific() == is_specific_after);
  assert(m_example->GetText()       == text_after       );

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

  //Emit everything that has changed
  if (competency_changed)
  {
    m_example->m_signal_competency_changed(m_example.get()); //RECURSIVE ERROR #2 HIERO
  }
  if (is_complex_changed)
  {
    m_example->m_signal_is_complex_changed(m_example.get());
  }
  if (is_concrete_changed)
  {
    m_example->m_signal_is_concrete_changed(m_example.get());
  }
  if (is_specific_changed)
  {
    m_example->m_signal_is_specific_changed(m_example.get());
  }
  if (text_changed)
  {
    m_example->m_signal_text_changed(m_example.get());
  }
  assert( example ==  m_example);
  assert(*example == *m_example);
}

void ribi::cmap::QtExampleDialog::OnCompetencyChanged(const Example * const example)
{
  const bool verbose = true;
  assert(example);

  const int index_before = ui->box_competency->currentIndex();
  const int index_after = Competencies().ToIndex(example->GetCompetency());
  assert(index_after >= 0);
  assert(index_after < static_cast<int>(Competencies().GetAllCompetencies().size()));

  if (verbose)
  {
    std::stringstream s;
    s << "Change competency index from " << index_before << " to " << index_after;
    TRACE(s.str());
  }

  ui->box_competency->setCurrentIndex(index_after);
  assert(ui->box_competency->currentIndex() == index_after);
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
  const bool verbose = true;

  if (!m_example)
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
    s << "QtExampleDialog will set competency " << Competencies().ToStr(competency)
      << " (index " << index << ", current competency is "
      << (m_example ? Competencies().ToStr(m_example->GetCompetency()) : "[nullptr]")
      << ")";
    TRACE(s.str());
  }
  //Let the Example figure out itself if this changes anything;
  //Allow setting a new competency if it equals the current
  m_example->SetCompetency(competency);

  assert(m_example->GetCompetency() == competency);
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
