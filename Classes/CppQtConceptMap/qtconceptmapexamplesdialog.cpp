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

#include <QLayout>
#include <QVBoxLayout>

#include "conceptmapexamples.h"
#include "conceptmapexamplesfactory.h"
#include "qtconceptmapexampledialog.h"
#include "trace.h"
#include "ui_qtconceptmapexamplesdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtExamplesDialog::QtExamplesDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtExamplesDialog),
    m_examples{ExamplesFactory().GetTest(0)}
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

void ribi::cmap::QtExamplesDialog::OnExamplesChanged(Examples* examples) noexcept
{
  //if (layout()) delete layout();
  QVBoxLayout * const layout = new QVBoxLayout;
  for (boost::shared_ptr<Example> example: examples->Get())
  {
    QtExampleDialog * const d = new QtExampleDialog;
    d->SetExample(example); //RECURSIVE ERROR HIERO
    layout->addWidget(d);
  }

  this->setLayout(layout);
}

void ribi::cmap::QtExamplesDialog::SetExamples(const boost::shared_ptr<Examples>& examples)
{
  if (m_examples == examples) return;

  const bool examples_changed = *m_examples == *examples;

  //Disconnect m_examples
  m_examples->m_signal_examples_changed.disconnect(
    boost::bind(&ribi::cmap::QtExamplesDialog::OnExamplesChanged,this,boost::lambda::_1)
  );

  //Replace m_example by the new one
  m_examples = examples;

  m_examples->m_signal_examples_changed.connect(
    boost::bind(&ribi::cmap::QtExamplesDialog::OnExamplesChanged,this,boost::lambda::_1)
  );
  //Emit that everything has changed
  if (examples_changed) m_examples->m_signal_examples_changed(m_examples.get());
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
  //QtExampleDialog d;
  TRACE("ribi::cmap::QtExamplesDialog::Test finished successfully");
}
#endif
