//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
  Copyright (C) 2009  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitHelperFunctionsH
#define UnitHelperFunctionsH
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
#include <fstream>

#ifndef USE_STL_ONLY
  #include <System.hpp>
#endif

unsigned int totalSum(const std::vector<unsigned int>& myVector);
template<class T> T totalSum(const std::vector<T>& myVector);
unsigned int getIndexLowestValue(const std::vector<double>& myVector);
unsigned int getIndexHighestValue(const std::vector<double>& myVector);
template <class T> void meanAndStdDev(const std::vector<T>& myVector, double& mean, double& stdDev);


std::string itoa(const int& x);
std::string ftoa(const double& x);
bool fileExists(const std::string& fileName);
std::string doubleToBitString(const double& anyDouble);

void Dot(const std::string& message);
void Dot(const std::vector<unsigned int>& myVector);
void Dot(const std::vector<int>& myVector);
void Dot(const std::vector<double>& myVector);

#endif
