//---------------------------------------------------------------------------
/*
Widget, GUI independent widget class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWidget.htm
//---------------------------------------------------------------------------
#ifndef WIDGET_H
#define WIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/make_shared.hpp>
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///GUI indepedent widget class, modeled after the Qt and Wt architure
struct Widget
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::box<Point> Rect;

  static Rect CreateRect(const double left, const double top, const double width, const double height) noexcept;

  double GetBottom() const noexcept;
  const Rect& GetGeometry() const noexcept { return m_geometry; }
  Rect& GetGeometry() noexcept { return m_geometry; }
  double GetHeight() const noexcept;
  double GetLeft() const noexcept;
  double GetRight() const noexcept;
  double GetTop() const noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  double GetWidth() const noexcept;

  ///Is the coordinat within the widget its rectangle?
  bool IsIn(const double x, const double y) const noexcept;

  ///SetGeometry resizes the Widget and emits an OnResize signal
  void SetGeometry(const Rect& geometry) noexcept;
  void SetGeometry(const double left, const double top, const double width, const double height) noexcept;

  ///Respond to a change in size
  mutable boost::signals2::signal<void ()> m_signal_geometry_changed;

  protected:
  virtual ~Widget() noexcept {}
  friend void boost::checked_delete<>(      Widget*);
  friend void boost::checked_delete<>(const Widget*);
  friend class boost::detail::sp_ms_deleter<      Widget>;
  friend class boost::detail::sp_ms_deleter<const Widget>;

  private:
  Rect m_geometry;
};

} //~namespace ribi

#endif // WIDGET_H
