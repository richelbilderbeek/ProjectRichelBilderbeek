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
#ifndef DIALOGWHATSNEW_H
#define DIALOGWHATSNEW_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class DialogWhatsNew;
}
//---------------------------------------------------------------------------
class DialogWhatsNew : public QDialog
{
  Q_OBJECT

public:
  explicit DialogWhatsNew(QWidget *parent = 0);
  ~DialogWhatsNew();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogWhatsNew *ui;
};
//---------------------------------------------------------------------------
#endif // DIALOGWHATSNEW_H
