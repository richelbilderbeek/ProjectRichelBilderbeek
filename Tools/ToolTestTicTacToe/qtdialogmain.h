//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm
//---------------------------------------------------------------------------
#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
struct QTableWidget;
struct QtTicTacToeWidget;
namespace Ui {
  class DialogMain;
}
//---------------------------------------------------------------------------
class DialogMain : public QDialog
{
  Q_OBJECT

public:
  explicit DialogMain(QWidget *parent = 0);
  ~DialogMain();
static const std::string GetVersion();
static const std::vector<std::string> GetVersionHistory();

protected:
  void changeEvent(QEvent *e);
private:
  Ui::DialogMain *ui;
  QtTicTacToeWidget * m_tictactoewidget;
  QTimer * m_timer;

private slots:
  void OnAbout();
  void OnPlay();
  void OnRestart();
  void OnStateChange();
  void OnTick();
};
//---------------------------------------------------------------------------
///SetReadOnlyTableWidget makes the QTableWidget read-only.
///From http://www.richelbilderbeek.nl/CppSetReadOnlyTableWidget.htm
void SetReadOnlyTableWidget(QTableWidget * const t);
//---------------------------------------------------------------------------
#endif // DIALOGMAIN_H
