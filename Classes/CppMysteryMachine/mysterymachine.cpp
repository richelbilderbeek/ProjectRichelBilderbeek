//---------------------------------------------------------------------------
/*
MysteryMachine, my mystery machine class
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
//From http://www.richelbilderbeek.nl/CppMysteryMachine.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "mysterymachine.h"

#include <boost/lexical_cast.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "textcanvas.h"
#include "testtimer.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::MysteryMachine::MysteryMachine() noexcept
  : m_dial_back(new DialWidget),
    m_dial_front(new DialWidget),
    m_led_front_1(new LedWidget(0,0,32,32,1.0,255,  0,  0)),
    m_led_front_2(new LedWidget(0,0,32,32,0.0,  0,255,  0)),
    m_led_front_3(new LedWidget(0,0,32,32,0.0,  0,  0,255)),
    m_led_back_1(new LedWidget(0,0,32,32,1.0,255,  0,  0)),
    m_led_back_2(new LedWidget(0,0,32,32,0.0,  0,255,  0)),
    m_led_back_3(new LedWidget(0,0,32,32,0.0,  0,  0,255)),
    m_led_top_front( new LedWidget(0,0,32,32,0.0,255,0,0)),
    m_led_top_middle(new LedWidget(0,0,32,32,0.0,255,0,0)),
    m_led_top_back(  new LedWidget(0,0,32,32,0.0,255,0,0)),
    m_toggle_button(new ToggleButtonWidget)
{
  #ifndef NDEBUG
  Test();
  #endif
  m_dial_back->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::MysteryMachine::Update,this));
  m_dial_front->GetDial()->m_signal_position_changed.connect(boost::bind(
    &ribi::MysteryMachine::Update,this));
  m_toggle_button->GetToggleButton()->m_signal_toggled.connect(boost::bind(
    &ribi::MysteryMachine::Update,this));
  Update();
}

std::string ribi::MysteryMachine::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::MysteryMachine::GetVersionHistory() noexcept
{
  return {
    "2011-04-10: Version 1.0: initial version",
    "2011-08-20: Version 1.1: added operator<<",
    "2014-02-28: Version 1.2: added ToTextCanvas",
  };
}

#ifndef NDEBUG
void ribi::MysteryMachine::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  MysteryMachine m;
  assert(!m.GetVersion().empty());
}
#endif

const boost::shared_ptr<ribi::TextCanvas> ribi::MysteryMachine::ToTextCanvas() const noexcept
{
  const int w = 58;
  const int h = 20;
  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(w,h)
  };
  //Create the edges
  {
    canvas->PutText(0,0,std::string(w,'-'));
    canvas->PutText(0,h - 1,std::string(w,'-'));
    for (int y=0; y!=h; ++y)
    {
      canvas->PutChar(0,y,'|');
      canvas->PutChar(w-1,y,'|');
    }
    canvas->PutChar(  0,0  ,'+');
    canvas->PutChar(  0,h-1,'+');
    canvas->PutChar(w-1,0  ,'+');
    canvas->PutChar(w-1,h-1,'+');
  }
  //Put front at left
  canvas->PutCanvas(1,1,m_dial_front->ToTextCanvas(3));
  canvas->PutCanvas(49,12,m_dial_back->ToTextCanvas(3));

  canvas->PutCanvas(9,1,m_led_front_1->ToCanvas(3));
  canvas->PutCanvas(9,6,m_led_front_2->ToCanvas(3));
  canvas->PutCanvas(9,11,m_led_front_3->ToCanvas(3));

  canvas->PutCanvas(17,1,m_led_top_front->ToCanvas(3));
  canvas->PutCanvas(25,6,m_led_top_middle->ToCanvas(3));
  canvas->PutCanvas(33,11,m_led_top_back->ToCanvas(3));

  canvas->PutCanvas(41,2,m_led_back_3->ToCanvas(3));
  canvas->PutCanvas(41,7,m_led_back_2->ToCanvas(3));
  canvas->PutCanvas(41,12,m_led_back_1->ToCanvas(3));

  canvas->PutCanvas(26,1,m_toggle_button->ToTextCanvas(6,4));
  return canvas;
}


void ribi::MysteryMachine::Update() noexcept
{
  const int back = static_cast<int>(GetDialBack()->GetDial()->GetPosition() * 12.0) % 3;
  const int front = static_cast<int>(GetDialFront()->GetDial()->GetPosition() * 12.0) % 3;
  int top = (GetToggleButton()->GetToggleButton()->IsPressed()
    ? (1 + front - back + 3) % 3
    : -1);
  assert(front >= 0);
  assert(front  < 3);
  assert(back >= 0);
  assert(back  < 3);
  assert(top >= -1); //-1 denotes off
  assert(top  < 3);
  m_led_front_1->GetLed()->SetIntensity(front == 0 ? 1.0 : 0.0);
  m_led_front_2->GetLed()->SetIntensity(front == 1 ? 1.0 : 0.0);
  m_led_front_3->GetLed()->SetIntensity(front == 2 ? 1.0 : 0.0);
  m_led_back_1->GetLed()->SetIntensity(back == 0 ? 1.0 : 0.0);
  m_led_back_2->GetLed()->SetIntensity(back == 1 ? 1.0 : 0.0);
  m_led_back_3->GetLed()->SetIntensity(back == 2 ? 1.0 : 0.0);
  m_led_top_front->GetLed()->SetIntensity( top == 0 ? 1.0 : 0.0);
  m_led_top_middle->GetLed()->SetIntensity(top == 1 ? 1.0 : 0.0);
  m_led_top_back->GetLed()->SetIntensity(  top == 2 ? 1.0 : 0.0);
}

std::ostream& ribi::operator<<(std::ostream& os, const MysteryMachine& machine) noexcept
{
  os
    << "<MysteryMachine>"
    << "<dial_back>"
      << *machine.m_dial_back
    << "</dial_back>"
    << "<dial_front>"
      << *machine.m_dial_front
    << "</dial_front>"
    << "<led_back_1>"
      << *machine.m_led_back_1
    << "</led_back_1>"
    << "<led_back_2>"
      << *machine.m_led_back_2
    << "</led_back_2>"
    << "<led_back_3>"
      << *machine.m_led_back_3
    << "</led_back_3>"
    << "<led_front_1>"
    << *machine.m_led_front_1
    << "</led_front_1>"
    << "<led_front_2>"
      << *machine.m_led_front_2
    << "</led_front_2>"
    << "<led_front_3>"
      << *machine.m_led_front_3
    << "<led_front_3>"
    << "<led_top_back>"
      << *machine.m_led_top_back
    << "</led_top_back>"
    << "<led_top_front>"
      << *machine.m_led_top_front
    << "</led_top_front>"
    << "<led_top_middle>"
      << *machine.m_led_top_middle
    << "</led_top_middle>"
    << "<toggle_button>"
    << *machine.m_toggle_button
    << "</toggle_button>"
    << "</MysteryMachine>";
  return os;
}

