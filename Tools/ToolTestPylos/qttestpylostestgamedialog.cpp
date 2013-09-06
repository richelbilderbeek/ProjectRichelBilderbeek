//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------


#include "qttestpylostestgamedialog.h"

#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop
//---------------------------------------------------------------------------
#include <QBitmap>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
//---------------------------------------------------------------------------
#include "pylosboard.h"
#include "pylosmove.h"
#include "pylospositionstate.h"
#include "qtpylosboardwidget.h"
#include "ui_qttestpylostestgamedialog.h"
//---------------------------------------------------------------------------
QtTestPylosTestGameDialog::QtTestPylosTestGameDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestPylosTestGameDialog),
  m_widget(new QtPylosGameWidget),
  m_timer(new QTimer(this))
{
  ui->setupUi(this);

  ui->widget_pylos_layout->addWidget(m_widget.get());

  //Connect the timer
  QObject::connect(
    m_timer,SIGNAL(timeout()),
    this,SLOT(OnTimer()));

  //When there's a winner, only the log needs to be informed
  QObject::connect(this->m_widget.get(),SIGNAL(HasWinner()),
    this,SLOT(UpdateLog()));
  //When one of the other selectors changes, only the log needs to be informed
  QObject::connect(this->m_widget.get(),SIGNAL(Toggle()),
    this,SLOT(UpdateLog()));
  //When the selector changes, only the log needs to be informed
  QObject::connect(this->m_widget.get(),SIGNAL(SelectorChanged()),
    this,SLOT(UpdateLog()));
  //When the active player changes, only the log needs to be informed
  QObject::connect(this->m_widget.get(),SIGNAL(DoneMove()),
    this,SLOT(UpdateLog()));

  UpdateLog();
}
//---------------------------------------------------------------------------
QtTestPylosTestGameDialog::~QtTestPylosTestGameDialog()
{
  m_timer->stop();
  delete ui;
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::changeEvent(QEvent *e)
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
void QtTestPylosTestGameDialog::on_button_play_visual_clicked()
{
  if (m_timer->isActive())
  {
    //Disable timer
    m_timer->stop();
  }
  else
  {
    //Start timer
    if (m_widget->GetWinner() != Pylos::Winner::none)
    {
      if ( (std::rand() >> 4) % 2)
      {
        ui->radio_advanced->click();
      }
      else
      {
        ui->radio_basic->click();
      }
    }
    m_timer->setInterval(10);
    m_timer->start();
  }
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::OnTimer()
{
  const QRect r = this->m_widget->geometry();
  const int x = r.left() + (std::rand() % r.width());
  const int y = r.top()  + (std::rand() % r.height());
  QPoint pos(x,y);
  boost::shared_ptr<QMouseEvent> e;
  e.reset(new QMouseEvent(
    QEvent::MouseMove,
    pos,
    Qt::NoButton,
    Qt::NoButton,
    Qt::NoModifier));
  m_widget->mouseMoveEvent(e.get());
  if ((std::rand() >> 4) % 2)
  {
    e.reset(new QMouseEvent(
      QEvent::MouseButtonPress,
      pos,
      Qt::LeftButton,
      Qt::LeftButton,
      Qt::NoModifier));
  }
  else
  {
    e.reset(new QMouseEvent(
      QEvent::MouseButtonPress,
      pos,
      Qt::RightButton,
      Qt::RightButton,
      Qt::NoModifier));
  }
  this->m_widget->mousePressEvent(e.get());

  if (m_widget->GetWinner() != Pylos::Winner::none)
  {
    m_timer->stop();
  }
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::on_radio_advanced_clicked()
{
  m_widget->StartAdvanced();
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::on_radio_basic_clicked()
{
  m_widget->StartBasic();
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::on_radio_bw_clicked()
{
  m_widget->SetColorSchemeBlackWhite();
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::on_radio_rb_clicked()
{
  m_widget->SetColorSchemeRedBlue();
}
//---------------------------------------------------------------------------
void QtTestPylosTestGameDialog::UpdateLog()
{
  ui->text_log->clear();

  ui->text_log->appendPlainText(
    QString("Selector coordinat: ")
    + QString(m_widget->GetSelector().ToStr().c_str()));

  ui->bar1->setValue(m_widget->GetPylos()->GetBoard()->Count(Pylos::PositionState::player1));
  ui->bar2->setValue(m_widget->GetPylos()->GetBoard()->Count(Pylos::PositionState::player2));

  {
    std::string s = "Other selectors' coordinats: ";
    const std::vector<Pylos::Coordinat>& v
      = m_widget->GetOtherSelectors();
    if (v.empty()) { s+="none"; }
    if (v.size() > 0) { s+= v[0].ToStr(); }
    if (v.size() == 2) { s+= std::string(" and ") + v[1].ToStr(); }
    ui->text_log->appendPlainText(s.c_str());
  }
  {
    const std::string s = "Must remove: " + Pylos::ToStr(m_widget->GetMustRemove());
    ui->text_log->appendPlainText(s.c_str());
  }
  {
    const std::string s = "Winner: " + Pylos::ToStr(m_widget->GetWinner());
    ui->text_log->appendPlainText(s.c_str());
  }
  {
    const std::vector<Pylos::Move> v = m_widget->GetPylos()->GetAllPossibleMoves();
    const std::size_t sz = v.size();
    {
      const std::string s = "#moves: " + boost::lexical_cast<std::string>(sz) ;
      ui->text_log->appendPlainText(s.c_str());
    }

    for (std::size_t i=0; i!=sz; ++i)
    {
      const std::string s = boost::lexical_cast<std::string>(i)
        + ": " + v[i].ToStr();
      ui->text_log->appendPlainText(s.c_str());
    }
  }
  {
    ui->text_log->appendPlainText("");
    ui->text_log->appendPlainText("Move history:");
    const std::vector<Pylos::Move> v = m_widget->GetPylos()->GetMoveHistory();
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const std::string s = boost::lexical_cast<std::string>(i)
        + ". " + v[i].ToStr();
      ui->text_log->appendPlainText(s.c_str());
    }
  }

}
//---------------------------------------------------------------------------
