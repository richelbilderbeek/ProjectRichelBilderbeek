//---------------------------------------------------------------------------
/*
Rasper, Raspberry Pi GPIO web application controller
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRasper.htm
//---------------------------------------------------------------------------
#ifndef WTRASPERMAINDIALOG_H
#define WTRASPERMAINDIALOG_H

#include <vector>
#include <Wt/WContainerWidget>
#include "raspberrypigpiopin.h"

namespace Wt
{
  struct WPushButton;
  struct WMouseEvent;
}


namespace ribi {

struct IpAddress;

namespace ToolRasper {

///Rasper its main dialog
struct WtMainDialog : public Wt::WContainerWidget
{
  WtMainDialog();

  private:
  struct Ui
  {
    Ui();
    std::vector<Wt::WPushButton*> m_buttons;
  } ui;

  std::vector<rpi::gpio::Pin> m_pins;

  ///Respond to the user changing the name edit
  void OnClick(const int pin_number);

  //const std::set<int> pins { 3,5,7,8,10,11,12,13,15,16,18,19,21,22,23,24,26 };
  //void OnClick1()  { OnClick( 1); }
  //void OnClick2()  { OnClick( 2); }
  void OnClick3()  { OnClick( 3); }
  //void OnClick4()  { OnClick( 4); }
  void OnClick5()  { OnClick( 5); }
  //void OnClick6()  { OnClick( 6); }
  void OnClick7()  { OnClick( 7); }
  void OnClick8()  { OnClick( 8); }
  //void OnClick9()  { OnClick( 9); }
  void OnClick10() { OnClick(10); }
  void OnClick11() { OnClick(11); }
  void OnClick12() { OnClick(12); }
  void OnClick13() { OnClick(13); }
  //void OnClick14() { OnClick(14); }
  void OnClick15() { OnClick(15); }
  void OnClick16() { OnClick(16); }
  //void OnClick17() { OnClick(17); }
  void OnClick18() { OnClick(18); }
  void OnClick19() { OnClick(19); }
  //void OnClick20() { OnClick(20); }
  void OnClick21() { OnClick(21); }
  void OnClick22() { OnClick(22); }
  void OnClick23() { OnClick(23); }
  void OnClick24() { OnClick(24); }
  //void OnClick25() { OnClick(25); }
  void OnClick26() { OnClick(26); }

  static const std::vector<rpi::gpio::Pin> CreatePins();
};

} //~namespace ToolRasper
} //~namespace ribi


#endif // WTRASPERMAINDIALOG_H
