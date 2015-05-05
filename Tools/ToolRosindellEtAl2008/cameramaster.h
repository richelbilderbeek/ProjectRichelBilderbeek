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

#include "mastercontrol.h"

namespace Urho3D {
  class Drawable;
  class Node;
  class Scene;
  class Sprite;
  class Viewport;
  class RenderPath;
  class RigidBody;
  class Camera;
}

using namespace Urho3D;

class CameraMaster : public Object
{
    OBJECT(CameraMaster);
    friend class MasterControl;
    friend class InputMaster;
public:
    CameraMaster(Context *context, MasterControl* masterControl);

    virtual void Start();
    virtual void Stop();

    SharedPtr<Camera> camera_;
    SharedPtr<Viewport> viewport_;
    SharedPtr<RenderPath> effectRenderPath;

    Vector3 GetWorldPosition();
    Quaternion GetRotation();
private:
    MasterControl * const masterControl_;
    void HandleSceneUpdate(StringHash eventType, VariantMap &eventData);
    SharedPtr<Node> translationNode_;
    SharedPtr<Node> rotationNode_;

    SharedPtr<RigidBody> rigidBody_;
    double yaw_ = 0.0;
    double pitch_ = 0.0;
    //double roll_ = 0.0;
    double yawDelta_ = 0.0;
    double pitchDelta_ = 0.0;
    double forceMultiplier = 1.0;
    void SetupViewport();
};
