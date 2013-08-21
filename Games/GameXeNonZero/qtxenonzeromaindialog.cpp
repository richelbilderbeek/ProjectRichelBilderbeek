#include "qtxenonzeromaindialog.h"

#include <cassert>

#include "gamexenonzerodialog.h"
#include "ui_qtxenonzeromaindialog.h"

QtXeNonZeroMainDialog::QtXeNonZeroMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtXeNonZeroMainDialog),
  m_dialog(new xnz::Dialog)
{
  ui->setupUi(this);
  assert(m_dialog);
  on_button_space_clicked();
}

QtXeNonZeroMainDialog::~QtXeNonZeroMainDialog()
{
  delete ui;
}

void QtXeNonZeroMainDialog::Display(const boost::shared_ptr<const xnz::Area> area)
{
  assert(area);
  std::string text;
  const auto v = area->GetArea();
  for (const auto s: v) { text += s + "\n"; }
  ui->text->setPlainText(text.c_str());
}

void QtXeNonZeroMainDialog::on_button_a_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::left));
}

void QtXeNonZeroMainDialog::on_button_d_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::right));
}

void QtXeNonZeroMainDialog::on_button_e_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::shoot));

}

void QtXeNonZeroMainDialog::on_button_s_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::down));
}

void QtXeNonZeroMainDialog::on_button_space_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::space));
}

void QtXeNonZeroMainDialog::on_button_w_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::up));
}
