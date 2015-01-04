//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtboenkencontrolsdialog.h"

#include <boost/lexical_cast.hpp>

#include "qtboenkenpresskeydialog.h"
#include "ui_qtboenkencontrolsdialog.h"
#pragma GCC diagnostic pop

ribi::QtBoenkenControlsDialog::QtBoenkenControlsDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenControlsDialog),
    m_keys_accel{},
    m_keys_turn{}
{
  ui->setupUi(this);

  QObject::connect(
    ui->button_done,
    &QPushButton::clicked,
    this,
    &ribi::QtBoenkenControlsDialog::close
  );
  m_keys_accel.push_back(Qt::Key_W);
  m_keys_accel.push_back(Qt::Key_Up);
  m_keys_turn.push_back(Qt::Key_D);
  m_keys_turn.push_back(Qt::Key_Right);

  QObject::connect(
    ui->button_accelerate_1,
    &QPushButton::clicked,
    this,
    &ribi::QtBoenkenControlsDialog::onAccelerate1
  );
  QObject::connect(
    ui->button_accelerate_2,
    &QPushButton::clicked,
    this,
    &ribi::QtBoenkenControlsDialog::onAccelerate2
  );
  QObject::connect(
    ui->button_turn_1,
    &QPushButton::clicked,
    this,
    &ribi::QtBoenkenControlsDialog::onTurn1
  );
  QObject::connect(ui->button_turn_2,
    &QPushButton::clicked,
    this,
    &ribi::QtBoenkenControlsDialog::onTurn2
  );

  showKeys();
}

ribi::QtBoenkenControlsDialog::~QtBoenkenControlsDialog() noexcept
{
  delete ui;
}

void ribi::QtBoenkenControlsDialog::showKeys() noexcept
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

void ribi::QtBoenkenControlsDialog::onAccelerate1() noexcept
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_accel[0] = key;
  showKeys();
}

void ribi::QtBoenkenControlsDialog::onAccelerate2() noexcept
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_accel[1] = key;
  showKeys();
}

void ribi::QtBoenkenControlsDialog::onTurn1() noexcept
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_turn[0] = key;
  showKeys();
}

void ribi::QtBoenkenControlsDialog::onTurn2() noexcept
{
  QtBoenkenPressKeyDialog d;
  d.exec();
  const int key = d.GetKey();
  m_keys_turn[1] = key;
  showKeys();
}

std::vector<int> ribi::QtBoenkenControlsDialog::getKeysAccel() const noexcept
{
  return m_keys_accel;
}

std::vector<int> ribi::QtBoenkenControlsDialog::getKeysTurn() const noexcept
{
  return m_keys_turn;
}

std::vector<std::string> ribi::QtBoenkenControlsDialog::getNames() const noexcept
{
  std::vector<std::string> v;
  v.push_back(ui->edit_name1->text().toStdString());
  v.push_back(ui->edit_name2->text().toStdString());
  return v;
}

ribi::Boenken::Controls ribi::QtBoenkenControlsDialog::GetControls() const noexcept
{
  Boenken::Controls c;
  c.m_keys_accel = this->getKeysAccel();
  c.m_keys_turn = this->getKeysTurn();
  c.m_names = this->getNames();
  return c;
}
