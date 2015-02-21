//---------------------------------------------------------------------------
/*
HistogramEqualizationer, tool to perform a histogram equalization
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
//From http://www.richelbilderbeek.nl/ToolHistogramEqualizationer.htm
//---------------------------------------------------------------------------
#ifndef TOOLHISTOGRAMEQUALIZATIONERMAINDIALOG_H
#define TOOLHISTOGRAMEQUALIZATIONERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <vector>
#include <QImage>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct HistogramEqualizationerMainDialog
{
  static QImage DoHistogramEqualization(const QImage& source) noexcept;

  private:
  //void ConvertToGrey(const TImage * const source, TImage * const target);
  static const std::vector<int> GetImageHistogram(const QImage& image) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

//From htpp://www.richelbilderbeek.nl/CppGetCumulativeHistogram.htm
template <class T> const std::vector<T> GetCumulativeHistogram(const std::vector<T>& histogram)
{
  std::vector<T> v(histogram.begin(),histogram.end() );
  const int size = v.size();
  for (int i=1; i!=size; ++i)
  {
    v[i] += v[i-1];
  }
  return v;
}

} //~namespace ribi


#endif
