//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
Copyright (C) 2010-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm
//---------------------------------------------------------------------------
#ifndef DIALOGSIMPLIFYNEWICK_H
#define DIALOGSIMPLIFYNEWICK_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
//#include <cln/cln.h>
#include "about.h"
#include "BigInteger.hh"
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class DialogSimplifyNewick;
}
//---------------------------------------------------------------------------
class DialogSimplifyNewick : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSimplifyNewick(QWidget *parent = 0);
  ~DialogSimplifyNewick();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogSimplifyNewick *ui;

private slots:
  void onAbout();
  void onEditChange();
  void onStart();

  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
///CliToStr converts a cln::cl_I to std::string.
///From http://www.richelbilderbeek.nl/CppCliToStr.htm
//const std::string CliToStr(const cln::cl_I& i);
//---------------------------------------------------------------------------
///IntToStrWithSep converts an integer to std::string
///and adds thousands seperators.
///From http://www.richelbilderbeek.nl/CppIntToStrWithSep.htm
//const std::string IntToStrWithSep(cln::cl_I i);
//---------------------------------------------------------------------------
///GetMaxInt returns the highest possible value of a int.
///From http://www.richelbilderbeek.nl/CppGetMaxInt.htm
int GetMaxInt();
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer();
//---------------------------------------------------------------------------
///SafeIntToCli converts an int to cln::cl_I safely.
///From http://www.richelbilderbeek.nl/CppSafeIntToCli.htm
//const cln::cl_I SafeIntToCli(const int i);
//---------------------------------------------------------------------------
///SimplifyNewick simplifies a Newick below a certain complexity.
///From http://www.richelbilderbeek.nl/CppSimplifyNewick.htm
//const std::string SimplifyNewick(
//  const std::string& newick, const cln::cl_I& max_complexity);
//---------------------------------------------------------------------------
///SimplifyNewick simplifies a Newick below a certain complexity.
///From http://www.richelbilderbeek.nl/CppSimplifyNewick.htm
const std::string SimplifyNewick(
  const std::string& newick, const BigInteger& max_complexity);
//---------------------------------------------------------------------------
#endif // DIALOGSIMPLIFYNEWICK_H
