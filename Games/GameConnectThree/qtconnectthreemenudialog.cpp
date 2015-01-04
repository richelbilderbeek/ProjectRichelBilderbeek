//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconnectthreemenudialog.h"

#include <cassert>

#include <QApplication>
#include <QDesktopWidget>

#include "connectthreemenudialog.h"
#include "qtaboutdialog.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreeresources.h"
#include "qtconnectthreewidget.h"
#include "qtselectplayerwidget.h"
#include "qtconnectthreecanvas.h"
#include "qtcanvasdialog.h"
#include "qtcanvas.h"
#include "testtimer.h"
#include "ui_qtconnectthreemenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::con3::QtConnectThreeMenuDialog::QtConnectThreeMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtConnectThreeMenuDialog),
    m_resources(new QtConnectThreeResources),
    m_select(new QtSelectPlayerWidget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  assert(layout());

  layout()->addWidget(m_select.get());
}

ribi::con3::QtConnectThreeMenuDialog::~QtConnectThreeMenuDialog() noexcept
{
  delete ui;
}


void ribi::con3::QtConnectThreeMenuDialog::on_button_start_clicked() noexcept
{
  QtConnectThreeGameDialog d(m_resources, nullptr,this->m_select->GetIsPlayerHuman());
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::con3::QtConnectThreeMenuDialog::on_button_about_clicked() noexcept
{
  About about = ConnectThreeMenuDialog().GetAbout();
  about.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::con3::QtConnectThreeMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::con3::QtConnectThreeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ConnectThreeMenuDialog();
  }
  const boost::shared_ptr<const ConnectThreeResources> resources(new QtConnectThreeResources);
  QtConnectThreeGameDialog d(resources,nullptr,std::bitset<3>(false));
  {
    const std::bitset<3> is_player_human(false);

    QtCanvas * const qtcanvas {
      new QtConnectThreeCanvas(is_player_human,16,8)
    };
    boost::scoped_ptr<QtCanvasDialog> d {
      new QtCanvasDialog(qtcanvas)
    };
    assert(d);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::con3::QtConnectThreeMenuDialog::on_button_start_retro_clicked() noexcept
{
  const std::bitset<3>& is_player_human = std::bitset<3>(true);

  QtCanvas * const qtcanvas {
    new QtConnectThreeCanvas(is_player_human,16,8)
  };
  boost::scoped_ptr<QtCanvasDialog> d {
    new QtCanvasDialog(qtcanvas)
  };
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    d->setGeometry(
      0,0,256,256);
    d->move( screen.center() - this->rect().center() );
  }
  d->setWindowTitle("ConnectThree");
  ShowChild(d.get());
}
