//---------------------------------------------------------------------------
/*
VigenereCipher, Vigenere cipher tool
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
//From http://www.richelbilderbeek.nl/ToolVigenereCipher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtvigenereciphermaindialog.h"

#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "vigenerecipher.h"
#include "loopreader.h"
#include "testtimer.h"
#include "qtaboutdialog.h"
#include "trace.h"
#include "ui_qtvigenereciphermaindialog.h"
#include "vigenereciphermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtVigenereCipherMainDialog::QtVigenereCipherMainDialog(QWidget *parent) noexcept
 :  QtHideAndShowDialog(parent),
    ui(new Ui::QtVigenereCipherMainDialog),
    m_dialog(new VigenereCipherMainDialog("a"))
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  {
    const QRegExp regex("[a-z]*");
    QValidator * const validator = new QRegExpValidator(regex, this);
    ui->edit_encrypted_text->setValidator(validator);
    ui->edit_key->setValidator(validator);
    ui->edit_plaintext->setValidator(validator);
  }
}

ribi::QtVigenereCipherMainDialog::~QtVigenereCipherMainDialog() noexcept
{
  delete ui;
  delete m_dialog;
}

void ribi::QtVigenereCipherMainDialog::on_button_encrypt_clicked() noexcept
{
  const std::string key = ui->edit_key->text().toStdString();
  //for (auto c:key) { if (c < 'A' || c > 'Z') return; }
  const std::string text = ui->edit_plaintext->text().toStdString();
  //for (auto c:text) { if (c < 'A' || c > 'Z') return; }
  m_dialog->SetPlainText(text);
  m_dialog->SetKey(key);
  m_dialog->Encrypt();

  const std::string result = m_dialog->GetEncryptedText();
  if (ui->edit_encrypted_text->text().toStdString() != result)
  {
    ui->edit_encrypted_text->setText(result.c_str());
  }
}

void ribi::QtVigenereCipherMainDialog::on_button_deencrypt_clicked() noexcept
{
  const std::string key = ui->edit_key->text().toStdString();
  //for (auto c:key) { if (c < 'A' || c > 'Z') return; }
  const std::string text = ui->edit_encrypted_text->text().toStdString();
  //for (auto c:text) { if (c < 'A' || c > 'Z') return; }
  m_dialog->SetEncryptedText(text);
  m_dialog->SetKey(key);
  m_dialog->Deencrypt();

  const std::string result = m_dialog->GetPlainText();
  if (ui->edit_plaintext->text().toStdString() != result)
  {
    ui->edit_plaintext->setText(result.c_str());
  }
}

void ribi::QtVigenereCipherMainDialog::on_edit_plaintext_textChanged(const QString &)
{
  on_button_encrypt_clicked();
}

void ribi::QtVigenereCipherMainDialog::on_edit_encrypted_text_textChanged(const QString &)
{
  on_button_deencrypt_clicked();
}

#ifndef NDEBUG
void ribi::QtVigenereCipherMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

