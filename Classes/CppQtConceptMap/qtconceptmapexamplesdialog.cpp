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
#include "trace.h"
#include "ui_qtconceptmapexamplesdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtExamplesDialog::QtExamplesDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtExamplesDialog),
    m_dialogs{},
    m_examples{}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  this->SetExamples(ExamplesFactory().GetTest(0));
}

ribi::cmap::QtExamplesDialog::~QtExamplesDialog()
{
  delete ui;
}

void ribi::cmap::QtExamplesDialog::OnExamplesChanged(Examples* examples) noexcept
{
  const bool verbose = true;

  //if (examples == m_examples.get()) return; //Will allways be true
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

  if (layout()) delete layout();
  assert(!layout());

  m_dialogs.clear();
  assert(m_dialogs.empty());

  QVBoxLayout * const layout = new QVBoxLayout;

  if (verbose)
  {
    std::stringstream s;
    s << "QtExamplesDialog setting " << examples->Get().size() << " Example instances";
    TRACE(s.str());
  }
  assert(examples);
  int index = 0;
  for (auto example: examples->Get())
  {
    {
      QLabel * label = new QLabel;
      const std::string text = "Example index " + boost::lexical_cast<std::string>(index);
      label->setText(text.c_str());
      layout->addWidget(label);

      ++index;
    }

    assert(example);
    boost::shared_ptr<QtExampleDialog> dialog(new QtExampleDialog);
    m_dialogs.push_back(dialog);
    if (verbose)
    {
      std::stringstream s;
      s << "QtExamplesDialog will set Example '" << example->ToStr() << "'\n";
      TRACE(s.str());
    }
    dialog->SetExample(example); //RECURSIVE ERROR #2 HIERO
    assert( example ==  dialog->GetExample());
    assert(*example == *dialog->GetExample());
    //assert(!"Yay, recursive error issue 1/2? is fixed!");
    layout->addWidget(dialog.get());
  }

  this->setLayout(layout);
}

void ribi::cmap::QtExamplesDialog::SetExamples(const boost::shared_ptr<Examples>& examples)
{
  //const bool verbose = true;
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
    m_examples->m_signal_examples_changed(m_examples.get());
  }
}

#ifndef NDEBUG
void ribi::cmap::QtExamplesDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::cmap::QtExamplesDialog::Test");
  QtExamplesDialog d;
  for (auto examples: ExamplesFactory().GetTests())
  {
    d.SetExamples(examples);
    assert(d.GetExamples() == examples);
  }
  TRACE("ribi::cmap::QtExamplesDialog::Test finished successfully");
}
#endif
