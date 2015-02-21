//---------------------------------------------------------------------------
/*
QtMysteryMachineWidget, Qt widget for displaying the MysteryMachine class
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
//From http://www.richelbilderbeek.nl/CppQtMysteryMachineWidget.htm
//---------------------------------------------------------------------------
#ifndef QTMYSTERYMACHINEWIDGET_H
#define QTMYSTERYMACHINEWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include <QWidget>

#include "dial.h" //For MOC
#include "dialwidget.h" //For MOC
#include "led.h" //For MOC
#include "ledwidget.h" //For MOC
#include "mysterymachine.h" //For MOC
#include "mysterymachinewidget.h" //For MOC
#include "togglebutton.h" //For MOC
#include "togglebuttonwidget.h" //For MOC
#pragma GCC diagnostic pop

namespace ribi {

struct QtToggleButtonWidget;

///QtMysteryMachineWidget displays a MysteryMachine
struct QtMysteryMachineWidget : public QWidget
{
  Q_OBJECT

  public:

  explicit QtMysteryMachineWidget(QWidget *parent = 0);

  ///A QtMysteryMachineWidget is created by its width and height
  QtMysteryMachineWidget(const int width, const int height,
    QWidget *parent = 0);

  ///Obtain a read-only pointer to the MysteryMachine
  const MysteryMachineWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the MysteryMachine
  MysteryMachineWidget * GetWidget() { return m_widget.get(); }

  ///Signal that is emitted when a QtMysteryMachineWidget is toggled
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Obtain the QtMysteryMachineWidget its version
  static std::string GetVersion() noexcept;

  ///Obtain the QtMysteryMachineWidget its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  protected:
  ///Respond to mouse clicks
  void mousePressEvent(QMouseEvent *);

  ///Paint the QtMysteryMachineWidget
  void paintEvent(QPaintEvent *);

  ///Resize the QtMysteryMachineWidget
  void resizeEvent(QResizeEvent *);

  private:

  ///The MysteryMachine
  boost::scoped_ptr<MysteryMachineWidget> m_widget;

  ///Repaint the QtMysteryMachineWidget
  void DoRepaint();

  ///Respond to mouse click
  //void OnClicked(const Wt::WMouseEvent& e);
};

} //~namespace ribi

#endif // WTMYSTERYMACHINEWIDGET_H
