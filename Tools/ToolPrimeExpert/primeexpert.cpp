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
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include "primeexpert.h"

ribi::PrimeExpert::PrimeExpert()
  : mPrimes{}
{
  mPrimes.push_back(2);
}

void ribi::PrimeExpert::CalculateNextPrime()
{
  const int heighestKnownPrime = mPrimes.back();

  for (int i = heighestKnownPrime + 1; ;++i)
  {
    if (this->IsPrime(i)) { mPrimes.push_back(i); return; }
  }
}

int ribi::PrimeExpert::CalculateMax(const int x)
{
  return 1 + static_cast<int>(
    std::sqrt(static_cast<double>(x) ) );

}

std::string ribi::PrimeExpert::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::PrimeExpert::GetVersionHistory() noexcept
{
  return {
    "2008-07-12: Version 1.0: initial version in C++ Builder",
    "2011-02-26: Version 2.0: port to Qt Creator"
  };
}

bool ribi::PrimeExpert::IsPrime(const int x)
{
  assert(x > 2);
  //Calculate the maximum value for devision
  const int max = CalculateMax(x);

  assert(CalculateMax( 4) == 3); //When examining 4, divide (from 2) to 3
  assert(CalculateMax( 5) == 3);
  assert(CalculateMax( 6) == 3);
  assert(CalculateMax( 7) == 3);
  assert(CalculateMax( 8) == 3);
  assert(CalculateMax( 9) == 4); //When examining 9, divide (from 2) to 4
  assert(CalculateMax(10) == 4);
  assert(CalculateMax(11) == 4);
  assert(CalculateMax(12) == 4);
  assert(CalculateMax(13) == 4);
  assert(CalculateMax(14) == 4);
  assert(CalculateMax(15) == 4);
  assert(CalculateMax(16) == 5); //When examining 16, divide (from 2) to 5
  assert(CalculateMax(17) == 5);

  //Collect enough prime numbers to find if x is prime,
  //  if these are not yet present
  while ( mPrimes.back() < CalculateMax(x) )
    CalculateNextPrime();

  for (int i=0; ;++i)
  {
    assert( i < static_cast<int>(mPrimes.size() ) );
    const int knownPrime = mPrimes[i];
    if (knownPrime >= max) return true;
    if ( x % knownPrime == 0) return false;
  }

}

std::ostream& ribi::operator<<(std::ostream& os, const PrimeExpert& primeExpert)
{
  std::copy(
    primeExpert.mPrimes.begin(),
    primeExpert.mPrimes.end(),
    std::ostream_iterator<int>(os," ") );
  return os;
}
