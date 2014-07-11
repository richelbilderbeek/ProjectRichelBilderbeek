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
#pragma hdrstop
#include "UnitHelperFunctions.h"

//#define EXTENSIVE_LOG
//---------------------------------------------------------------------------
bool fileExists(const std::string& fileName)
{
  std::fstream fin;
  fin.open(fileName.c_str(),std::ios::in);
  if( fin.is_open() )
  {
    fin.close();
    return true;
  }
  fin.close();
  return false;
}
//---------------------------------------------------------------------------
 unsigned int totalSum(const std::vector<unsigned int>& myVector)
{
  unsigned int sum=0;
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i)
  {
    sum+=myVector[i];
  }
  return(sum);
}
//---------------------------------------------------------------------------
template<class T> T totalSum(const std::vector<T>& myVector)
{
  T sum=0;
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i)
  {
    sum+=myVector[i];
  }
  return(sum);
}
//---------------------------------------------------------------------------
unsigned int getIndexLowestValue(const std::vector<double>& myVector)
{
  const unsigned int size = myVector.size();
  unsigned int indexLowest = 0;
  double lowestValue = myVector[0];
  for (unsigned int i=1; i<size; ++i)
  {
    const double value = myVector[i];
    if (value < lowestValue)
    {
      lowestValue = value;
      indexLowest = i;
    }
  }
  return indexLowest;
}
//---------------------------------------------------------------------------
unsigned int getIndexHighestValue(const std::vector<double>& myVector)
{
  const unsigned int size = myVector.size();
  unsigned int indexHighest = 0;
  double highestValue = myVector[0];
  for (unsigned int i=1; i<size; ++i)
  {
    const double value = myVector[i];
    if (value > highestValue)
    {
      highestValue = value;
      indexHighest = i;
    }
  }
  return indexHighest;
}
//---------------------------------------------------------------------------
std::string doubleToBitString(const double& anyDouble)
{
  static union MyUnion
  {
    unsigned int myInts[2];
    double myDouble;
  } myUnion;
  myUnion.myDouble = anyDouble;

  unsigned int myInt0 = myUnion.myInts[0];
  unsigned int myInt1 = myUnion.myInts[1];
  std::string myBitString;
  for (unsigned int i = 0; i<32; ++i)
  {
    if (myInt0%2==0)
      myBitString = "0" + myBitString;
    else
      myBitString = "1" + myBitString;
    myInt0>>=1;
  }
  for (unsigned int i = 0; i<32; ++i)
  {
    if (myInt1%2==0)
      myBitString = "0" + myBitString;
    else
      myBitString = "1" + myBitString;
    myInt1>>=1;
  }
  return myBitString;
}
//---------------------------------------------------------------------------
template <class T>
void meanAndStdDev(const std::vector<T>& myVector, double& mean, double& stdDev)
{
  const unsigned int size = myVector.size();
  assert(size>1);
  const double dSize = static_cast<double>(size);
  mean = 0;
  double sumX = 0;
  double sumXsquared = 0;
  for (unsigned int i=0; i<size; ++i)
  {
    const T value = myVector[i];
    sumX+=value;
    sumXsquared+=(value*value);
    mean+=value;
  }

  mean/=dSize;
  stdDev = std::sqrt(((dSize*sumXsquared)-(sumX*sumX))/(dSize *(dSize-1.0)));
}
//---------------------------------------------------------------------------
std::string ftoa(const double& x)
{
  std::ostringstream o;
  if (!(o << x)) return "ERROR";
  return o.str();
}
//---------------------------------------------------------------------------
std::string itoa(const int& x)
{
  std::ostringstream o;
  if (!(o << x)) return "ERROR";
  return o.str();
}
//---------------------------------------------------------------------------
void Dot(const std::string& message)
{
  #ifndef NDEBUG
    #ifndef USE_STL_ONLY
      OutputDebugString(message.c_str());
    #else
      std::cout << "ODS: " << message << std::endl;
    #endif
  #endif
}
//---------------------------------------------------------------------------
void Dot(const std::vector<double>& myVector)
{
  #ifndef NDEBUG
  std::string output = "index: ";
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i)
  {
    output+=ftoa(myVector[i])+" ";
  }
  Dot(output);
  #endif
}
//---------------------------------------------------------------------------
void Dot(const std::vector<int>& myVector)
{
  #ifndef NDEBUG
  std::string output = "index: ";
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i)
  {
    output+=itoa(myVector[i])+" ";
  }
  Dot(output);
  #endif
}
//---------------------------------------------------------------------------
void Dot(const std::vector<unsigned int>& myVector)
{
  #ifndef NDEBUG
  std::string output = "index: ";
  const unsigned int size = myVector.size();
  for (unsigned int i=0; i<size; ++i)
  {
    output+=itoa(myVector[i])+" ";
  }
  Dot(output);
  #endif
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
