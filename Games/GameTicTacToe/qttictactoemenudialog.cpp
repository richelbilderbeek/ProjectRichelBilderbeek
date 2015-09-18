//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
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
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttictactoemenudialog.h"

#include <cassert>
#include <boost/make_shared.hpp>

#include <QApplication>
#include <QDesktopWidget>

#include "qtaboutdialog.h"
//#include "qtcanvas.h"
//#include "qtcanvasdialog.h"
#include "testtimer.h"
#include "qttictactoecanvas.h"
#include "qttictactoegamedialog.h"
#include "qttictactoewidget.h"
#include "tictactoemenudialog.h"
#include "tictactoeai.h"
#include "trace.h"
#include "ui_qttictactoemenudialog.h"
#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeMenuDialog::QtTicTacToeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::tictactoe::QtTicTacToeMenuDialog::~QtTicTacToeMenuDialog() noexcept
{
  delete ui;
}

void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_start_clicked()
{
  const boost::shared_ptr<Ai> player1;
  const boost::shared_ptr<Ai> player2;
  QtTicTacToeGameDialog d(player1,player2);
  this->ShowChild(&d);
}

void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_about_clicked()
{
  About a = TicTacToeMenuDialog().GetAbout();
  a.AddLibrary("QtTicTacToeWidget version: " + tictactoe::QtTicTacToeWidget::GetVersion());
  QtAboutDialog d(a);
  //d.setStyleSheet(styleSheet());
  this->ShowChild(&d);
}

void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::tictactoe::QtTicTacToeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TicTacToeMenuDialog();
  {
    const boost::shared_ptr<Ai> player1;
    const boost::shared_ptr<Ai> player2;
    QtTicTacToeGameDialog d(player1,player2);
    assert(!d.GetVersion().empty());
  }
  #ifdef SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
  {
    QtCanvas * const qtcanvas {
      new QtTicTacToeCanvas
    };
    boost::scoped_ptr<QtCanvasDialog> d {
      new QtCanvasDialog(qtcanvas)
    };
    assert(d);
  }
  const auto player1 = boost::make_shared<AiEnforceDraw>();
  const auto player2 = boost::make_shared<AiPlayRandom>();
  QtTicTacToeWidget(player1,player2);
  const TestTimer test_timer(__func__,__FILE__,1.0);
  #endif // SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
}
#endif

#ifdef SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
void ribi::tictactoe::QtTicTacToeMenuDialog::on_button_start_old_school_clicked()
{
  QtCanvas * const qtcanvas {
    new QtTicTacToeCanvas
  };
  boost::scoped_ptr<QtCanvasDialog> d {
    new QtCanvasDialog(qtcanvas)
  };
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    d->setGeometry(
      0,0,102,102);
    d->move( screen.center() - this->rect().center() );
  }
  d->setWindowTitle("TicTacToe");
  ShowChild(d.get());
  //canvas will be deleted by QtCanvasDialog
}
#endif // SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918
