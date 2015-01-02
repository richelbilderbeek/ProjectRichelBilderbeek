#include "dialog.h"

#include <cassert>
#include <iostream>

#include <boost/locale.hpp>
#include <boost/math/constants/constants.hpp>
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);

  const double pi = boost::math::constants::pi<double>();

  assert(std::locale().name() == "C");

  assert(boost::lexical_cast<std::string>(pi)[1] == ',' && "Dutch");

  boost::locale::generator gen;
  std::locale::global(gen(""));
  std::locale::global(gen("en_US.UTF-8"));

  assert(std::locale().name() == "*");

  assert(boost::lexical_cast<std::string>(pi)[1] == ',' && "Dutch");
}

Dialog::~Dialog()
{
  delete ui;
}
