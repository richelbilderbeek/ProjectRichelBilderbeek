#include "qtstochasticityinspectorsupportwidget.h"

#include <cmath>
#include <boost/math/distributions/chi_squared.hpp>

#include <apfloat.h>

#include "ribi_apfloat.h"
#include "testtimer.h"
#include "trace.h"
#include "qtstochasticityinspectormodelcolors.h"
#include "ui_qtstochasticityinspectorsupportwidget.h"

QtStochasticityInspectorSupportWidget::QtStochasticityInspectorSupportWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtStochasticityInspectorSupportWidget),
  m_critical_value{0.0},
  m_delta{0.0}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  QObject::connect(ui->box_alpha,SIGNAL(valueChanged(double)),this,SLOT(OnChiChanged()));
  QObject::connect(ui->box_dof,SIGNAL(valueChanged(int)),this,SLOT(OnChiChanged()));

  ui->edit_l0->setFont(QFont("monospace",6));
  ui->edit_l1->setFont(QFont("monospace",6));
  ui->edit_delta->setFont(QFont("monospace",6));

  OnChiChanged();
}

QtStochasticityInspectorSupportWidget::~QtStochasticityInspectorSupportWidget()
{
  delete ui;
}

void QtStochasticityInspectorSupportWidget::OnChiChanged()
{
  const double alpha{ui->box_alpha->value()};
  const int dof{ui->box_dof->value()};
  boost::math::chi_squared_distribution<double> distribution(dof);
  m_critical_value = boost::math::quantile(boost::math::complement(distribution,alpha));
  ui->edit_critical_value->setText(std::to_string(m_critical_value).c_str());
}

void QtStochasticityInspectorSupportWidget::ShowSupport(const double log_likelihood_bm, const double log_likelihood_ou)
{
  ui->edit_ll0->setText(std::to_string(log_likelihood_bm).c_str());
  ui->edit_ll1->setText(std::to_string(log_likelihood_ou).c_str());

  const apfloat likelihood_bm{exp(apfloat(log_likelihood_bm))};
  const apfloat likelihood_ou{exp(apfloat(log_likelihood_ou))};

  //BM is H_0, OU is H_1
  m_delta = apfloat(2.0) * (likelihood_ou - likelihood_bm);


  ui->edit_l0->setText(ribi::Apfloat().ToStr(likelihood_bm).c_str());
  ui->edit_l1->setText(ribi::Apfloat().ToStr(likelihood_ou).c_str());
  ui->edit_delta->setText(ribi::Apfloat().ToStr(m_delta).c_str());

  QPalette palette = ui->label_conclusion->palette();
  if (m_delta < m_critical_value)
  {
    palette.setColor(ui->label_conclusion->foregroundRole(),ribi::QtStochasticityInspectorModelColors::m_bm_color);
    ui->label_conclusion->setText("Cannot reject H0: values observed are BM");
  }
  else
  {
    palette.setColor(ui->label_conclusion->foregroundRole(),ribi::QtStochasticityInspectorModelColors::m_ou_color);
    ui->label_conclusion->setText("Reject H0: values observed are not BM");
  }
  ui->label_conclusion->setPalette(palette);
}

#ifndef NDEBUG
void QtStochasticityInspectorSupportWidget::Test() noexcept
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
