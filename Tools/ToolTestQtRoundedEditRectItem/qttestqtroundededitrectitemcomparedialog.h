//---------------------------------------------------------------------------
/*
TestQtRoundedEditRectItem, tool to test QtRoundedEditRectItem
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTROUNDEDEDITRECTITEMCOMPAREDIALOG_H
#define QTTESTQTROUNDEDEDITRECTITEMCOMPAREDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtTestQtRoundedEditRectItemCompareDialog;
}

namespace ribi {

class QtTestQtRoundedEditRectItemCompareDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
public:

  explicit QtTestQtRoundedEditRectItemCompareDialog(QWidget *parent = 0);
  QtTestQtRoundedEditRectItemCompareDialog(const QtTestQtRoundedEditRectItemCompareDialog&) = delete;
  QtTestQtRoundedEditRectItemCompareDialog& operator=(const QtTestQtRoundedEditRectItemCompareDialog&) = delete;
  ~QtTestQtRoundedEditRectItemCompareDialog() noexcept;
protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestQtRoundedEditRectItemCompareDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDEDITRECTITEMCOMPAREDIALOG_H
