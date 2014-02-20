#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtxenonzeromaindialog.h"

#include <cassert>

#include "xenonzeromaindialog.h"
#include "ui_qtxenonzeromaindialog.h"
#include "textcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtXeNonZeroMainDialog::QtXeNonZeroMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtXeNonZeroMainDialog),
    m_dialog(new xnz::Dialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  assert(m_dialog);
  on_button_space_clicked();
}

ribi::QtXeNonZeroMainDialog::~QtXeNonZeroMainDialog() noexcept
{
  delete ui;
}

void ribi::QtXeNonZeroMainDialog::Display(const boost::shared_ptr<const xnz::Area> area)
{
  assert(area);
  std::string text;
  const boost::shared_ptr<const TextCanvas> v { area->CreateTextCanvas() };
  ui->text->setPlainText(v->ToString().c_str());
}

void ribi::QtXeNonZeroMainDialog::on_button_a_clicked()
{
  assert(m_dialog);
  Display(m_dialog->OnKeyPress(xnz::Key::left));
}

void ribi::QtXeNonZeroMainDialog::on_button_d_clicked()
{
  assert(m_dialog);
  Display(m_dialog->OnKeyPress(xnz::Key::right));
}

void ribi::QtXeNonZeroMainDialog::on_button_e_clicked()
{
  assert(m_dialog);
  Display(m_dialog->OnKeyPress(xnz::Key::shoot));
}

void ribi::QtXeNonZeroMainDialog::on_button_s_clicked()
{
  assert(m_dialog);
  Display(m_dialog->OnKeyPress(xnz::Key::down));
}

void ribi::QtXeNonZeroMainDialog::on_button_space_clicked()
{
  assert(m_dialog);
  Display(m_dialog->OnKeyPress(xnz::Key::space));
}

void ribi::QtXeNonZeroMainDialog::on_button_w_clicked()
{
  assert(m_dialog);
  Display(m_dialog->OnKeyPress(xnz::Key::up));
}

#ifndef NDEBUG
void ribi::QtXeNonZeroMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtXeNonZeroMainDialog::Test");
  TRACE("Finished ribi::QtXeNonZeroMainDialog::Test successfully");
}
#endif
