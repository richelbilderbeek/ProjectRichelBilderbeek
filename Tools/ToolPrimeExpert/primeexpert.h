//---------------------------------------------------------------------------
/*
PrimeExpert, class to calculate whether a number is prime
Copyright (C) 2008-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolPrimeExpert.htm
//---------------------------------------------------------------------------
#ifndef PRIMEEXPERT_H
#define PRIMEEXPERT_H

#include <string>
#include <vector>

namespace ribi {

struct PrimeExpert
{
  PrimeExpert();

  bool IsPrime(const int x);

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  std::vector<int> mPrimes;

  void CalculateNextPrime();
  int CalculateMax(const int x);
  friend std::ostream& operator<<(std::ostream&, const PrimeExpert&);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const PrimeExpert& primeExpert);

} //~namespace ribi

#endif // PRIMEEXPERT_H
