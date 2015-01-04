//---------------------------------------------------------------------------
/*
MysteryMachine, my mystery machine class
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
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct DialWidget;
struct LedWidget;
struct TextCanvas;
struct ToggleButtonWidget;

///MysteryMachine contains the logic behind my Mystery Machine
struct MysteryMachine
{
  MysteryMachine() noexcept;
  MysteryMachine(const MysteryMachine&) = delete;
  MysteryMachine& operator=(const MysteryMachine&) = delete;

  const boost::shared_ptr<DialWidget> GetDialBack() noexcept { return m_dial_back; }
  const boost::shared_ptr<DialWidget> GetDialFront() noexcept { return m_dial_front; }
  const boost::shared_ptr<LedWidget> GetLedBack1() noexcept { return m_led_back_1; }
  const boost::shared_ptr<LedWidget> GetLedBack2() noexcept { return m_led_back_2; }
  const boost::shared_ptr<LedWidget> GetLedBack3() noexcept { return m_led_back_3; }
  const boost::shared_ptr<LedWidget> GetLedFront1() noexcept { return m_led_front_1; }
  const boost::shared_ptr<LedWidget> GetLedFront2() noexcept { return m_led_front_2; }
  const boost::shared_ptr<LedWidget> GetLedFront3() noexcept { return m_led_front_3; }
  const boost::shared_ptr<LedWidget> GetLedTopFront() noexcept { return m_led_top_front;  }
  const boost::shared_ptr<LedWidget> GetLedTopMiddle() noexcept { return m_led_top_middle; }
  const boost::shared_ptr<LedWidget> GetLedTopBack() noexcept { return m_led_top_back;   }
  const boost::shared_ptr<ToggleButtonWidget> GetToggleButton() noexcept { return m_toggle_button; }


  const boost::shared_ptr<const DialWidget> GetDialBack() const noexcept { return m_dial_back; }
  const boost::shared_ptr<const DialWidget> GetDialFront() const noexcept { return m_dial_front; }
  const boost::shared_ptr<const LedWidget> GetLedBack1() const noexcept { return m_led_back_1; }
  const boost::shared_ptr<const LedWidget> GetLedBack2() const noexcept { return m_led_back_2; }
  const boost::shared_ptr<const LedWidget> GetLedBack3() const noexcept { return m_led_back_3; }
  const boost::shared_ptr<const LedWidget> GetLedFront1() const noexcept { return m_led_front_1; }
  const boost::shared_ptr<const LedWidget> GetLedFront2() const noexcept { return m_led_front_2; }
  const boost::shared_ptr<const LedWidget> GetLedFront3() const noexcept { return m_led_front_3; }
  const boost::shared_ptr<const LedWidget> GetLedTopFront() const noexcept  { return m_led_top_front;  }
  const boost::shared_ptr<const LedWidget> GetLedTopMiddle() const noexcept { return m_led_top_middle; }
  const boost::shared_ptr<const LedWidget> GetLedTopBack() const noexcept   { return m_led_top_back;   }
  const boost::shared_ptr<const ToggleButtonWidget> GetToggleButton() const noexcept { return m_toggle_button; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;


  ///Convert the MysteryMachine to a TextCanvas
  /*

+--------------------------------------------------------+
|  ***     ***     ***     ____                          |
|** | ** **hhh** **MMM**  |    |           ***           |
|*  |  * *hhhhh* *MMMMM*  |____|         **MMM**         |
|*  |  * *hhhhh* *MMMMM*  |____|         *MMMMM*         |
|*     * *hhhhh* *MMMMM*                 *MMMMM*         |
| *   *    ***    *MMM*    ***           *MMMMM*         |
|  ***   **MMM**   ***   **MMM**           ***           |
|        *MMMMM*         *MMMMM*         **MMM**         |
|        *MMMMM*         *MMMMM*         *MMMMM*         |
|        *MMMMM*         *MMMMM*         *MMMMM*         |
|          ***            *MMM*    ***   *MMMMM*         |
|        **MMM**           ***   **MMM**   ***     ***   |
|        *MMMMM*                 *MMMMM* **hhh** ** | ** |
|        *MMMMM*                 *MMMMM* *hhhhh* *  |  * |
|        *MMMMM*                 *MMMMM* *hhhhh* *  |  * |
|         *MMM*                   *MMM*  *hhhhh* *     * |
|          ***                     ***    *hhh*   *   *  |
|                                          ***     ***   |
+--------------------------------------------------------+

  */
  const boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  private:
  virtual ~MysteryMachine() noexcept {}
  friend void boost::checked_delete<>(MysteryMachine*);

  boost::shared_ptr<DialWidget> m_dial_back;
  boost::shared_ptr<DialWidget> m_dial_front;
  boost::shared_ptr<LedWidget> m_led_front_1;
  boost::shared_ptr<LedWidget> m_led_front_2;
  boost::shared_ptr<LedWidget> m_led_front_3;
  boost::shared_ptr<LedWidget> m_led_back_1;
  boost::shared_ptr<LedWidget> m_led_back_2;
  boost::shared_ptr<LedWidget> m_led_back_3;
  boost::shared_ptr<LedWidget> m_led_top_front;
  boost::shared_ptr<LedWidget> m_led_top_middle;
  boost::shared_ptr<LedWidget> m_led_top_back;
  boost::shared_ptr<ToggleButtonWidget> m_toggle_button;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void Update() noexcept;

  friend std::ostream& operator<<(std::ostream& os, const MysteryMachine& machine) noexcept;

};

std::ostream& operator<<(std::ostream& os, const MysteryMachine& machine) noexcept;

} //~namespace ribi

#endif // MYSTERYMACHINE_H
