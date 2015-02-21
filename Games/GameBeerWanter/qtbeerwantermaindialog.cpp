//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtbeerwantermaindialog.h"

#include <iostream>

#include "beerwantermaindialog.h"
#include "qtbeerwanterwidget.h"
#include "testtimer.h"
#include "ui_qtbeerwantermaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtBeerWanterMainDialog::QtBeerWanterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtBeerWanterMainDialog),
    m_widget(new QtBeerWanterWidget)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->beerwanter_layout->addWidget(m_widget.get());
  this->setGeometry(
    m_widget->GetBeerWanter()->GetWindowX(),
    m_widget->GetBeerWanter()->GetWindowY(),
    m_widget->GetBeerWanter()->GetWindowWidth(),
    m_widget->GetBeerWanter()->GetWindowHeight()
  );

  QObject::connect(
    m_widget.get(),
    &QtBeerWanterWidget::LevelUp,
    this,
    &ribi::QtBeerWanterMainDialog::ChangeTitle
  );
  QObject::connect(
    m_widget.get(),
    &QtBeerWanterWidget::DoShake,
    this,
    &ribi::QtBeerWanterMainDialog::OnShake
  );
}

ribi::QtBeerWanterMainDialog::~QtBeerWanterMainDialog() noexcept
{
  delete ui;
}

void ribi::QtBeerWanterMainDialog::ChangeTitle(const std::string& title) noexcept
{
  this->setWindowTitle(title.c_str());
}

void ribi::QtBeerWanterMainDialog::OnShake(const int x, const int y) noexcept
{
  this->setGeometry(x,y,this->width(),this->height());
  this->repaint();
}

#ifndef NDEBUG
void ribi::QtBeerWanterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const int screen_width = 640;
  const int screen_height = 400;
  const int sprite_width = 32;
  const int sprite_height = 48;
  const int window_width = 320;
  const int window_height = 200;

  BeerWanterMainDialog(
    screen_width,
    screen_height,
    sprite_width,
    sprite_height,
    window_width,
    window_height
  );
}
#endif
