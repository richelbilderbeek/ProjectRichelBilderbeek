//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
Copyright (C) 2010-2015 Richel Bilderbeek

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
#ifndef TOOLSIMPLIFYNEWICKMAINDIALOG_H
#define TOOLSIMPLIFYNEWICKMAINDIALOG_H

#include <string>
#include <vector>

struct BigInteger;

namespace ribi {

struct ToolSimplifyNewickMainDialog
{
  ///SimplifyNewick simplifies a Newick below a certain complexity,
  ///in a frequency dependent way.
  ///For example, for the phylogeny (100,2), SimplifyNewick
  ///returns (99,2) 50x as often as (100,1).
  ///From http://www.richelbilderbeek.nl/CppSimplifyNewick.htm
  static std::string SimplifyNewick(
    const std::string& s,
    const BigInteger& max_complexity);

  private:
  static int SumSecond(const std::vector<std::pair<std::vector<int>,int> >& v) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TOOLSIMPLIFYNEWICKMAINDIALOG_H
