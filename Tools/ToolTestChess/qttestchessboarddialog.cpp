//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestChess.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestchessboarddialog.h"

#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessmove.h"
#include "chessplayer.h"
//#include "testchessmaindialog.h"
#include "chessmovefactory.h"
#include "ui_qttestchessboarddialog.h"
#pragma GCC diagnostic pop

ribi::QtTestChessBoardDialog::QtTestChessBoardDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestChessBoardDialog)
{
  ui->setupUi(this);
  ui->chessboard_widget->m_signal_changed.connect(
    boost::bind(
      &QtTestChessBoardDialog::OnChessboardChanged,
      this));


  OnChessboardChanged();
}

ribi::QtTestChessBoardDialog::~QtTestChessBoardDialog() noexcept
{
  delete ui;
}

void ribi::QtTestChessBoardDialog::OnChessboardChanged()
{
  const std::vector<boost::shared_ptr<ribi::Chess::Move>> v = ui->chessboard_widget->GetWidget()->GetBoard()->GetMoves(
    ui->chessboard_widget->GetWidget()->GetActivePlayer());
  ui->list_moves->clear();
  for(const boost::shared_ptr<ribi::Chess::Move> m: v)
  {
    ui->list_moves->addItem(m->GetStr().c_str());
  }
}

void ribi::QtTestChessBoardDialog::on_list_moves_doubleClicked(const QModelIndex &index)
{
  const Chess::Player player = ui->chessboard_widget->GetWidget()->GetActivePlayer();
  const std::string move_str = ui->list_moves->item(index.row())->text().toStdString();
  const boost::shared_ptr<ribi::Chess::Move> move {
    Chess::MoveFactory().Create(move_str)
  };
  assert(ui->chessboard_widget->GetWidget()->GetBoard()->CanDoMove(move,player));
  ui->chessboard_widget->GetWidget()->GetBoard()->DoMove(move,player);
  OnChessboardChanged();
}

void ribi::QtTestChessBoardDialog::on_radio_black_clicked()
{
  ui->chessboard_widget->GetWidget()->SetActivePlayer(Chess::Player::black);
}

void ribi::QtTestChessBoardDialog::on_radio_white_clicked()
{
  ui->chessboard_widget->GetWidget()->SetActivePlayer(Chess::Player::white);
}
