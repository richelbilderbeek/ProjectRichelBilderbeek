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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtencrangermaindialog.h"

#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "encranger.h"
#include "loopreader.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtencrangermaindialog.h"
#include "encrangermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtToolEncrangerMainDialog::QtToolEncrangerMainDialog(QWidget *parent) noexcept
 :  QtHideAndShowDialog(parent),
    ui(new Ui::QtToolEncrangerMainDialog),
    m_dialog(new ToolEncrangerMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolEncrangerMainDialog::~QtToolEncrangerMainDialog() noexcept
{
  delete ui;
  delete m_dialog;
}

void ribi::QtToolEncrangerMainDialog::on_button_encrypt_clicked() noexcept
{
  const int key = ui->box_key->value();
  assert(key >= 0);
  m_dialog->SetPlainText(ui->edit_plaintext->text().toStdString());
  m_dialog->SetKey(key);
  m_dialog->Encrypt();
  ui->edit_encrypted_text->setText(m_dialog->GetEncryptedText().c_str());
}

void ribi::QtToolEncrangerMainDialog::on_button_deencrypt_clicked() noexcept
{
  const int key = ui->box_key->value();
  m_dialog->SetEncryptedText(ui->edit_encrypted_text->text().toStdString());
  m_dialog->SetKey(key);
  m_dialog->Deencrypt();
  ui->edit_plaintext->setText(m_dialog->GetPlainText().c_str());
}

#ifndef NDEBUG
void ribi::QtToolEncrangerMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Encranger(0);
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
