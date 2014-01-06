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
#include "qtpylosmenudialog.h"

#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "pylosmenudialog.h"
#include "qtaboutdialog.h"
#include "qtpylosboardwidget.h"
#include "qtpylosinstructionsdialog.h"
#include "qtpylosmaindialog.h"
#include "qtpylossprites.h"
#include "qtpyloswidget.h"
#include "ui_qtpylosmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtPylosMenuDialog::QtPylosMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPylosMenuDialog),
  m_selected(-1),
  m_type_basic(true),
  m_theme_bw(false)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Generate sprites when needed
  {
    Pylos::QtSprites s(256,256);
  }

}

ribi::QtPylosMenuDialog::~QtPylosMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtPylosMenuDialog::mousePressEvent(QMouseEvent *)
{
  if (ui->label_theme->underMouse())
  {
    m_theme_bw = !m_theme_bw;
    if (m_theme_bw)
      ui->label_theme->setText("Theme: black & white");
    else
      ui->label_theme->setText("Theme: red & blue");
    return;
  }

  if (ui->label_type->underMouse())
  {
    m_type_basic = !m_type_basic;
    if (m_type_basic)
      ui->label_type->setText("Game type: basic");
    else
      ui->label_type->setText("Game type: advanced");
    return;
  }

  switch (m_selected)
  {
    case 0: OnStart(); return;
    case 1: OnInstructions(); return;
    case 2: OnAbout(); return;
    case 3: this->close(); return;
  }
}

void ribi::QtPylosMenuDialog::mouseMoveEvent(QMouseEvent *)
{
  if (
       ui->label_start->underMouse()
    || ui->label_start_left->underMouse()
    || ui->label_start_right->underMouse())
  {
    m_selected = 0;
  }
  else if (ui->label_instructions->underMouse()
    || ui->label_instructions_left->underMouse()
    || ui->label_instructions_right->underMouse())
  {
    m_selected = 1;
  }

  else if (ui->label_about->underMouse()
    || ui->label_about_left->underMouse()
    || ui->label_about_right->underMouse())
  {
    m_selected = 2;
  }
  else if (ui->label_quit->underMouse()
    || ui->label_quit_left->underMouse()
    || ui->label_quit_right->underMouse())
  {
    m_selected = 3;
  }
  else
  {
    m_selected = -1;
  }
  ui->label_start_left->setPixmap(QPixmap( m_selected == 0
    ? ":/images/sprite_player1.png" : ":/images/sprite_hole.png"));
  ui->label_start_right->setPixmap(QPixmap( m_selected == 0
    ? ":/images/sprite_player2.png" : ":/images/sprite_hole.png"));

  ui->label_instructions_left->setPixmap(QPixmap( m_selected == 1
    ? ":/images/sprite_player1.png" : ":/images/sprite_hole.png"));
  ui->label_instructions_right->setPixmap(QPixmap( m_selected == 1
    ? ":/images/sprite_player2.png" : ":/images/sprite_hole.png"));

  ui->label_about_left->setPixmap(QPixmap( m_selected == 2
    ? ":/images/sprite_player1.png" : ":/images/sprite_hole.png"));
  ui->label_about_right->setPixmap(QPixmap( m_selected == 2
    ? ":/images/sprite_player2.png" : ":/images/sprite_hole.png"));

  ui->label_quit_left->setPixmap(QPixmap( m_selected == 3
    ? ":/images/sprite_player1.png" : ":/images/sprite_hole.png"));
  ui->label_quit_right->setPixmap(QPixmap( m_selected == 3
    ? ":/images/sprite_player2.png" : ":/images/sprite_hole.png"));
  repaint();
}

void ribi::QtPylosMenuDialog::OnAbout()
{
  About a = PylosMenuDialog().GetAbout();
  a.AddLibrary("QtPylosBoardWidget version: " + QtPylosBoardWidget::GetVersion());
  a.AddLibrary("QtPylosGameWidget version: " + QtPylosGameWidget::GetVersion());
  a.AddLibrary("Pylos::QtSprites version: " + Pylos::QtSprites::GetVersion());
  a.AddLibrary("QtPylosWidget version: " + QtPylosWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtPylosMenuDialog::OnInstructions()
{
  QtPylosInstructionsDialog d;
  this->ShowChild(&d);
}

void ribi::QtPylosMenuDialog::OnStart()
{
  QtPylosGameWidget * const p = new QtPylosGameWidget();
  assert(p);
  //Set the game type
  if (m_type_basic) p->StartBasic();
  else p->StartAdvanced();
  //Set the color theme
  if (m_theme_bw) p->SetColorSchemeBlackWhite();
  else p->SetColorSchemeRedBlue();
  //Create the game dialog
  //note: p is deleted by DialogMain
  QtPylosMainDialog d(p);
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtPylosMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtPylosMenuDialog::Test");
  TRACE("Finished ribi::QtPylosMenuDialog::Test successfully");
}
#endif
