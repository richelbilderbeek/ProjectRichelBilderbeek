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
