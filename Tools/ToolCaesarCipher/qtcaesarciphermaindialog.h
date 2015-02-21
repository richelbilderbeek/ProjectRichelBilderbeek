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
#ifndef QTCAESARCIPHERMAINDIALOG_H
#define QTCAESARCIPHERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtCaesarCipherMainDialog;
}

namespace ribi {

struct CaesarCipherMainDialog;

class QtCaesarCipherMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtCaesarCipherMainDialog(QWidget *parent = 0) noexcept;
  QtCaesarCipherMainDialog(const QtCaesarCipherMainDialog&) = delete;
  QtCaesarCipherMainDialog& operator=(const QtCaesarCipherMainDialog&) = delete;
  ~QtCaesarCipherMainDialog() noexcept;

protected:

private:
  Ui::QtCaesarCipherMainDialog *ui;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  CaesarCipherMainDialog * const m_dialog;

private slots:
  void on_button_deencrypt_clicked() noexcept;
  void on_button_encrypt_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  void on_edit_plaintext_textChanged(const QString &arg1);
  void on_edit_encrypted_text_textChanged(const QString &arg1);
};

} //~namespace ribi

#endif // QTCAESARCIPHERMAINDIALOG_H
