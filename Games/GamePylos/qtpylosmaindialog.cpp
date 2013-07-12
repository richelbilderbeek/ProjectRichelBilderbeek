
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2012 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/GamePylos.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpylosmaindialog.h"

#include <QDesktopWidget>

#include "pylosgame.h"
#include "qtpyloswondialog.h"
#include "ui_qtpylosmaindialog.h"

QtPylosMainDialog::QtPylosMainDialog(
  QtPylosGameWidget * const pylos_widget,
  QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::QtPylosMainDialog),
    m_pylos_widget(pylos_widget ? pylos_widget : new QtPylosGameWidget)
{
  ui->setupUi(this);

  //Connect
  QObject::connect(m_pylos_widget,SIGNAL(HasWinner()),
    this,SLOT(OnWinner()));

  //Place widget
  this->layout()->addWidget(m_pylos_widget);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(
    0,0,256,256);
  this->move( screen.center() - this->rect().center() );
}

QtPylosMainDialog::~QtPylosMainDialog()
{
  delete ui;
  delete m_pylos_widget;
}

void QtPylosMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

const std::string QtPylosMainDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> QtPylosMainDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-09-22: version 1.0: initial release version");
  v.push_back("2012-05-28: version 2.0: improved version to work with ProjectRichelBilderbeek");
  return v;
}

void QtPylosMainDialog::OnWinner()
{
  QtPylosWonDialog d;
  d.SetWinner(m_pylos_widget->GetPylos()->GetWinner());
  d.exec();
  close();
}


