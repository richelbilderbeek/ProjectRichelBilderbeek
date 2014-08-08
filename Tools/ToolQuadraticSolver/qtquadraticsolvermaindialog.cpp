#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtquadraticsolvermaindialog.h"

#include <sstream>
#include <string>
#include <vector>



#include <QKeyEvent>

#include "about.h"
#include "trace.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "quadraticsolvermaindialog.h"
#include "quadraticsolvermenudialog.h"
#include "ui_qtquadraticsolvermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtQuadraticSolverMainDialog::QtQuadraticSolverMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtQuadraticSolverMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  OnAnyChange();
}

ribi::QtQuadraticSolverMainDialog::~QtQuadraticSolverMainDialog() noexcept
{
  delete ui;
}

void ribi::QtQuadraticSolverMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtQuadraticSolverMainDialog::OnAnyChange()
{
  const double a = ui->box_a->value();
  const double b = ui->box_b->value();
  const double c = ui->box_c->value();
  const std::vector<double> v = QuadraticSolverMainDialog::SolveQuadratic(a,b,c);
  const std::size_t sz = v.size();
  std::stringstream s;
  s << "Number of solutions: " << sz;
  for (std::size_t i=0; i!=sz; ++i)
  {
    s << "\n#" << i << ": " << v[i];
  }
  const std::string text = s.str();
  ui->text->setPlainText(text.c_str());
}


void ribi::QtQuadraticSolverMainDialog::on_box_a_valueChanged(double)
{
  OnAnyChange();
}

void ribi::QtQuadraticSolverMainDialog::on_box_b_valueChanged(double)
{
  OnAnyChange();
}

void ribi::QtQuadraticSolverMainDialog::on_box_c_valueChanged(double)
{
  OnAnyChange();
}

#ifndef NDEBUG
void ribi::QtQuadraticSolverMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
