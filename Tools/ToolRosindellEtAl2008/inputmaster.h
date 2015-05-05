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
#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#define BT_INFINITY
#include <Urho3D/Input/Input.h>
#pragma GCC diagnostic pop

#include "mastercontrol.h"

namespace Urho3D {
class Drawable;
class Node;
class Scene;
class Sprite;
}

using namespace Urho3D;

class InputMaster : public Object
{
  OBJECT(InputMaster);
public:
  InputMaster(
    Context * const context,
    MasterControl * const masterControl
  );

private:
  MasterControl * const masterControl_;
  void HandleMouseDown(StringHash eventType, VariantMap &eventData);
  void HandleKeyDown(StringHash eventType, VariantMap &eventData);
  void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};
