
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2012 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/GameBoenken.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtboenkencontrolsdialog.h"

#include <boost/lexical_cast.hpp>

#include "qtboenkenpresskeydialog.h"
#include "ui_qtboenkencontrolsdialog.h"

QtBoenkenControlsDialog::QtBoenkenControlsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtBoenkenControlsDialog)
{
  ui->setupUi(this);
  QObject::connect(ui->button_done,SIGNAL(clicked()),this,SLOT(close()));
  m_keys_accel.push_back(Qt::Key_W);
  m_keys_accel.push_back(Qt::Key_Up);
  m_keys_turn.push_back(Qt::Key_D);
  m_keys_turn.push_back(Qt::Key_Right);

  QObject::connect(ui->button_accelerate_1,SIGNAL(clicked()),this,SLOT(onAccelerate1()));
  QObject::connect(ui->button_accelerate_2,SIGNAL(clicked()),this,SLOT(onAccelerate2()));
  QObject::connect(ui->button_turn_1,SIGNAL(clicked()),this,SLOT(onTurn1()));
  QObject::connect(ui->button_turn_2,SIGNAL(clicked()),this,SLOT(onTurn2()));

  showKeys();
}

QtBoenkenControlsDialog::~QtBoenkenControlsDialog()
{
  delete ui;
}

void QtBoenkenControlsDialog::changeEvent(QEvent *e)
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

void QtBoenkenControlsDialog::showKeys()
{
  ui->button_accelerate_1->setText(
    boost::lexical_cast<std::string>(m_keys_accel[0]).c_str() );
  ui->button_accelerate_2->setText(
    boost::lexical_cast<std::string>(m_keys_accel[1]).c_str() );
  ui->button_turn_1->setText(
    boost::lexical_cast<std::string>(m_keys_turn[0]).c_str() );
  ui->button_turn_2->setText(
    boost::lexical_cast<std::string>(m_keys_turn[1]).c_str() );

}

void QtBoenkenControlsDialog::onAccelerate1()
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_accel[0] = key;
  showKeys();
}

void QtBoenkenControlsDialog::onAccelerate2()
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_accel[1] = key;
  showKeys();
}

void QtBoenkenControlsDialog::onTurn1()
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_turn[0] = key;
  showKeys();
}

void QtBoenkenControlsDialog::onTurn2()
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_turn[1] = key;
  showKeys();
}

std::vector<int> QtBoenkenControlsDialog::getKeysAccel() const
{
  return m_keys_accel;
}

std::vector<int> QtBoenkenControlsDialog::getKeysTurn() const
{
  return m_keys_turn;
}

std::vector<std::string> QtBoenkenControlsDialog::getNames() const
{
  std::vector<std::string> v;
  v.push_back(ui->edit_name1->text().toStdString());
  v.push_back(ui->edit_name2->text().toStdString());
  return v;
}

Boenken::Controls QtBoenkenControlsDialog::GetControls() const
{
  Boenken::Controls c;
  c.m_keys_accel = this->getKeysAccel();
  c.m_keys_turn = this->getKeysTurn();
  c.m_names = this->getNames();
  return c;
}
