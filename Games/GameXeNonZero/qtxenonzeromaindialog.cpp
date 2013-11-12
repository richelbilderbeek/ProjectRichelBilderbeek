#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtxenonzeromaindialog.h"

#include <cassert>

#include "xenonzeromaindialog.h"
#include "ui_qtxenonzeromaindialog.h"
#pragma GCC diagnostic pop

ribi::QtXeNonZeroMainDialog::QtXeNonZeroMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtXeNonZeroMainDialog),
    m_dialog(new xnz::Dialog)
{
  ui->setupUi(this);
  assert(m_dialog);
  on_button_space_clicked();
}

ribi::QtXeNonZeroMainDialog::~QtXeNonZeroMainDialog()
{
  delete ui;
}

void ribi::QtXeNonZeroMainDialog::Display(const boost::shared_ptr<const xnz::Area> area)
{
  assert(area);
  std::string text;
  const auto v = area->GetArea();
  for (const auto s: v) { text += s + "\n"; }
  ui->text->setPlainText(text.c_str());
}

void ribi::QtXeNonZeroMainDialog::on_button_a_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::left));
}

void ribi::QtXeNonZeroMainDialog::on_button_d_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::right));
}

void ribi::QtXeNonZeroMainDialog::on_button_e_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::shoot));
}

void ribi::QtXeNonZeroMainDialog::on_button_s_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::down));
}

void ribi::QtXeNonZeroMainDialog::on_button_space_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::space));
}

void ribi::QtXeNonZeroMainDialog::on_button_w_clicked()
{
  assert(m_dialog);
  Display(m_dialog->ProcessInput(xnz::Dialog::Input::up));
}
