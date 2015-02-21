//---------------------------------------------------------------------------
/*
FilterOperationer, performs filter operations on images
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
// From http://www.richelbilderbeek.nl/ToolFilterOperationer.htm
//---------------------------------------------------------------------------
#ifndef FILTEROPERATIONERMAINDIALOG_H
#define FILTEROPERATIONERMAINDIALOG_H

#include <iosfwd>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/fwd.hpp>

#include <QPixmap>
#include <QImage>
#pragma GCC diagnostic pop

namespace ribi {

struct FilterOperationerMainDialog
{
  static const QPixmap DoFilterOperation(
    const QPixmap& source,
    const boost::numeric::ublas::matrix<double>& filter); //y-x-ordered

  private:
  static double GetFilterOperationPixel(
    const std::vector<std::vector<int> >& source, //y-x-ordered
    const int sourceX,
    const int sourceY,
    const std::vector<std::vector<double> >& filter); //y-x-ordered


  static const std::vector<std::vector<int> > DoFilterOperation(
    const std::vector<std::vector<int> >& source, //y-x-ordered
    const std::vector<std::vector<double> >& filter); //y-x-ordered

  static const std::pair<double,double> GetFilterRange(const std::vector<std::vector<double> >& filter);

  //const std::vector<std::vector<int> > GetRescaledImage(
  //  const std::vector<std::vector<int> >& source);

  //const std::vector<std::vector<int> > GetRescaledImage(
  //  const std::vector<std::vector<int> >& source,
  //  const std::vector<std::vector<double> >& filter);

  //export template <class T>
  //const double GetAverage(const std::vector<std::vector<T> >& v);


  //From htpp://www.richelbilderbeek.nl/CppGetCumulativeHistogram.htm
  template <class T> const std::vector<T> GetCumulativeHistogram(const std::vector<T>& histogram);

  ///Y-X ordered
  static const std::vector<std::vector<int> > PixmapToVector(const QPixmap& pixmap);

  static const std::vector<std::vector<int> > ImageToVector(const QImage& image);

  ///Y-X ordered
  static const std::vector<std::vector<double> > MatrixToVector(const boost::numeric::ublas::matrix<double>& m);

  ///Y-X ordered
  static const QImage VectorToImage(const std::vector<std::vector<int> >& m);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif
