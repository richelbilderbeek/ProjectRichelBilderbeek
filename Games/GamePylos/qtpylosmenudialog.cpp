
/*
Pylos, Pylos/Pyraos game
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

//From http://www.richelbilderbeek.nl/GamePylos.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
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

QtPylosMenuDialog::QtPylosMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtPylosMenuDialog),
  m_selected(-1),
  m_type_basic(true),
  m_theme_bw(false)
{
  ui->setupUi(this);

  //Generate sprites when needed
  {
    Pylos::QtSprites s(256,256);
    /*
    s.Get(Pylos::QtSprites::board_hole).save("sprite_hole.png");
    s.Get(Pylos::QtSprites::player1).save("sprite_player1.png");
    s.Get(Pylos::QtSprites::player2).save("sprite_player2.png");
    s.Get(Pylos::QtSprites::player1_remove).save("sprite_player1_remove.png");
    s.Get(Pylos::QtSprites::player2_remove).save("sprite_player2_remove.png");
    s.Get(Pylos::QtSprites::player1_select).save("sprite_player1_select.png");
    s.Get(Pylos::QtSprites::player2_select).save("sprite_player2_select.png");
    */
  }

}

QtPylosMenuDialog::~QtPylosMenuDialog()
{
  delete ui;
}

void QtPylosMenuDialog::changeEvent(QEvent *e)
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

void QtPylosMenuDialog::mousePressEvent(QMouseEvent *)
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

void QtPylosMenuDialog::mouseMoveEvent(QMouseEvent *)
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

void QtPylosMenuDialog::OnAbout()
{
  About a = PylosMenuDialog::GetAbout();
  a.AddLibrary("QtPylosBoardWidget version: " + QtPylosBoardWidget::GetVersion());
  a.AddLibrary("QtPylosGameWidget version: " + QtPylosGameWidget::GetVersion());
  a.AddLibrary("Pylos::QtSprites version: " + Pylos::QtSprites::GetVersion());
  a.AddLibrary("QtPylosWidget version: " + QtPylosWidget::GetVersion());
  QtAboutDialog d(a);

  d.exec();
}

void QtPylosMenuDialog::OnInstructions()
{
  QtPylosInstructionsDialog d;
  d.exec();
}

void QtPylosMenuDialog::OnStart()
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
  this->hide();
  d.exec();
  this->show();
}



