#pragma once

#include <Urho3D/Urho3D.h>
#include <Urho3D/Container/HashMap.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/UI/UI.h>
//#include <Urho3D/Physics/RigidBody.h>

namespace Urho3D {
class Drawable;
class Node;
class Scene;
class Sprite;
}

using namespace Urho3D;

class CameraMaster;
class InputMaster;

typedef struct GameWorld
{
    SharedPtr<CameraMaster> camera;
    SharedPtr<Scene> scene;
    SharedPtr<Node> backgroundNode;
    SharedPtr<Node> voidNode;
    struct {
        SharedPtr<Node> sceneCursor;
        SharedPtr<Cursor> uiCursor;
        PODVector<RayQueryResult> hitResults;
    } cursor;
} GameWorld;

typedef struct HitInfo
{
    Vector3 position_;
    Vector3 hitNormal_;
    Node* hitNode_;
    Drawable* drawable_;
} HitInfo;

namespace {
  StringHash const N_VOID = StringHash("Void");
  StringHash const N_CURSOR = StringHash("Cursor");
  StringHash const N_TILEPART = StringHash("TilePart");
  StringHash const N_SLOT = StringHash("Slot");
}

class MasterControl : public Application
{
    OBJECT(MasterControl);
    friend class InputMaster;

public:
    explicit MasterControl(Context* context);
    GameWorld world_;
    SharedPtr<ResourceCache> cache_;
    SharedPtr<Graphics> graphics_;


    /// Setup before engine initialization. Modifies the engine paramaters.
    virtual void Setup();
    /// Setup after engine initialization.
    virtual void Start();
    /// Cleanup after the main loop. Called by Application.
    virtual void Stop();
    void Exit();
private:
    SharedPtr<UI> ui_;
    SharedPtr<Renderer> renderer_;
    SharedPtr<XMLFile> defaultStyle_;

    /// Set custom window title and icon
    void SetWindowTitleAndIcon();
    /// Create console and debug HUD
    void CreateConsoleAndDebugHud();

    /// Construct the scene content.
    void CreateScene();
    /// Construct user interface elements.
    void CreateUI();
    /// Subscribe to application-wide logic update and post-render update events.
    void SubscribeToEvents();

    /// Handle scene update event to control camera's pitch and yaw.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post-render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    /// Create a mushroom object at position.
    void CreatePlatform(const Vector3 pos);
    void UpdateCursor(double timeStep);
    /// Utility function to raycast to the cursor position. Return true if hit.
    bool CursorRayCast(double maxDistance, PODVector<RayQueryResult> &hitResults);

    /// Pause flag
    //bool paused_;
};































