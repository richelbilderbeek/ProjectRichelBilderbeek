#include "qtbirthdeathmodellikelihoodwidget.h"

#include <cassert>
#include "birthdeathmodelhelper.h"

#include "ui_qtbirthdeathmodellikelihoodwidget.h"

QtBirthDeathModelLikelihoodWidget::QtBirthDeathModelLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBirthDeathModelLikelihoodWidget),
  m_phylogeny{}
{
  ui->setupUi(this);

  QObject::connect(ui->box_birth_rate,SIGNAL(valueChanged(double)),this,SLOT(OnParameterChanged()));
  QObject::connect(ui->box_death_rate,SIGNAL(valueChanged(double)),this,SLOT(OnParameterChanged()));
}

QtBirthDeathModelLikelihoodWidget::~QtBirthDeathModelLikelihoodWidget()
{
  delete ui;
}

void QtBirthDeathModelLikelihoodWidget::OnParameterChanged()
{
  const double log_likelihood_phylogeny{
    ribi::bdm::Helper().CalcLogLikelihoodDdd(
      m_phylogeny,
      ui->box_birth_rate->value() / boost::units::si::second,
      ui->box_death_rate->value() / boost::units::si::second,
      ribi::bdm::Helper::Part::phylogeny
    )
  };
  ui->edit_log_likelihood_phylogeny->setText(std::to_string(log_likelihood_phylogeny).c_str());
}

void QtBirthDeathModelLikelihoodWidget::SetPhylogeny(const std::string& phylogeny)
{
  if (m_phylogeny == phylogeny) return;

  m_phylogeny = phylogeny;
  OnParameterChanged();
}
