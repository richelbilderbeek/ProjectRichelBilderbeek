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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestencrangerdialog.h"

#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "encranger.h"
#include "loopreader.h"
#include "qtaboutdialog.h"
#include "ui_qttestencrangerdialog.h"
#include "testencrangerdialog.h"
#pragma GCC diagnostic pop

ribi::QtTestEncrangerDialog::QtTestEncrangerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestEncrangerDialog),
    m_dialog(new TestEncrangerDialog)
{
  ui->setupUi(this);
}

ribi::QtTestEncrangerDialog::~QtTestEncrangerDialog()
{
  delete ui;
  delete m_dialog;
}

void ribi::QtTestEncrangerDialog::on_button_encrypt_clicked()
{
  try
  {
    boost::lexical_cast<int>(ui->edit_key->text().toStdString());
  }
  catch (boost::bad_lexical_cast&)
  {
    ui->edit_encrypted_text->setText("ERROR: Key must be a positive number");
    return;
  }
  const int key = boost::lexical_cast<int>(ui->edit_key->text().toStdString());
  if (key < 0)
  {
    ui->edit_encrypted_text->setText("ERROR: Key must be a positive number");
    return;
  }

  m_dialog->SetPlainText(ui->edit_plaintext->text().toStdString());
  m_dialog->SetKey(key);
  m_dialog->Encrypt();
  ui->edit_encrypted_text->setText(m_dialog->GetEncryptedText().c_str());
}

void ribi::QtTestEncrangerDialog::on_button_deencrypt_clicked()
{
  try
  {
    boost::lexical_cast<int>(ui->edit_key->text().toStdString());
  }
  catch (boost::bad_lexical_cast&)
  {
    ui->edit_encrypted_text->setText("ERROR: Key must be a positive number");
    return;
  }
  const int key = boost::lexical_cast<int>(ui->edit_key->text().toStdString());
  if (key < 0)
  {
    ui->edit_encrypted_text->setText("ERROR: Key must be a positive number");
    return;
  }

  m_dialog->SetEncryptedText(ui->edit_encrypted_text->text().toStdString());
  m_dialog->SetKey(key);
  m_dialog->Deencrypt();
  ui->edit_plaintext->setText(m_dialog->GetPlainText().c_str());
}

void ribi::QtTestEncrangerDialog::on_button_about_clicked()
{
  About a = TestEncrangerDialog::GetAbout();
  QtAboutDialog d(a);
  d.exec();
}

