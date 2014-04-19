//---------------------------------------------------------------------------
/*
GaborFilterWidget, Widget for the GaborFilter class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppGaborFilterWidget.htm
//---------------------------------------------------------------------------
#ifndef GABORFILTERWIDGET_H
#define GABORFILTERWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#include "widget.h"
#pragma GCC diagnostic pop

namespace ribi {

struct GaborFilter;

///Widget for displaying a GaborFilter
struct GaborFilterWidget : public Widget
{
  GaborFilterWidget(
    const int x = 0,
    const int y = 0,
    const int width  = 128,
    const int height = 128,
    const double angle = 0.0,
    const double frequency = 16.0,
    const double sigma = 8.0
  );
  GaborFilterWidget(const GaborFilterWidget&) = delete;
  GaborFilterWidget& operator=(const GaborFilterWidget&) = delete;
  ~GaborFilterWidget() noexcept {}

  ///Obtain a read-only pointer to GaborFilter
  const GaborFilter * GetGaborFilter() const noexcept { return m_filter.get(); }

  ///Obtain a read-and-write pointer to GaborFilter
  GaborFilter * GetGaborFilter() noexcept { return m_filter.get(); }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///The GABORFILTER
  boost::scoped_ptr<GaborFilter> m_filter;

  friend std::ostream& operator<<(std::ostream& os, const GaborFilterWidget& widget) noexcept;
};

std::ostream& operator<<(std::ostream& os, const GaborFilterWidget& widget) noexcept;

} //~namespace ribi

#endif // GABORFILTERWIDGET_H
