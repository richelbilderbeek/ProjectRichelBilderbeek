#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtalphafilterdialog.h"

#include <cassert>
#include "alphafilter.h"
#include "ui_qtalphafilterdialog.h"

#pragma GCC diagnostic pop

ribi::QtAlphaFilterDialog::QtAlphaFilterDialog(QWidget *parent) noexcept
  : QDialog(parent),
    ui(new Ui::QtAlphaFilterDialog)
{
  ui->setupUi(this);
}

ribi::QtAlphaFilterDialog::~QtAlphaFilterDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::AlphaFilter> ribi::QtAlphaFilterDialog::Create() const noexcept
{
  const double alpha  = ui->box_alpha->value();
  const double dt =  ui->box_dt->value();
  const boost::shared_ptr<AlphaFilter> filter(new AlphaFilter(alpha,dt));
  assert(filter);
  return filter;
}
