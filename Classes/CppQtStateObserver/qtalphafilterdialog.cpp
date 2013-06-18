#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtalphafilterdialog.h"

#include <cassert>
#include "alphafilter.h"
#include "ui_qtalphafilterdialog.h"

QtAlphaFilterDialog::QtAlphaFilterDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtAlphaFilterDialog)
{
  ui->setupUi(this);
}

QtAlphaFilterDialog::~QtAlphaFilterDialog()
{
  delete ui;
}

boost::shared_ptr<AlphaFilter> QtAlphaFilterDialog::Create() const
{
  const double alpha  = ui->box_alpha->value();
  const double dt =  ui->box_dt->value();
  const boost::shared_ptr<AlphaFilter> filter(new AlphaFilter(alpha,dt));
  assert(filter);
  return filter;
}
