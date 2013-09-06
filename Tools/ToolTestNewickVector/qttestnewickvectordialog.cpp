//---------------------------------------------------------------------------
/*
TestNewickVector, GUI tool to test NewickVector
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestNewickVector.htm
//---------------------------------------------------------------------------


#include "qttestnewickvectordialog.h"


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#pragma GCC diagnostic pop
//---------------------------------------------------------------------------
#include <QTimer>
//---------------------------------------------------------------------------
#include "BigIntegerLibrary.hh"
//---------------------------------------------------------------------------
#include "about.h"
#include "binarynewickvector.h"
#include "testnewickvectordialog.h"
#include "newick.h"
#include "newickvector.h"
#include "qtaboutdialog.h"
#include "ui_qttestnewickvectordialog.h"
//---------------------------------------------------------------------------
///QtTestNewickVectorDialog constructor performs most Newick tests
ribi::QtTestNewickVectorDialog::QtTestNewickVectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestNewickVectorDialog),
    m_timer(new QTimer),
    m_dialog(new TestNewickVectorDialog)
{
  ui->setupUi(this);
  QObject::connect(
    ui->edit_newick,SIGNAL(textChanged(QString)),
    this,SLOT(OnAnyChange()));
  QObject::connect(
    ui->edit_theta,SIGNAL(textChanged(QString)),
    this,SLOT(OnAnyChange()));
  QObject::connect(
    ui->edit_max_complexity,SIGNAL(textChanged(QString)),
    this,SLOT(OnAnyChange()));
  QObject::connect(
    ui->box_show_calculation,SIGNAL(clicked()),
    this,SLOT(OnAnyChange()));
  QObject::connect(
    ui->box_compare,SIGNAL(clicked()),
    this,SLOT(OnAnyChange()));


  QObject::connect(
    m_timer,SIGNAL(timeout()),
    this,SLOT(OnDemoTick()));

  #ifndef NDEBUG
  setWindowTitle(windowTitle()+" (debug)");
  #else
  setWindowTitle(windowTitle()+" (release)");
  #endif

  this->OnAnyChange();
}
//---------------------------------------------------------------------------
ribi::QtTestNewickVectorDialog::~QtTestNewickVectorDialog()
{
  m_timer->stop();
  delete ui;
  delete m_timer;
}
//---------------------------------------------------------------------------

void ribi::QtTestNewickVectorDialog::Display()
{
  ui->edit_text->clear();
  const std::vector<std::string>& text = m_dialog->GetText();
  ui->edit_text->clear();
  BOOST_FOREACH(const std::string& s,text)
  {
    ui->edit_text->appendPlainText(s.c_str());
  }
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::OnAnyChange()
{
  m_dialog->SetMaxComplexity(ui->edit_max_complexity->text().toStdString());
  m_dialog->SetNewick(ui->edit_newick->text().toStdString());
  m_dialog->SetTheta(ui->edit_theta->text().toStdString());
  m_dialog->AutoCalculate();
  Display();
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::OnDemoTick()
{
  //Get any Newick
  if ((std::rand() >> 4) % 2)
  {
    const std::vector<std::string> v = Newick::CreateValidNewicks();
    const std::string s = v[std::rand() % v.size()];
    ui->edit_newick->setText(QString(s.c_str()));
  }
  else
  {
    const std::vector<std::string> v = Newick::CreateInvalidNewicks();
    const std::string s = v[std::rand() % v.size()];
    ui->edit_newick->setText(QString(s.c_str()));
  }
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::on_button_demo_clicked()
{
  if (m_timer->isActive())
  {
    m_timer->stop();
    assert(!m_timer->isActive());
    ui->button_demo->setText("&Start demo");
  }
  else
  {
    m_timer->start(100);
    assert(m_timer->isActive());
    ui->button_demo->setText("&Stop demo");
  }
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestNewickVectorDialog::GetAbout());
  d.exec();
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::on_button_calculate_clicked()
{
  m_dialog->SetMaxComplexity(ui->edit_max_complexity->text().toStdString());
  m_dialog->SetNewick(ui->edit_newick->text().toStdString());
  m_dialog->SetTheta(ui->edit_theta->text().toStdString());
  m_dialog->Calculate();
  Display();
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::on_box_show_calculation_clicked()
{
  m_dialog->SetAnalyseCalculation(ui->box_show_calculation->isChecked());
  ui->box_compare->setEnabled( ui->box_show_calculation->isChecked() );
}
//---------------------------------------------------------------------------
void ribi::QtTestNewickVectorDialog::on_box_compare_clicked()
{
  m_dialog->SetCompareToTwoDigitNewick(ui->box_compare->isChecked());
}
//---------------------------------------------------------------------------
