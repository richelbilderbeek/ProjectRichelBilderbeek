//---------------------------------------------------------------------------
/*
TestNeuralNet, tool to test the NeuralNet class
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
//From http://www.richelbilderbeek.nl/ToolTestNeuralNet.htm
//---------------------------------------------------------------------------
#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class DialogAbout;
}
//---------------------------------------------------------------------------
class DialogAbout : public QDialog
{
  Q_OBJECT

public:
  explicit DialogAbout(QWidget *parent = 0);
  ~DialogAbout();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogAbout *ui;
};
//---------------------------------------------------------------------------
///GetBoostVersion returns the version of the current Boost library.
///From http://www.richelbilderbeek.nl/CppGetBoostVersion.htm
const std::string GetBoostVersion();
//---------------------------------------------------------------------------
#endif // DIALOGABOUT_H
