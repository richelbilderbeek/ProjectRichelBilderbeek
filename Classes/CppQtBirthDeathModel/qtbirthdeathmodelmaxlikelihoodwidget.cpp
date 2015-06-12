#include "qtbirthdeathmodelmaxlikelihoodwidget.h"

#include <cassert>
#include "birthdeathmodelhelper.h"

#include "ui_qtbirthdeathmodelmaxlikelihoodwidget.h"

QtBirthDeathModelMaxLikelihoodWidget::QtBirthDeathModelMaxLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBirthDeathModelMaxLikelihoodWidget),
  m_phylogeny{}
{
  ui->setupUi(this);
}

QtBirthDeathModelMaxLikelihoodWidget::~QtBirthDeathModelMaxLikelihoodWidget()
{
  delete ui;
}

void QtBirthDeathModelMaxLikelihoodWidget::SetPhylogeny(const std::string& phylogeny)
{
  if (m_phylogeny == phylogeny) return;

  using Rate = ribi::units::Rate;

  m_phylogeny = phylogeny;

  Rate birth_rate{0.0 / boost::units::si::second};
  Rate death_rate{0.0 / boost::units::si::second};
  ribi::bdm::Helper().CalcMaxLikelihood(
    phylogeny,
    birth_rate,
    death_rate
  );
  ui->edit_birth_rate->setText(std::to_string(birth_rate.value()).c_str());
  ui->edit_death_rate->setText(std::to_string(death_rate.value()).c_str());

  const double max_log_likelihood{
    ribi::bdm::Helper().CalcLogLikelihoodDdd(
      phylogeny,
      birth_rate,
      death_rate,
      ribi::bdm::Helper::Part::phylogeny
    )
  };
  ui->edit_log_likelihood_phylogeny->setText(std::to_string(max_log_likelihood).c_str());
}
