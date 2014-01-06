//---------------------------------------------------------------------------
/*
TestQtRoundedTextRectItem, tool to test QtRoundedTextRectItem
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTROUNDEDTEXTRECTITEMMAINDIALOG_H
#define QTTESTQTROUNDEDTEXTRECTITEMMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestQtRoundedTextRectItemMainDialog;
}

namespace ribi {

class QtTestQtRoundedTextRectItemMainDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
public:

  explicit QtTestQtRoundedTextRectItemMainDialog(QWidget *parent = 0);
  QtTestQtRoundedTextRectItemMainDialog(const QtTestQtRoundedTextRectItemMainDialog&) = delete;
  QtTestQtRoundedTextRectItemMainDialog& operator=(const QtTestQtRoundedTextRectItemMainDialog&) = delete;
  ~QtTestQtRoundedTextRectItemMainDialog() noexcept;
protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtTestQtRoundedTextRectItemMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDTEXTRECTITEMMAINDIALOG_H
