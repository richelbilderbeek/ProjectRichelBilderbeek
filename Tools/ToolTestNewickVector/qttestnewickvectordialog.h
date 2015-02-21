//---------------------------------------------------------------------------
/*
TestNewickVector, GUI tool to test NewickVector
Copyright (C) 2011-2015 Richel Bilderbeek

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestNewickVectorDialog;
}


namespace ribi {

struct TestNewickVectorDialog;

class QtTestNewickVectorDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  ///QtTestNewickVectorDialog constructor performs most Newick tests
  explicit QtTestNewickVectorDialog(QWidget *parent = 0) noexcept;
  QtTestNewickVectorDialog(const QtTestNewickVectorDialog&) = delete;
  QtTestNewickVectorDialog& operator=(const QtTestNewickVectorDialog&) = delete;
  ~QtTestNewickVectorDialog() noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

private:
  Ui::QtTestNewickVectorDialog *ui;
  QTimer * m_timer;
  boost::scoped_ptr<TestNewickVectorDialog> m_dialog;
  void Display() noexcept;


private slots:
  void on_box_compare_clicked() noexcept;
  void on_box_show_calculation_clicked() noexcept;
  void on_button_calculate_clicked() noexcept;
  void on_button_about_clicked() noexcept;
  void on_button_demo_clicked() noexcept;
  void OnAnyChange() noexcept;
  void OnDemoTick() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTNEWICKVECTORDIALOG_H
