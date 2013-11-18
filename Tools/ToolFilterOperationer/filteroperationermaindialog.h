//---------------------------------------------------------------------------
/*
FilterOperationer, performs filter operations on images
Copyright (C) 2008-2013  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolFilterOperationer.htm
//---------------------------------------------------------------------------
#ifndef FILTEROPERATIONERMAINDIALOG_H
#define FILTEROPERATIONERMAINDIALOG_H

#include <iosfwd>
#include <vector>

namespace ribi {

struct FilterOperationerMainDialog
{
  double GetFilterOperationPixel(
    const std::vector<std::vector<int> >& source, //y-x-ordered
    const int sourceX,
    const int sourceY,
    const std::vector<std::vector<double> >& filter); //y-x-ordered


  const std::vector<std::vector<int> > DoFilterOperation(
    const std::vector<std::vector<int> >& source, //y-x-ordered
    const std::vector<std::vector<double> >& filter); //y-x-ordered

  const std::pair<double,double> GetFilterRange(const std::vector<std::vector<double> >& filter);

  //const std::vector<std::vector<int> > GetRescaledImage(
  //  const std::vector<std::vector<int> >& source);

  //const std::vector<std::vector<int> > GetRescaledImage(
  //  const std::vector<std::vector<int> >& source,
  //  const std::vector<std::vector<double> >& filter);

  //export template <class T>
  //const double GetAverage(const std::vector<std::vector<T> >& v);


  //From htpp://www.richelbilderbeek.nl/CppGetCumulativeHistogram.htm
  template <class T> const std::vector<T> GetCumulativeHistogram(const std::vector<T>& histogram);
};

} //~namespace ribi

#endif
