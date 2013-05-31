//---------------------------------------------------------------------------
/*
TestBinaryNewickVector, GUI tool to test BinaryNewickVector
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestBinaryNewickVector.htm
//---------------------------------------------------------------------------
#ifndef DIALOGTESTBINARYNEWICKVECTOR_H
#define DIALOGTESTBINARYNEWICKVECTOR_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class DialogTestBinaryNewickVector;
}
//---------------------------------------------------------------------------
class DialogTestBinaryNewickVector : public QDialog
{
  Q_OBJECT

public:
  explicit DialogTestBinaryNewickVector(QWidget *parent = 0);
  ~DialogTestBinaryNewickVector();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogTestBinaryNewickVector *ui;
  QTimer * m_timer;
private slots:
  void on_button_calculate_clicked();
  void on_button_about_clicked();
  void on_button_demo_clicked();
  void OnAnyChange();
  void OnDemoTick();
};
//---------------------------------------------------------------------------
#endif // DIALOGTESTBINARYNEWICKVECTOR_H
