//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtconnectthreemenudialog.h"


#include "connectthreemenudialog.h"
#include "qtaboutdialog.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreewidget.h"
#include "qtselectplayerwidget.h"
#include "ui_qtconnectthreemenudialog.h"
//---------------------------------------------------------------------------
QtConnectThreeMenuDialog::QtConnectThreeMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtConnectThreeMenuDialog),
    m_select(new QtSelectPlayerWidget)
{
  ui->setupUi(this);
  ui->layout_horizontal->addWidget(m_select.get());
}
//---------------------------------------------------------------------------
QtConnectThreeMenuDialog::~QtConnectThreeMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtConnectThreeMenuDialog::changeEvent(QEvent *e)
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
//---------------------------------------------------------------------------
void QtConnectThreeMenuDialog::mousePressEvent(QMouseEvent *)
{
  if (ui->label_start->underMouse()) { OnClickStart(); }
  else if (ui->label_about->underMouse()) { OnClickAbout(); }
  else if (ui->label_quit->underMouse()) { this->close(); }
}
//---------------------------------------------------------------------------
void QtConnectThreeMenuDialog::OnClickAbout()
{
  About about = ConnectThreeMenuDialog::GetAbout();
  about.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtConnectThreeMenuDialog::OnClickStart()
{
  QtConnectThreeGameDialog d(0,this->m_select->GetIsPlayerHuman());
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
