#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include "qtdialog.h"
#include "ui_qtdialog.h"

#include <iostream>
#include <string>
#include <vector>


const std::vector<std::string> SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}


QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  const std::vector<std::string> v = SeperateString("1,2,3,4",',');
  BOOST_FOREACH(const std::string s, v) { std::cout << boost::lexical_cast<int>(s) << ','; }
}

QtDialog::~QtDialog()
{
  delete ui;
}
