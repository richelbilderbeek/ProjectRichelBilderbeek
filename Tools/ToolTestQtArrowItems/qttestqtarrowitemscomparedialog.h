// ---------------------------------------------------------------------------
/*
TestQtArrowItems, tool to test Qt arrow QGraphicsItems
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
// ---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQtArrowItems.htm
// ---------------------------------------------------------------------------
#ifndef QTTESTQTARROWITEMSCOMPAREDIALOG_H
#define QTTESTQTARROWITEMSCOMPAREDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "about.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtTestQtArrowItemsCompareDialog;
}

namespace ribi {

class QtTestQtArrowItemsCompareDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQtArrowItemsCompareDialog(QWidget *parent = 0);
  QtTestQtArrowItemsCompareDialog(const QtTestQtArrowItemsCompareDialog&) = delete;
  QtTestQtArrowItemsCompareDialog& operator=(const QtTestQtArrowItemsCompareDialog&) = delete;
  ~QtTestQtArrowItemsCompareDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtTestQtArrowItemsCompareDialog *ui;

  void OnRequestSceneUpdate();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTARROWITEMSCOMPAREDIALOG_H
