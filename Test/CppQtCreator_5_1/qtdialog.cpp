#include "qtdialog.h"
#include "ui_qtdialog.h"

//#include <cstdlib>
#include <string>
//#include <boost/lexical_cast.hpp>
#include <sstream>

///GetGccVersion returns the version number of GCC currently installed.
///From http://www.richelbilderbeek.nl/CppGetGccVersion.htm
const std::string GetGccVersion()
{
  std::stringstream s;
  s << (__GNUC__)
    << std::string(".")
    << (__GNUC_MINOR__)
    << std::string(".")
    << (__GNUC_PATCHLEVEL__);
  return s.str();
}

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  //this->setWindowTitle(GetGccVersion().c_str());
}

QtDialog::~QtDialog()
{
  delete ui;
}
