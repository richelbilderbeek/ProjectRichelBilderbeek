#include "qtstochasticityinspectorsupportwidget.h"

#include <cmath>
#include <boost/math/distributions/chi_squared.hpp>

#include "ui_qtstochasticityinspectorsupportwidget.h"

QtStochasticityInspectorSupportWidget::QtStochasticityInspectorSupportWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtStochasticityInspectorSupportWidget),
  m_critical_value{0.0},
  m_delta{0.0}
{
  ui->setupUi(this);

  QObject::connect(ui->box_alpha,SIGNAL(valueChanged(double)),this,SLOT(OnChiChanged()));
  QObject::connect(ui->box_dof,SIGNAL(valueChanged(int)),this,SLOT(OnChiChanged()));

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
  ui->edit_l0->setText(std::to_string(log_likelihood_bm).c_str());
  ui->edit_l1->setText(std::to_string(log_likelihood_ou).c_str());

  //BM is H_0, OU is H_1
  m_delta = 2.0 * (std::log(log_likelihood_ou) - std::log(log_likelihood_bm) );
  ui->edit_delta->setText(std::to_string(m_delta).c_str());

  if (m_delta < m_critical_value)
  {
    ui->label_conclusion->setText("Cannot reject H0: values observed are BM");
  }
  else
  {
    ui->label_conclusion->setText("Reject H0: values observed are not BM");
  }
}
