#include "qtstochasticityinspectoraicwidget.h"

#include <cmath>
#include <boost/math/distributions/chi_squared.hpp>

#include <apfloat.h>

#include "ribi_apfloat.h"
#include "testtimer.h"
#include "trace.h"
#include "qtstochasticityinspectormodelcolors.h"
#include "ui_qtstochasticityinspectoraicwidget.h"

QtStochasticityInspectorAicWidget::QtStochasticityInspectorAicWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtStochasticityInspectorAicWidget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  //ui->edit_aic_bm->setFont(QFont("monospace",6));
  //ui->edit_aic_ou->setFont(QFont("monospace",6));
}

QtStochasticityInspectorAicWidget::~QtStochasticityInspectorAicWidget()
{
  delete ui;
}

void QtStochasticityInspectorAicWidget::ShowAic(const double log_likelihood_bm, const double log_likelihood_ou)
{
  ui->edit_ll0->setText(std::to_string(log_likelihood_bm).c_str());
  ui->edit_ll1->setText(std::to_string(log_likelihood_ou).c_str());

  const double aic_bm{
    static_cast<double>(2 * ui->box_k_bm->value())
    - (2.0 * log_likelihood_bm)
  };

  const double aic_ou{
    static_cast<double>(2 * ui->box_k_ou->value())
    - (2.0 * log_likelihood_ou)
  };

  ui->edit_aic_bm->setText(std::to_string(aic_bm).c_str());
  ui->edit_aic_ou->setText(std::to_string(aic_ou).c_str());

  QPalette palette = ui->label_conclusion->palette();
  if (aic_bm < aic_ou)
  {
    palette.setColor(ui->label_conclusion->foregroundRole(),ribi::QtStochasticityInspectorModelColors::m_bm_color);
    ui->label_conclusion->setText("Prefer BM");
  }
  else
  {
    palette.setColor(ui->label_conclusion->foregroundRole(),ribi::QtStochasticityInspectorModelColors::m_ou_color);
    ui->label_conclusion->setText("Prefer OU");
  }
  ui->label_conclusion->setPalette(palette);
}

#ifndef NDEBUG
void QtStochasticityInspectorAicWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::Apfloat();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
