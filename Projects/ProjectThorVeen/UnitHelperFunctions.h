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
#ifndef UnitHelperFunctionsH
#define UnitHelperFunctionsH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
#include <Chart.hpp>
#include <ComCtrls.hpp>
class SimulationParameters;
/*
class Comctrls::TRichEdit;
class Chart::TChart;
class Teengine::TChartSeries;
*/
//---------------------------------------------------------------------------

namespace helper
{
  bool isInt(const std::string& s, int& rInt);
  bool isDouble(const std::string& s, double& rDouble);
  std::string itoa(const int& x);
  std::string ftoa(const double& x);
  void dot(const std::string& s);
  void dot(const char* s);
  void dot(const int& i);
  void log(std::vector<std::string> myLog, TRichEdit * richEdit);
  void plot(const std::vector<int>& values, TChartSeries* Series);
  void emptyChart(TChart * chart);
  template <class T> void add(std::vector<T>& target, const std::vector<T>& source);
  void add(std::vector<std::string>& target, const std::vector<std::string>& source);


  };

#endif
