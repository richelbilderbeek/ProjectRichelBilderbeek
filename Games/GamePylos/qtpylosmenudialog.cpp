//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtpylosmenudialog.h"

#include <iostream>
#include <memory>

#include <boost/make_shared.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "pylosmenudialog.h"
#include "qtaboutdialog.h"
#include "qtpylosboardwidget.h"
#include "qtpylosgamewidget.h"
#include "qtpylosinstructionsdialog.h"
#include "testtimer.h"
#include "qtpylosmaindialog.h"
#include "qtpylossprites.h"
#include "qtpyloswidget.h"
#include "ui_qtpylosmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::pylos::QtPylosMenuDialog::QtPylosMenuDialog(QWidget *parent) :
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
    pylos::QtSprites s(256,256);
  }

}

ribi::pylos::QtPylosMenuDialog::~QtPylosMenuDialog() noexcept
{
  delete ui;
}

void ribi::pylos::QtPylosMenuDialog::mousePressEvent(QMouseEvent *)
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

void ribi::pylos::QtPylosMenuDialog::mouseMoveEvent(QMouseEvent *)
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

void ribi::pylos::QtPylosMenuDialog::OnAbout()
{
  About a = MenuDialog().GetAbout();
  a.AddLibrary("QtPylosBoardWidget version: " + QtPylosBoardWidget::GetVersion());
  a.AddLibrary("QtPylosGameWidget version: " + QtPylosGameWidget::GetVersion());
  a.AddLibrary("pylos::QtSprites version: " + QtSprites::GetVersion());
  a.AddLibrary("QtPylosWidget version: " + QtPylosWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::pylos::QtPylosMenuDialog::OnInstructions()
{
  QtPylosInstructionsDialog d;
  this->ShowChild(&d);
}

void ribi::pylos::QtPylosMenuDialog::OnStart()
{
  const auto p = std::make_shared<QtPylosGameWidget>();
  assert(p);
  //Set the game type
  if (m_type_basic) p->StartBasic();
  else p->StartAdvanced();
  //Set the color theme
  if (m_theme_bw) p->SetColorSchemeBlackWhite();
  else p->SetColorSchemeRedBlue();
  //Create the game dialog
  //note: p is deleted by DialogMain
  ribi::pylos::QtPylosMainDialog d(p);
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::pylos::QtPylosMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    pylos::MenuDialog();
    QtPylosMainDialog::Test();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  #ifdef FIX_ISSUE_234
  const boost::shared_ptr<QtPylosGameWidget> p(new QtPylosGameWidget);
  assert(p);
  //Set the game type
  p->StartBasic();
  p->SetColorSchemeBlackWhite();
  const boost::shared_ptr<QtPylosMainDialog> d{new QtPylosMainDialog(p)};
  //const QtPylosMainDialog d(p);
  assert(!d->GetVersion().empty());
  #endif // FIX_ISSUE_234
}
#endif
