//---------------------------------------------------------------------------
/*
TestNewickVector, GUI tool to test NewickVector
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestNewickVector.htm
//---------------------------------------------------------------------------
#ifndef QTTESTNEWICKVECTORDIALOG_H
#define QTTESTNEWICKVECTORDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtTestNewickVectorDialog;
}
//---------------------------------------------------------------------------

namespace ribi {

struct TestNewickVectorDialog;
//---------------------------------------------------------------------------
class QtTestNewickVectorDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestNewickVectorDialog(QWidget *parent = 0);
  ~QtTestNewickVectorDialog();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
protected:
  

private:
  Ui::QtTestNewickVectorDialog *ui;
  QTimer * m_timer;
  boost::scoped_ptr<TestNewickVectorDialog> m_dialog;
  void Display();


private slots:
  void on_box_compare_clicked();
  void on_box_show_calculation_clicked();
  void on_button_calculate_clicked();
  void on_button_about_clicked();
  void on_button_demo_clicked();
  void OnAnyChange();
  void OnDemoTick();

  //static bool Match(const std::vector<int>& lhs, const std::vector<int>& rhs);
};

} //~namespace ribi

#endif // QTTESTNEWICKVECTORDIALOG_H
