
/*
Widget, GUI independent widget class
Copyright (C) 2011 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/CppWidget.htm

#ifndef WIDGET_H
#define WIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include "rectangle.h"

///GUI indepedent widget class, modeled after the Qt and Wt architure
struct Widget
{
  const Rect& GetGeometry() const { return m_geometry; }
  Rect& GetGeometry() { return m_geometry; }

  ///SetGeometry resizes the Widget and emits an OnResize signal
  void SetGeometry(const Rect& geometry);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Respond to a change in size
  mutable boost::signals2::signal<void ()> m_signal_geometry_changed;

  protected:
  virtual ~Widget() {}
  friend void boost::checked_delete<>(::Widget*);

  private:
  Rect m_geometry;
};

#endif // WIDGET_H
