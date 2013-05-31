//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2012 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtbeerwantermaindialog.h"

#include <iostream>
//---------------------------------------------------------------------------
#include "beerwantermaindialog.h"
#include "qtbeerwanterwidget.h"
#include "ui_qtbeerwantermaindialog.h"
//---------------------------------------------------------------------------
QtBeerWanterMainDialog::QtBeerWanterMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtBeerWanterMainDialog),
    m_widget(new QtBeerWanterWidget)
{
  ui->setupUi(this);
  ui->beerwanter_layout->addWidget(m_widget.get());
  this->setGeometry(
    m_widget->GetBeerWanter()->GetWindowX(),
    m_widget->GetBeerWanter()->GetWindowY(),
    m_widget->GetBeerWanter()->GetWindowWidth(),
    m_widget->GetBeerWanter()->GetWindowHeight());

  QObject::connect(m_widget.get(),SIGNAL(LevelUp(const std::string&)),
    this,SLOT(ChangeTitle(const std::string&)));
  QObject::connect(m_widget.get(),SIGNAL(DoShake(const int,const int)),
    this,SLOT(OnShake(const int,const int)));
}
//---------------------------------------------------------------------------
QtBeerWanterMainDialog::~QtBeerWanterMainDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtBeerWanterMainDialog::ChangeTitle(const std::string& title)
{
  this->setWindowTitle(title.c_str());
}
//---------------------------------------------------------------------------
void QtBeerWanterMainDialog::OnShake(const int x, const int y)
{
  this->setGeometry(x,y,this->width(),this->height());
  this->repaint();
}
//---------------------------------------------------------------------------
