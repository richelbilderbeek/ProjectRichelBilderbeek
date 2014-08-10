#include "qtpredickadvocatormaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

#include "testtimer.h"
#include "trace.h"
#include "ui_qtpredickadvocatormaindialog.h"
#pragma GCC diagnostic pop

ribi::QtPreDickAdvocaTorMainDialog::QtPreDickAdvocaTorMainDialog(
  const int seed,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPreDickAdvocaTorMainDialog),
    m_dialog(seed)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  const int sz = m_dialog.GetTeamNames().size();
  for (int i = 0; i!=sz; ++i)
  {
    const QString name = m_dialog.GetTeamNames()[i].c_str();
    ui->box_left->addItem(name);
    ui->box_right->addItem(name);
  }

  OnAnyChange();

}

ribi::QtPreDickAdvocaTorMainDialog::~QtPreDickAdvocaTorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtPreDickAdvocaTorMainDialog::OnAnyChange()
{
  const int index1 = ui->box_left->currentIndex();
  const int index2 = ui->box_right->currentIndex();
  if (index1 < 0 || index2 < 0) return;
  assert(index1 >= 0);
  assert(index2 >= 0);
  if (index1==index2)
  {
    ui->label1->setText("-");
    ui->label2->setText("-");
  }
  else
  {

    assert(index1 < static_cast<int>(m_dialog.GetTeamScores().size()));
    assert(index2 < static_cast<int>(m_dialog.GetTeamScores().size()));
    assert(index2 < static_cast<int>(m_dialog.GetTeamScores()[index1].size()));
    assert(index1 < static_cast<int>(m_dialog.GetTeamScores()[index2].size()));
    const int score1 = m_dialog.GetTeamScores()[index1][index2];
    const int score2 = m_dialog.GetTeamScores()[index2][index1];
    QString s1; s1.setNum(score1);
    QString s2; s2.setNum(score2);

    ui->label1->setText(s1);
    ui->label2->setText(s2);
  }
}



void ribi::QtPreDickAdvocaTorMainDialog::on_box_left_currentIndexChanged(int)
{
  OnAnyChange();
}

void ribi::QtPreDickAdvocaTorMainDialog::on_box_right_currentIndexChanged(int)
{
  OnAnyChange();
}

#ifndef NDEBUG
void ribi::QtPreDickAdvocaTorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  PreDickAdvocaTorMainDialog(0);
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
