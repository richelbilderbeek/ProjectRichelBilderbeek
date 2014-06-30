//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpylosmaindialog.h"

#include <boost/make_shared.hpp>

#include <QDesktopWidget>

#include "pylosgame.h"
#include "qtpylosgamewidget.h"
#include "qtpyloswondialog.h"
#include "ui_qtpylosmaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::pylos::QtPylosMainDialog::QtPylosMainDialog(
  const boost::shared_ptr<QtPylosGameWidget>& pylos_widget,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPylosMainDialog),
    m_pylos_widget(pylos_widget)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Connect
  QObject::connect(m_pylos_widget.get(),SIGNAL(HasWinner()),
    this,SLOT(OnWinner()));

  //Place widget
  this->layout()->addWidget(m_pylos_widget.get());

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(
    0,0,256,256);
  this->move( screen.center() - this->rect().center() );
}

ribi::pylos::QtPylosMainDialog::~QtPylosMainDialog() noexcept
{
  delete ui;
}

std::string ribi::pylos::QtPylosMainDialog::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::pylos::QtPylosMainDialog::GetVersionHistory() noexcept
{
  return {
    "2010-09-22: version 1.0: initial release version",
    "2012-05-28: version 2.0: improved version to work with ProjectRichelBilderbeek"
    "2014-06-30: version 2.1: replaced raw by smart pointer"
  };
}

void ribi::pylos::QtPylosMainDialog::OnWinner()
{
  QtPylosWonDialog d;
  d.SetWinner(m_pylos_widget->GetPylos()->GetWinner());
  this->ShowChild(&d);
  close();
}

#ifndef NDEBUG
void ribi::pylos::QtPylosMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::pylos::QtPylosMainDialog::Test");
  const boost::shared_ptr<QtPylosGameWidget> p(new QtPylosGameWidget);
  assert(p);
  //Set the game type
  p->StartBasic();
  p->SetColorSchemeBlackWhite();
  const boost::shared_ptr<QtPylosMainDialog> d(new QtPylosMainDialog(p));
  assert(!d->GetVersion().empty());
  //delete p;
  TRACE("Finished ribi::pylos::QtPylosMainDialog::Test successfully");
}
#endif
