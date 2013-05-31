//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012 Richel Bilderbeek

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
#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessmove.h"
#include "chessplayer.h"
#include "qttestchessboarddialog.h"
//#include "testchessmaindialog.h"
#include "ui_qttestchessboarddialog.h"
//---------------------------------------------------------------------------
QtTestChessBoardDialog::QtTestChessBoardDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestChessBoardDialog)
{
  ui->setupUi(this);
  ui->chessboard_widget->m_signal_changed.connect(
    boost::bind(
      &QtTestChessBoardDialog::OnChessboardChanged,
      this));


  OnChessboardChanged();
}
//---------------------------------------------------------------------------
QtTestChessBoardDialog::~QtTestChessBoardDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtTestChessBoardDialog::OnChessboardChanged()
{
  const std::vector<Chess::Move> v = ui->chessboard_widget->GetWidget()->GetBoard()->GetMoves(
    ui->chessboard_widget->GetWidget()->GetActivePlayer());
  ui->list_moves->clear();
  std::for_each(v.begin(),v.end(),
    [&ui](const Chess::Move& m)
    {
      ui->list_moves->addItem(m.GetStr().c_str());
    }
  );
}
//---------------------------------------------------------------------------
void QtTestChessBoardDialog::on_list_moves_doubleClicked(const QModelIndex &index)
{
  const Chess::Player player = ui->chessboard_widget->GetWidget()->GetActivePlayer();
  const std::string move_str = ui->list_moves->item(index.row())->text().toStdString();
  assert(ui->chessboard_widget->GetWidget()->GetBoard()->CanDoMove(move_str,player));
  ui->chessboard_widget->GetWidget()->GetBoard()->DoMove(move_str,player);
  OnChessboardChanged();
}
//---------------------------------------------------------------------------
void QtTestChessBoardDialog::on_radio_black_clicked()
{
  ui->chessboard_widget->GetWidget()->SetActivePlayer(Chess::Player::black);
}
//---------------------------------------------------------------------------
void QtTestChessBoardDialog::on_radio_white_clicked()
{
  ui->chessboard_widget->GetWidget()->SetActivePlayer(Chess::Player::white);
}
//---------------------------------------------------------------------------
