//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

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
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//
//Music used: Macroform, song 'Dreaming',
//from https://www.jamendo.com/en/list/a142918/meditations
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#define BT_INFINITY
#include <Urho3D/Urho3D.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/IO/FileSystem.h>
#pragma GCC diagnostic pop

#include "inputmaster.h"
#include "cameramaster.h"

InputMaster::InputMaster(
  Context * const context,
  MasterControl * const masterControl
)
  : Object(context),
    masterControl_{masterControl}
{
  SubscribeToEvent(E_MOUSEBUTTONDOWN, HANDLER(InputMaster, HandleMouseDown));
  SubscribeToEvent(E_KEYDOWN, HANDLER(InputMaster, HandleKeyDown));
}

void InputMaster::HandleMouseDown(
  StringHash /* eventType */, VariantMap & /* eventData */)
{
    using namespace MouseButtonDown;
    //int button = eventData[P_BUTTON].GetInt();
}


void InputMaster::HandleMouseUp(
  StringHash /* eventType */, VariantMap &eventData)
{
    using namespace MouseButtonUp;
    int button = eventData[P_BUTTON].GetInt();
    if (button == MOUSEB_LEFT) {}//Deselect when mouse did not move during click on N_VOID
}

void InputMaster::HandleKeyDown(
  StringHash /* eventType */, VariantMap &eventData)
{
  using namespace KeyDown;
  const int key = eventData[P_KEY].GetInt();

  //Exit when ESC is pressed
  if (key == KEY_ESC)
  {
    masterControl_->Exit();
  }

  //Take screenshot
  if (key == KEY_9)
  {
    Graphics * const graphics{GetSubsystem<Graphics>()};
    Image screenshot(context_);
    graphics->TakeScreenShot(screenshot);
    //Here we save in the Data folder with date and time appended
    const String fileName{"screenshot.png"};
    //Log::Write(1, fileName);
    screenshot.SavePNG(fileName);
  }
}
