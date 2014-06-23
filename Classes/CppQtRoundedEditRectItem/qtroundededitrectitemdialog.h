//---------------------------------------------------------------------------
/*
QtRoundedEditRectItem, editable rectangular-shaped QGraphicsItem
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
//From http://www.richelbilderbeek.nl/QtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTROUNDEDEDITRECTITEMDIALOG_H
#define QTROUNDEDEDITRECTITEMDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtRoundedEditRectItemDialog;
}

namespace ribi {

//struct QtRoundedRectItem; //QtRoundedEditRectItem its base class
struct QtRoundedEditRectItem; //The item
struct QtRoundedRectItemDialog; //its base class display

class QtRoundedEditRectItemDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:

  explicit QtRoundedEditRectItemDialog(QWidget *parent = 0);
  QtRoundedEditRectItemDialog(const QtRoundedEditRectItemDialog&) = delete;
  QtRoundedEditRectItemDialog& operator=(const QtRoundedEditRectItemDialog&) = delete;
  ~QtRoundedEditRectItemDialog() noexcept;

  boost::shared_ptr<QtRoundedEditRectItem> GetItem() const noexcept { return m_item; }

  static int GetMinimumHeight(const QtRoundedEditRectItem& /* item */) noexcept { return 276; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  void SetItem(const boost::shared_ptr<QtRoundedEditRectItem>& item) noexcept;


protected:
  void keyPressEvent(QKeyEvent * event);

private slots:
  void on_button_font_clicked();
  void on_text_textChanged();
  void on_button_text_pen_clicked();

  void on_box_padding_left_valueChanged(double arg1);

  void on_box_padding_top_valueChanged(double arg1);

  void on_box_padding_right_valueChanged(double arg1);

  void on_box_padding_bottom_valueChanged(double arg1);

private:
  Ui::QtRoundedEditRectItemDialog *ui;

  ///Dialog for its base class
  const boost::shared_ptr<QtRoundedRectItemDialog> m_dialog;

  ///The QtRoundedRectItem to work on
  boost::shared_ptr<QtRoundedEditRectItem> m_item;


  void OnBaseChanged(QtRoundedEditRectItem * const qtitem) noexcept;
  void OnFontChanged(QtRoundedEditRectItem * const qtitem) noexcept;
  void OnPaddingChanged(QtRoundedEditRectItem * const qtitem) noexcept;
  void OnTextChanged(QtRoundedEditRectItem * const qtitem) noexcept;
  void OnTextPenChanged(QtRoundedEditRectItem * const qtitem) noexcept;



  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTROUNDEDEDITRECTITEMDIALOG_H
