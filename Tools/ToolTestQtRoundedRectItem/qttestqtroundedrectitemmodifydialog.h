//---------------------------------------------------------------------------
/*
TestQtRoundedRectItem, tool to test QtRoundedRectItem
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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTROUNDEDRECTITEMMODIFYDIALOG_H
#define QTTESTQTROUNDEDRECTITEMMODIFYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtTestQtRoundedRectItemModifyDialog;
}

namespace ribi {

struct QtRoundedRectItem;

class QtTestQtRoundedRectItemModifyDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:

  explicit QtTestQtRoundedRectItemModifyDialog(QWidget *parent = 0);
  QtTestQtRoundedRectItemModifyDialog(const QtTestQtRoundedRectItemModifyDialog&) = delete;
  QtTestQtRoundedRectItemModifyDialog& operator=(const QtTestQtRoundedRectItemModifyDialog&) = delete;
  ~QtTestQtRoundedRectItemModifyDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event);

private slots:
  void on_button_contour_pen_clicked();

  void on_button_focus_pen_clicked();

  void on_box_radius_x_valueChanged(double arg1);
  void on_box_radius_y_valueChanged(double arg1);

  void on_box_x_valueChanged(double arg1);
  void on_box_y_valueChanged(double arg1);

  void on_box_width_valueChanged(double arg1);
  void on_box_height_valueChanged(double arg1);

private:
  Ui::QtTestQtRoundedRectItemModifyDialog *ui;

  ///The QtRoundedRectItem to work on
  boost::shared_ptr<QtRoundedRectItem> m_item;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDRECTITEMMODIFYDIALOG_H
