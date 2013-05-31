//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtcodetohtmlmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "codetohtmlmenudialog.h"
#include "qtaboutdialog.h"
#include "qtcodetohtmlmaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qtcodetohtmlmenudialog.h"

QtCodeToHtmlMenuDialog::QtCodeToHtmlMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCodeToHtmlMenuDialog)
{
  ui->setupUi(this);
}

QtCodeToHtmlMenuDialog::~QtCodeToHtmlMenuDialog()
{
  delete ui;
}

void QtCodeToHtmlMenuDialog::changeEvent(QEvent *e)
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

void QtCodeToHtmlMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtCodeToHtmlMenuDialog::on_button_about_clicked()
{
  About a = CodeToHtmlMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtCodeToHtmlMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtCodeToHtmlMenuDialog::on_button_start_clicked()
{
  //Make a screenshot
  //QPixmap::grabWidget(this,this->window()->rect()).save("ToolCodeToHtmlMenuDialog.png");

  QtCodeToHtmlMainDialog d;
  ShowChild(&d);
}

