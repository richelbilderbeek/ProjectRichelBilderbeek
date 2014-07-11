//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Richel Bilderbeek

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
//---------------------------------------------------------------------------
//#define NDOT
//---------------------------------------------------------------------------
#include "UnitHelperFunctions.h"
//---------------------------------------------------------------------------
#include <vcl>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>
//---------------------------------------------------------------------------
#include "UnitSimulationParameters.h"
//---------------------------------------------------------------------------
namespace helper
{
  //---------------------------------------------------------------------------
  ///Checks whether a std::string can be converted to an integer.
  ///Returns true if possible, also returning this integer by referencing.
  ///Returns false otherwise, setting the referenced integer to zero.
  bool isInt(const std::string& s, int& rInt)
  {
    std::istringstream i(s);
    if (!(i >> rInt))
    {
      rInt = 0;
      return false;
    }
    return true;
  }
  //---------------------------------------------------------------------------
  ///Checks whether a std::string can be converted to a double.
  ///Returns true if possible, also returning this double by referencing.
  ///Returns false otherwise, setting the referenced double to zero.
  bool isDouble(const std::string& s, double& rDouble)
  {
    std::istringstream i(s);
    if (!(i >> rDouble))
    {
      rDouble = 0.0;
      return false;
    }
    return true;
  }
  //---------------------------------------------------------------------------
  std::string itoa(const int& x)
  {
    std::ostringstream o;
    if (!(o << x)) return "ERROR";
    return o.str();
  }
  //---------------------------------------------------------------------------
  std::string ftoa(const double& x)
  {
    std::ostringstream o;
    if (!(o << x)) return "ERROR";
    return o.str();
  }
  //---------------------------------------------------------------------------
  void dot(const std::string& s)
  {
    #ifndef NDOT
    OutputDebugString(s.c_str());
    #endif
  }
  //---------------------------------------------------------------------------
  void dot(const char* s)
  {
    #ifndef NDOT
    OutputDebugString(s);
    #endif
  }
  //---------------------------------------------------------------------------
  void dot(const int& i)
  {
    #ifndef NDOT
    OutputDebugString(IntToStr(i).c_str());
    #endif
  }
  //---------------------------------------------------------------------------
  void plot(const std::vector<int>& values, TChartSeries* Series)
  {
    const int size = values.size();
    for (int i=0; i<size; ++i)
    {
      Series->AddXY(i,values[i]);
    }
  }
  //---------------------------------------------------------------------------
  void log(std::vector<std::string> myLog, TRichEdit * richEdit)
  {
    const int size = myLog.size();
    for (int i=0; i<size; ++i)
    {
      richEdit->Lines->Add( myLog[i].c_str() );
    }
  }
  //---------------------------------------------------------------------------
  void emptyChart(TChart * chart)
  {
    const int nSeries = chart->SeriesCount();
    for (int i=0; i<nSeries; ++i)
    {
      chart->Series[i]->Clear();
    }
  }
  //---------------------------------------------------------------------------
  template <class T> void add(std::vector<T>& target, const std::vector<T>& source)
  {
    const int size = source.size();
    for (int i=0; i<size; ++i)
    {
      target.push_back(source[i]);
    }
  }
  //---------------------------------------------------------------------------
  void add(std::vector<std::string>& target, const std::vector<std::string>& source)
  {
    const int size = source.size();
    for (int i=0; i<size; ++i)
    {
      target.push_back(source[i]);
    }
  }
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------


};
#pragma package(smart_init)
