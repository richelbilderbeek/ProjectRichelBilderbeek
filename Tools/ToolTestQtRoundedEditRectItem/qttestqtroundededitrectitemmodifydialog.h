//---------------------------------------------------------------------------
/*
TestQtRoundedEditRectItem, tool to test QtRoundedRectItem
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
#ifndef QTTESTQTROUNDEDEDITRECTITEMMODIFYDIALOG_H
#define QTTESTQTROUNDEDEDITRECTITEMMODIFYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QGraphicsView;

namespace Ui {
class QtTestQtRoundedEditRectItemModifyDialog;
}


namespace ribi {

//struct QtRoundedRectItem;
struct QtRoundedEditRectItem;
struct QtRoundedEditRectItemDialog;

class QtTestQtRoundedEditRectItemModifyDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:

  explicit QtTestQtRoundedEditRectItemModifyDialog(QWidget *parent = 0);
  QtTestQtRoundedEditRectItemModifyDialog(const QtTestQtRoundedEditRectItemModifyDialog&) = delete;
  QtTestQtRoundedEditRectItemModifyDialog& operator=(const QtTestQtRoundedEditRectItemModifyDialog&) = delete;
  ~QtTestQtRoundedEditRectItemModifyDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private slots:

private:
  Ui::QtTestQtRoundedEditRectItemModifyDialog *ui;

  boost::shared_ptr<QtRoundedEditRectItemDialog> m_dialog_left;
  boost::shared_ptr<QtRoundedEditRectItemDialog> m_dialog_right;
  boost::shared_ptr<QGraphicsView> m_view_left;
  boost::shared_ptr<QGraphicsView> m_view_right;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDEDITRECTITEMMODIFYDIALOG_H
