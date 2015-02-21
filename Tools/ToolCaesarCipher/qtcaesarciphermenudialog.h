//---------------------------------------------------------------------------
/*
CaesarCipher, Caesar cipher tool
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCaesarCipher.htm
//---------------------------------------------------------------------------
#ifndef QTCAESARCIPHERMENUDIALOG_H
#define QTCAESARCIPHERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtCaesarCipherMenuDialog;
}

namespace ribi {

class QtCaesarCipherMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCaesarCipherMenuDialog(QWidget *parent = 0) noexcept;
  QtCaesarCipherMenuDialog(const QtCaesarCipherMenuDialog&) = delete;
  QtCaesarCipherMenuDialog& operator=(const QtCaesarCipherMenuDialog&) = delete;
  ~QtCaesarCipherMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtCaesarCipherMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTCAESARCIPHERMENUDIALOG_H
