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
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Input/Input.h>

#pragma GCC diagnostic pop

#include "cameramaster.h"


Vector3 Scale(const Vector3& lhs, const Vector3& rhs)
{
  return Vector3(
    lhs.x_ * rhs.x_,
    lhs.y_ * rhs.y_,
    lhs.z_ * rhs.z_
  );
}

CameraMaster::CameraMaster(
  Context *context,
  MasterControl *masterControl
) :
    Object(context),
    masterControl_{masterControl}
{
  SubscribeToEvent(E_SCENEUPDATE, HANDLER(CameraMaster, HandleSceneUpdate));

  //Create the camera. Limit far clip distance to match the fog
  translationNode_ = masterControl_->world_.scene->CreateChild("CamTrans");
  rotationNode_ = translationNode_->CreateChild("CamRot");
  camera_ = rotationNode_->CreateComponent<Camera>();
  camera_->SetFarClip(1024.0f);
  //Set an initial position for the camera scene node above the origin
  //translationNode_->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
  translationNode_->SetPosition(Vector3(0.0, 3.0,-20.0));

  rotationNode_->SetRotation(Quaternion(0.0f, 90.0f, 0.0f));
  rigidBody_ = translationNode_->CreateComponent<RigidBody>();
  rigidBody_->SetAngularDamping(10.0f);
  CollisionShape* collisionShape = translationNode_->CreateComponent<CollisionShape>();
  collisionShape->SetSphere(0.1f);
  rigidBody_->SetMass(1.0f);

  Node* lightNode = translationNode_->CreateChild("DirectionalLight");
  lightNode->SetDirection(Vector3(0.0f, -1.0f, 0.0f));
  Light* light = lightNode->CreateComponent<Light>();
  light->SetLightType(LIGHT_POINT);
  light->SetBrightness(0.5f);
  light->SetColor(Color(0.7f, 0.9f, 0.6f));
  light->SetCastShadows(false);

  SetupViewport();
}



void CameraMaster::Start()
{
}

void CameraMaster::Stop()
{
}

void CameraMaster::SetupViewport()
{
  Renderer * const renderer = GetSubsystem<Renderer>();

  //Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
  SharedPtr<Viewport> viewport(new Viewport(context_, masterControl_->world_.scene, camera_));
  viewport_ = viewport;

  //Add anti-aliasing
  viewport_->SetRenderPath(effectRenderPath);
  renderer->SetViewport(0, viewport);
}

Vector3 CameraMaster::GetWorldPosition()
{
    return translationNode_->GetWorldPosition();
}

Quaternion CameraMaster::GetRotation()
{
    return rotationNode_->GetRotation();
}

void CameraMaster::HandleSceneUpdate(StringHash /* eventType */, VariantMap &eventData)
{
    using namespace Update;

    //Take the frame time step, which is stored as a double
    double timeStep = eventData[P_TIMESTEP].GetFloat();
    //Movement speed as world units per second
    const double MOVE_SPEED = 2000.0;
    //Mouse sensitivity as degrees per pixel
    const double MOUSE_SENSITIVITY = 0.1;

    //Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees. Only move the camera when the cursor is hidden.
    Input* input = GetSubsystem<Input>();
    IntVector2 mouseMove = input->GetMouseMove();
    yawDelta_ = 0.5*(yawDelta_ + MOUSE_SENSITIVITY * mouseMove.x_);
    pitchDelta_ = 0.5*(pitchDelta_ + MOUSE_SENSITIVITY * mouseMove.y_);
    yaw_ += yawDelta_;
    pitch_ += pitchDelta_;
    pitch_ = Clamp(pitch_, -89.0, 89.0);
    //Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    translationNode_->SetRotation(Quaternion(0.0f, 0.0f, 0.0f));
    rotationNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    //Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    Vector3 camForce = Vector3::ZERO;
    if (input->GetKeyDown('W')) camForce += Scale(rotationNode_->GetDirection(), Vector3(1.0f,0.0f,1.0f) ).Normalized();
    if (input->GetKeyDown('S')) camForce += Scale(rotationNode_->GetDirection(), Vector3(-1.0f,0.0f,-1.0f) ).Normalized();
    if (input->GetKeyDown('D')) camForce += Scale(rotationNode_->GetRight(), Vector3(1.0f,0.0f,1.0f) ).Normalized();
    if (input->GetKeyDown('A')) camForce += Scale(rotationNode_->GetRight(), Vector3(-1.0f,0.0f,-1.0f) ).Normalized();
    if (input->GetKeyDown('E')) camForce += Vector3::UP;
    if (input->GetKeyDown('Q') && translationNode_->GetPosition().y_ > 1.0f) camForce += Vector3::DOWN;
    camForce = camForce.Normalized() * MOVE_SPEED * timeStep;

    if ( forceMultiplier < 8.0 && (input->GetKeyDown(KEY_LSHIFT)||input->GetKeyDown(KEY_RSHIFT)) ){
        forceMultiplier += 0.23;
    } else forceMultiplier = pow(forceMultiplier, 0.75);
    rigidBody_->ApplyForce( (forceMultiplier * camForce) - (2.3f * rigidBody_->GetLinearVelocity()) );

    if (translationNode_->GetPosition().y_ < 1.0f)
    {
        translationNode_->SetPosition(Vector3(translationNode_->GetPosition().x_, 1.0f, translationNode_->GetPosition().z_));
        rigidBody_->SetLinearVelocity(Vector3(rigidBody_->GetLinearVelocity().x_, 0.0f, rigidBody_->GetLinearVelocity().z_));
    }
}

