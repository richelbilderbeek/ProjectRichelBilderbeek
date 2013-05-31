#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#include <QtGui/QApplication>
//---------------------------------------------------------------------------
#include "BigInteger.hh"
//---------------------------------------------------------------------------
#include "dialogtestmanydigitnewick.h"
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  DialogTestManyDigitNewick w;
  w.show();
  return a.exec();
}
//---------------------------------------------------------------------------

