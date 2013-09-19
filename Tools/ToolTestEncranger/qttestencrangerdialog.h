//---------------------------------------------------------------------------
/*
TestEncranger, tool to test the Encranger class
Copyright (C) 2009-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestEncranger.htm
//---------------------------------------------------------------------------
#ifndef QTTESTENCRANGERDIALOG_H
#define QTTESTENCRANGERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestEncrangerDialog;
}

namespace ribi {

struct TestEncrangerDialog;

class QtTestEncrangerDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestEncrangerDialog(QWidget *parent = 0) noexcept;
  QtTestEncrangerDialog(const QtTestEncrangerDialog&) = delete;
  QtTestEncrangerDialog& operator=(const QtTestEncrangerDialog&) = delete;
  ~QtTestEncrangerDialog() noexcept;

protected:

private:
  Ui::QtTestEncrangerDialog *ui;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
  TestEncrangerDialog * const m_dialog;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_deencrypt_clicked() noexcept;
  void on_button_encrypt_clicked() noexcept;
};

} //~namespace ribi

#endif // QTTESTENCRANGERDIALOG_H
