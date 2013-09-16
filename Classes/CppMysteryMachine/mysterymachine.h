//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppMysteryMachine.htm
//---------------------------------------------------------------------------
#ifndef MYSTERYMACHINE_H
#define MYSTERYMACHINE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct DialWidget;
struct LedWidget;
struct ToggleButtonWidget;

///MysteryMachine contains the logic behind my Mystery Machine
struct MysteryMachine
{
  MysteryMachine() noexcept;
  MysteryMachine(const MysteryMachine&);
  MysteryMachine& operator=(const MysteryMachine&);

  DialWidget * GetDialBack() noexcept { return m_dial_back.get(); }
  DialWidget * GetDialFront() noexcept { return m_dial_front.get(); }
  LedWidget * GetLedBack1() noexcept { return m_led_back_1.get(); }
  LedWidget * GetLedBack2() noexcept { return m_led_back_2.get(); }
  LedWidget * GetLedBack3() noexcept { return m_led_back_3.get(); }
  LedWidget * GetLedFront1() noexcept { return m_led_front_1.get(); }
  LedWidget * GetLedFront2() noexcept { return m_led_front_2.get(); }
  LedWidget * GetLedFront3() noexcept { return m_led_front_3.get(); }
  LedWidget * GetLedTopFront() noexcept { return m_led_top_front.get();  }
  LedWidget * GetLedTopMiddle() noexcept { return m_led_top_middle.get(); }
  LedWidget * GetLedTopBack() noexcept { return m_led_top_back.get();   }
  ToggleButtonWidget * GetToggleButton() noexcept { return m_toggle_button.get(); }


  const DialWidget * GetDialBack() const noexcept { return m_dial_back.get(); }
  const DialWidget * GetDialFront() const noexcept { return m_dial_front.get(); }
  const LedWidget * GetLedBack1() const noexcept { return m_led_back_1.get(); }
  const LedWidget * GetLedBack2() const noexcept { return m_led_back_2.get(); }
  const LedWidget * GetLedBack3() const noexcept { return m_led_back_3.get(); }
  const LedWidget * GetLedFront1() const noexcept { return m_led_front_1.get(); }
  const LedWidget * GetLedFront2() const noexcept { return m_led_front_2.get(); }
  const LedWidget * GetLedFront3() const noexcept { return m_led_front_3.get(); }
  const LedWidget * GetLedTopFront() const noexcept  { return m_led_top_front.get();  }
  const LedWidget * GetLedTopMiddle() const noexcept { return m_led_top_middle.get(); }
  const LedWidget * GetLedTopBack() const noexcept   { return m_led_top_back.get();   }
  const ToggleButtonWidget * GetToggleButton() const noexcept { return m_toggle_button.get(); }

  private:
  virtual ~MysteryMachine() noexcept {}
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

  void Update() noexcept;

  friend std::ostream& operator<<(std::ostream& os, const MysteryMachine& machine) noexcept;

  public:
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

std::ostream& operator<<(std::ostream& os, const MysteryMachine& machine) noexcept;

} //~namespace ribi

#endif // MYSTERYMACHINE_H
