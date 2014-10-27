//---------------------------------------------------------------------------
/*
Biology, biology-related functions and classes
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppBiology.htm
//---------------------------------------------------------------------------
#ifndef RIBI_BIOLOGY_H
#define RIBI_BIOLOGY_H

#include <iosfwd>
#include <string>
#include <vector>

namespace ribi {

///Biology contains biology-related classes and functions
struct Biology
{
  explicit Biology() noexcept;
  typedef double DnDt;
  typedef double PopSize;

  /// What is the growth of a logistically-growing population?
  ///
  /// dN              N - K
  /// -- = N * r * ( ------- )
  /// dt                N
  ///
  /// N: Current population size
  /// K: Carrying capacity: the stable population size if r > 1.0
  /// r: intrinsic growth rate, the average number of offspring an individual has
  /// t: time
  DnDt LogisticGrowth(const PopSize carrying_capacity, const PopSize current_population_size, const double intrinsic_growth_rate);

  private:

  #ifndef NDEBUG
  void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_BIOLOGY_H
