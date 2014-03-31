//---------------------------------------------------------------------------
/*
MysteryMachineWidget, GUI independent widget for MysteryMachine
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
//From http://www.richelbilderbeek.nl/CppMysteryMachineWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "mysterymachinewidget.h"

#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "geometry.h"
#include "led.h"
#include "ledwidget.h"
#include "mysterymachine.h"
#include "rectangle.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::MysteryMachineWidget::MysteryMachineWidget(
  const Rect& geometry) noexcept
  : m_signal_changed{},
    m_machine(new MysteryMachine)

{
  #ifndef NDEBUG
  Test();
  #endif
  m_signal_geometry_changed.connect(boost::bind(
    &ribi::MysteryMachineWidget::OnResize,this));
  SetGeometry(geometry);
}

///Respond to the user clicking on the MysteryMachineWidget
void ribi::MysteryMachineWidget::Click(const int x, const int y) noexcept
{
  if (m_machine->GetDialBack()->IsClicked(x,y))
  {
    m_machine->GetDialBack()->Click(x,y);
    m_signal_changed();
  }
  if (m_machine->GetDialFront()->IsClicked(x,y))
  {
    m_machine->GetDialFront()->Click(x,y);
    m_signal_changed();
  }
  if (m_machine->GetToggleButton()->IsIn(x,y))
  {
    m_machine->GetToggleButton()->Click(x,y);
    m_signal_changed();
  }
}

ribi::Widget::Rect ribi::MysteryMachineWidget::CreateRect(
  const double left,
  const double top,
  const double width,
  const double height
) noexcept
{
  return Geometry().CreateRect(left,top,width,height);
}

std::string ribi::MysteryMachineWidget::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::MysteryMachineWidget::GetVersionHistory() noexcept
{
  return {
    "2011-07-03: version 1.0: initial version",
    "2011-08-20: Version 1.1: added operator<<",
    "2014-02-28: Version 1.2: added ToTextCanvas and KeyPress",
  };
}

void ribi::MysteryMachineWidget::PressKey(const MysteryMachineKey key) noexcept
{
  switch (key)
  {
    case MysteryMachineKey::back_clockwise:
    {
      const double f {
        GetMachine()->GetDialBack()->GetDial()->GetPosition()
        + (1.0 / 12.0)
      };
      GetMachine()->GetDialBack()->GetDial()->SetPosition(
        f >= 1.0 ? f - 1.0 : f
      );
      m_signal_changed();
    }
    break;
    case MysteryMachineKey::back_counter_clockwise:
    {
      const double f {
        GetMachine()->GetDialBack()->GetDial()->GetPosition()
        - (1.0 / 12.0)
      };
      GetMachine()->GetDialBack()->GetDial()->SetPosition(
        f < 0.0 ? f + 1.0 : f
      );
      m_signal_changed();
    }
    break;
    case MysteryMachineKey::front_clockwise:
    {
      const double f {
        GetMachine()->GetDialFront()->GetDial()->GetPosition()
        + (1.0 / 12.0)
      };
      GetMachine()->GetDialFront()->GetDial()->SetPosition(
        f >= 1.0 ? f - 1.0 : f
      );
      m_signal_changed();
    }
    break;
    case MysteryMachineKey::front_counter_clockwise:
    {
      const double f {
        GetMachine()->GetDialFront()->GetDial()->GetPosition()
        - (1.0 / 12.0)
      };
      GetMachine()->GetDialFront()->GetDial()->SetPosition(
        f < 0.0 ? f + 1.0 : f
      );
      m_signal_changed();
    }
    break;
    case MysteryMachineKey::toggle:
    {
      GetMachine()->GetToggleButton()->GetToggleButton()->Toggle();
      m_signal_changed();
    }
    break;
  }
}

void ribi::MysteryMachineWidget::OnResize() noexcept
{
  const double w = boost::numeric_cast<double>(GetWidth());
  const double h = boost::numeric_cast<double>(GetHeight());
  const double s = std::min(w/4.0,h/8.0);
  const double w8 = w / 8.0;

  m_machine->GetDialBack()->SetGeometry((w8 * 1.0) - (s * 0.5),0,s,s);
  m_machine->GetDialFront()->SetGeometry((w8 * 7.0) - (s * 0.5),h-s,s,s);
  m_machine->GetToggleButton()->SetGeometry(
    (w8 * 4.0) + (s * 0.5),
    (h * 0.5) - (s * 0.5),
    s,s
  );



  m_machine->GetLedBack1()->SetGeometry((w8 * 3.0) - (s * 0.5),0,s,s);
  m_machine->GetLedBack2()->SetGeometry((w8 * 5.0) - (s * 0.5),0,s,s);
  m_machine->GetLedBack3()->SetGeometry((w8 * 7.0) - (s * 0.5),0,s,s);

  m_machine->GetLedFront1()->SetGeometry((w8 * 1.0) - (s * 0.5),h-s,s,s);
  m_machine->GetLedFront2()->SetGeometry((w8 * 3.0) - (s * 0.5),h-s,s,s);
  m_machine->GetLedFront3()->SetGeometry((w8 * 5.0) - (s * 0.5),h-s,s,s);

  m_machine->GetLedTopFront()->SetGeometry(
    (w8 * 5.0) - (s * 0.5),
    (((h - (s * 0.5)) + (h * 0.5)) * 0.5) - (s * 0.5),
    s,s
  );
  m_machine->GetLedTopMiddle()->SetGeometry((w8 * 4.0) - (s * 0.5),
    (h * 0.5) - (s * 0.5),
    s,s
  );
  m_machine->GetLedTopBack()->SetGeometry((w8 * 3.0) - (s * 0.5),
    (((s * 0.5) + (h * 0.5)) * 0.5) - (s * 0.5),
    s,s
  );
  //m_signal_mysterymachine_changed();
}

#ifndef NDEBUG
void ribi::MysteryMachineWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::MysteryMachineWidget::Test");
  MysteryMachineWidget w;
  assert(!w.GetVersion().empty());
  TRACE("Finished ribi::MysteryMachineWidget::Test successfully");
}
#endif

boost::shared_ptr<ribi::TextCanvas> ribi::MysteryMachineWidget::ToTextCanvas() const noexcept
{
  return GetMachine()->ToTextCanvas();
}

std::ostream& ribi::operator<<(std::ostream& os, const MysteryMachineWidget& widget) noexcept
{
  os
    << "<MysteryMachineWidget>"
    //<< "<geometry>"
    //<< widget.GetGeometry()
    //<< "</geometry>"
    << "<machine>"
    << *widget.m_machine
    << "</machine>"
    << "</MysteryMachineWidget>";
  return os;
}

