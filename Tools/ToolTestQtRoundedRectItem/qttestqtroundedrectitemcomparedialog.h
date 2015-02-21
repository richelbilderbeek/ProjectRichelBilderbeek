//---------------------------------------------------------------------------
/*
TestQtRoundedRectItem, tool to test QtRoundedRectItem
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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTROUNDEDRECTITEMCOMPAREDIALOG_H
#define QTTESTQTROUNDEDRECTITEMCOMPAREDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtTestQtRoundedRectItemCompareDialog;
}

namespace ribi {

class QtTestQtRoundedRectItemCompareDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:

  explicit QtTestQtRoundedRectItemCompareDialog(QWidget *parent = 0);
  QtTestQtRoundedRectItemCompareDialog(const QtTestQtRoundedRectItemCompareDialog&) = delete;
  QtTestQtRoundedRectItemCompareDialog& operator=(const QtTestQtRoundedRectItemCompareDialog&) = delete;
  ~QtTestQtRoundedRectItemCompareDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestQtRoundedRectItemCompareDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDRECTITEMCOMPAREDIALOG_H
