//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2012  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrandomcodemaindialog.h"

#include <string>
#include <vector>

#include <boost/foreach.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "about.h"
#include "qtaboutdialog.h"
#include "ui_qtrandomcodemaindialog.h"
#include "randomcode.h"
#include "randomcodemenudialog.h"

QtRandomCodeMainDialog::QtRandomCodeMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRandomCodeMainDialog)
{
  ui->setupUi(this);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry( screen.adjusted(64,64,-64,-64));
  this->move( screen.center() - this->rect().center() );

  ui->button_generate->click();
}

QtRandomCodeMainDialog::~QtRandomCodeMainDialog()
{
  delete ui;
}

void QtRandomCodeMainDialog::changeEvent(QEvent *e)
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


void QtRandomCodeMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtRandomCodeMainDialog::on_button_generate_clicked()
{
  const std::vector<std::string> v = RandomCode::CreateRandomCode();
  ui->textEdit->clear();
  BOOST_FOREACH(const std::string& s, v)
  {
    ui->textEdit->append(s.c_str());
  }
}

void QtRandomCodeMainDialog::on_button_about_clicked()
{
  About about = RandomCodeMenuDialog::GetAbout();
  //about.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  this->hide();
  d.exec();
  this->show();
}

