//---------------------------------------------------------------------------
/*
TestQtModels, tool to test the QtModel classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtModels.htm
//---------------------------------------------------------------------------
#ifndef QTTOOLTESTQTMODELSMENUDIALOG
#define QTTOOLTESTQTMODELSMENUDIALOG

#include "qthideandshowdialog.h"

namespace Ui {
  class QtToolTestQtModelsMenuDialog;
}

namespace ribi {

class QtToolTestQtModelsMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolTestQtModelsMenuDialog(QWidget *parent = 0);
  QtToolTestQtModelsMenuDialog(const QtToolTestQtModelsMenuDialog&) = delete;
  QtToolTestQtModelsMenuDialog& operator=(const QtToolTestQtModelsMenuDialog&) = delete;
  ~QtToolTestQtModelsMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtToolTestQtModelsMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTQTMODELSMENUDIALOG
