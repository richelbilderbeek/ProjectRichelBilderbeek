//---------------------------------------------------------------------------
/*
WtMysteryMachineWidget, Wt widget for displaying the MysteryMachine class
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
//From http://www.richelbilderbeek.nl/CppWtMysteryMachineWidget.htm
//---------------------------------------------------------------------------
#ifndef WTMYSTERYMACHINEWIDGET_H
#define WTMYSTERYMACHINEWIDGET_H

#include <iostream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/signals2.hpp>

#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#pragma GCC diagnostic pop
namespace Wt { struct WMouseEventEvent; }

namespace ribi {

struct MysteryMachineWidget;
struct WtToggleButtonWidget;

///WtMysteryMachineWidget displays a MysteryMachine
struct WtMysteryMachineWidget : public Wt::WPaintedWidget
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::box<Point> Rect;

  ///A WtMysteryMachineWidget is created by its width and height
  explicit WtMysteryMachineWidget(const int width, const int height);

  ///Obtain a read-only pointer to the MysteryMachine
  const MysteryMachineWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the MysteryMachine
  MysteryMachineWidget * GetWidget() { return m_widget.get(); }

  ///Signal that is emitted when a WtMysteryMachineWidget is toggled
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Obtain the WtMysteryMachineWidget its version
  static std::string GetVersion();

  ///Obtain the WtMysteryMachineWidget its version history
  static std::vector<std::string> GetVersionHistory();

  protected:
  ///Paint the WtMysteryMachineWidget
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:

  ///The MysteryMachine
  boost::scoped_ptr<MysteryMachineWidget> m_widget;

  ///Repaint the WtMysteryMachineWidget
  void DoRepaint();

  ///Respond to mouse click
  void OnClicked(const Wt::WMouseEvent& e);

  ///OnResize is called when the geometry of the widget is changed
  void OnResize();

  friend std::ostream& operator<<(std::ostream& os, const WtMysteryMachineWidget& widget);

  ///Wt resize: hide it from sight
  void resize(const Wt::WLength& width, const Wt::WLength& height);
};

std::ostream& operator<<(std::ostream& os, const WtMysteryMachineWidget& widget);

} //~namespace ribi

#endif // WTMYSTERYMACHINEWIDGET_H
