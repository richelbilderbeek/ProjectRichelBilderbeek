
/*
MysteryMachine, my mystery machine class
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

//From http://www.richelbilderbeek.nl/CppMysteryMachine.htm

#ifndef MYSTERYMACHINE_H
#define MYSTERYMACHINE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
  #include <boost/checked_delete.hpp>
  #include <boost/scoped_ptr.hpp>
  #include <boost/noncopyable.hpp>
  #include <boost/signals2.hpp>
#pragma GCC diagnostic pop

struct DialWidget;
struct LedWidget;
struct ToggleButtonWidget;

///MysteryMachine contains the logic behind my Mystery Machine
struct MysteryMachine : public boost::noncopyable
{
  MysteryMachine();

  DialWidget * GetDialBack() { return m_dial_back.get(); }
  DialWidget * GetDialFront() { return m_dial_front.get(); }
  LedWidget * GetLedBack1() { return m_led_back_1.get(); }
  LedWidget * GetLedBack2() { return m_led_back_2.get(); }
  LedWidget * GetLedBack3() { return m_led_back_3.get(); }
  LedWidget * GetLedFront1() { return m_led_front_1.get(); }
  LedWidget * GetLedFront2() { return m_led_front_2.get(); }
  LedWidget * GetLedFront3() { return m_led_front_3.get(); }
  LedWidget * GetLedTopFront() { return m_led_top_front.get();  }
  LedWidget * GetLedTopMiddle() { return m_led_top_middle.get(); }
  LedWidget * GetLedTopBack() { return m_led_top_back.get();   }
  ToggleButtonWidget * GetToggleButton() { return m_toggle_button.get(); }


  const DialWidget * GetDialBack() const { return m_dial_back.get(); }
  const DialWidget * GetDialFront() const { return m_dial_front.get(); }
  const LedWidget * GetLedBack1() const { return m_led_back_1.get(); }
  const LedWidget * GetLedBack2() const { return m_led_back_2.get(); }
  const LedWidget * GetLedBack3() const { return m_led_back_3.get(); }
  const LedWidget * GetLedFront1() const { return m_led_front_1.get(); }
  const LedWidget * GetLedFront2() const { return m_led_front_2.get(); }
  const LedWidget * GetLedFront3() const { return m_led_front_3.get(); }
  const LedWidget * GetLedTopFront() const  { return m_led_top_front.get();  }
  const LedWidget * GetLedTopMiddle() const { return m_led_top_middle.get(); }
  const LedWidget * GetLedTopBack() const   { return m_led_top_back.get();   }
  const ToggleButtonWidget * GetToggleButton() const { return m_toggle_button.get(); }

  private:
  ///MysteryMachine can only be deleted by Boost smart pointers
  virtual ~MysteryMachine() {}
  ///MysteryMachine can only be deleted by Boost smart pointers
  friend void boost::checked_delete<>(MysteryMachine*);

  boost::scoped_ptr<DialWidget> m_dial_back;
  boost::scoped_ptr<DialWidget> m_dial_front;
  boost::scoped_ptr<LedWidget> m_led_front_1;
  boost::scoped_ptr<LedWidget> m_led_front_2;
  boost::scoped_ptr<LedWidget> m_led_front_3;
  boost::scoped_ptr<LedWidget> m_led_back_1;
  boost::scoped_ptr<LedWidget> m_led_back_2;
  boost::scoped_ptr<LedWidget> m_led_back_3;
  boost::scoped_ptr<LedWidget> m_led_top_front;
  boost::scoped_ptr<LedWidget> m_led_top_middle;
  boost::scoped_ptr<LedWidget> m_led_top_back;
  boost::scoped_ptr<ToggleButtonWidget> m_toggle_button;

  void Update();

  friend std::ostream& operator<<(std::ostream& os, const MysteryMachine& machine);

  public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

std::ostream& operator<<(std::ostream& os, const MysteryMachine& machine);

#endif // MYSTERYMACHINE_H
