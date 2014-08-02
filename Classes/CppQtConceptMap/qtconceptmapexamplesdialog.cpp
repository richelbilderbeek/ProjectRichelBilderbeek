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
#include "qtconceptmapexamplesdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>

#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamplesfactory.h"
#include "qtconceptmapexampledialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtconceptmapexamplesdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtExamplesDialog::QtExamplesDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    m_signal_qtexamplesdialog_changed{},
    ui(new Ui::QtExamplesDialog),
    m_dialogs{},
    m_examples{}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::cmap::QtExamplesDialog::~QtExamplesDialog()
{
  delete ui;
}

int ribi::cmap::QtExamplesDialog::GetMinimumHeight(const Examples& examples) noexcept
{
  int height = 0;
  for (const auto example: examples.Get())
  {
    const int margin = 16;
    height += QtExampleDialog::GetMinimumHeight(*example);
    height += margin;
  }
  return height;
}

void ribi::cmap::QtExamplesDialog::OnExamplesChanged(Examples* examples) noexcept
{
  const bool verbose{false};

  //if (examples == m_examples.get()) return; //Will allways be true

  //Check if the dialog needs to change
  {
    bool will_change = false;
    if (examples->Get().size() != m_dialogs.size())
    {
      will_change = true;
    }
    else
    {
      const int n = static_cast<int>(examples->Get().size());
      for (int i=0; i!=n; ++i)
      {
        if (m_dialogs[i]->GetExample() != examples->Get()[i])
        {
          will_change = true;
        }
      }
    }
    if (!will_change) return;
  }

  //Creating the right number of QtExampleDialog instances
  assert(examples);
  while (examples->Get().size() < m_dialogs.size())
  {
    //Need to remove m_dialogs
    assert(layout());
    layout()->removeWidget(m_dialogs.back().get());
    m_dialogs.pop_back();

    if (verbose)
    {
      std::stringstream s;
      s << "QtExamplesDialog removed an Example instance";
      TRACE(s.str());
    }
  }
  while (examples->Get().size() > m_dialogs.size())
  {
    boost::shared_ptr<QtExampleDialog> dialog(new QtExampleDialog);
    assert(layout());
    layout()->addWidget(dialog.get());
    m_dialogs.push_back(dialog);

    if (verbose)
    {
      std::stringstream s;
      s << "QtExamplesDialog added an Example instance";
      TRACE(s.str());
    }
  }
  assert(examples->Get().size() == m_dialogs.size());


  const int n = static_cast<int>(m_dialogs.size());
  for (int i=0; i!=n; ++i)
  {
    assert(m_dialogs[i]);
    assert(examples->Get()[i]);
    m_dialogs[i]->SetExample(examples->Get()[i]);
    if (verbose)
    {
      std::stringstream s;
      s << "QtExamplesDialog will set Example '" << examples->Get()[i]->ToStr() << "'\n";
      TRACE(s.str());
    }
    assert( examples->Get()[i] ==  m_dialogs[i]->GetExample());
    assert(*examples->Get()[i] == *m_dialogs[i]->GetExample());
  }

}

void ribi::cmap::QtExamplesDialog::SetExamples(const boost::shared_ptr<Examples>& examples)
{
  //const bool verbose{false};
  assert(examples);

  if (m_examples == examples) return;

  bool examples_changed = true;
  if (m_examples)
  {
    examples_changed = *m_examples != *examples;

    //Disconnect m_examples
    m_examples->m_signal_examples_changed.disconnect(
      boost::bind(&ribi::cmap::QtExamplesDialog::OnExamplesChanged,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_examples = examples;

  m_examples->m_signal_examples_changed.connect(
    boost::bind(&ribi::cmap::QtExamplesDialog::OnExamplesChanged,this,boost::lambda::_1)
  );
  //Emit that everything has changed
  if (examples_changed)
  {
    //For those interested in m_examples
    m_examples->m_signal_examples_changed(m_examples.get());

    //For those interested in this dialog
    m_signal_qtexamplesdialog_changed(this);
  }

  assert( m_examples ==  examples);
  assert(*m_examples == *examples);
  this->setMinimumHeight(GetMinimumHeight(*m_examples));
}

#ifndef NDEBUG
void ribi::cmap::QtExamplesDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtExamplesDialog d;
  for(const auto examples: ExamplesFactory().GetTests())
  {
    d.SetExamples(examples);
    assert(d.GetExamples() == examples);
  }
}
#endif
