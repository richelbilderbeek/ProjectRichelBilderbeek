//---------------------------------------------------------------------------
/*
Encranger, encryption tool
Copyright (C) 2009-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolEncranger.htm
//---------------------------------------------------------------------------
#ifndef QTTOOLENCRANGERDIALOG_H
#define QTTOOLENCRANGERDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolEncrangerMainDialog;
}

namespace ribi {

struct ToolEncrangerMainDialog;

class QtToolEncrangerMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtToolEncrangerMainDialog(QWidget *parent = 0) noexcept;
  QtToolEncrangerMainDialog(const QtToolEncrangerMainDialog&) = delete;
  QtToolEncrangerMainDialog& operator=(const QtToolEncrangerMainDialog&) = delete;
  ~QtToolEncrangerMainDialog() noexcept;

protected:

private:
  Ui::QtToolEncrangerMainDialog *ui;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  ToolEncrangerMainDialog * const m_dialog;

private slots:
  void on_button_deencrypt_clicked() noexcept;
  void on_button_encrypt_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLENCRANGERDIALOG_H
