#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtmultiencrangermaindialog.h"

#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "encranger.h"
#include "loopreader.h"
#include "qtaboutdialog.h"
#include "ui_qtmultiencrangermaindialog.h"
#include "multiencrangermaindialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtToolMultiEncrangerMainDialog::QtToolMultiEncrangerMainDialog(QWidget *parent) noexcept
 :  QtHideAndShowDialog(parent),
    ui(new Ui::QtToolMultiEncrangerMainDialog),
    m_dialog(new ToolMultiEncrangerMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolMultiEncrangerMainDialog::~QtToolMultiEncrangerMainDialog() noexcept
{
  delete ui;
  delete m_dialog;
}

void ribi::QtToolMultiEncrangerMainDialog::on_button_encrypt_clicked() noexcept
{
  const int key = ui->box_key->value();
  assert(key >= 0);

  m_dialog->SetPlainText(ui->edit_plaintext->toPlainText().toStdString());
  m_dialog->SetKey(key);
  m_dialog->Encrypt();
  ui->edit_encrypted_text->setPlainText(m_dialog->GetEncryptedText().c_str());
}

void ribi::QtToolMultiEncrangerMainDialog::on_button_deencrypt_clicked() noexcept
{
  const int key = ui->box_key->value();
  m_dialog->SetEncryptedText(ui->edit_encrypted_text->toPlainText().toStdString());
  m_dialog->SetKey(key);
  m_dialog->Deencrypt();
  ui->edit_plaintext->setPlainText(m_dialog->GetPlainText().c_str());
}

#ifndef NDEBUG
void ribi::QtToolMultiEncrangerMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ToolMultiEncrangerMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
