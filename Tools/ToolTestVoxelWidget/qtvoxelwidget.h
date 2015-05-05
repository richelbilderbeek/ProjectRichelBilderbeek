//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef URHO3DTEMPLATE_H
#define URHO3DTEMPLATE_H

#pragma once

#include <Urho3D/Engine/Application.h>

namespace Urho3D {
class Drawable;
class Node;
class Scene;
class Sprite;
}

using namespace Urho3D;

class Urho3DTemplate : public Application
{
    /// Enable type information.
    OBJECT(Urho3DTemplate)

public:
    /// Constructor.
    Urho3DTemplate(Context* context);

    /// Setup before engine initialization. Modifies the engine paramaters.
    virtual void Setup();
    /// Setup after engine initialization.
    virtual void Start();
    /// Cleanup after the main loop. Called by Application.
    virtual void Stop();

protected:
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    /// Camera yaw angle.
    float cameraYaw_;
    /// Camera pitch angle.
    float cameraPitch_;

private:


    /// Set custom window title and icon.
    void SetWindowTitleAndIcon();
    /// Create console and debug HUD
    void CreateConsoleAndDebugHud();
    /// Handle key down event to provess key controls.
    void HandleKeyDown(String eventType, VariantMap& eventData);
    /// Handle scene update event to control camera's pitch and yaw.
    //void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Pause flag
    bool paused_;

    /// Construct the scene content.
    void CreateScene();
    /// Construct user interface elements.
    void CreateUI();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to application-wide logic update and post-render update events.
    void SubscribeToEvents();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Add or remove object.
    void AddOrRemoveObject();
    /// Create a mushroom object at position.
    Node* CreateMushroom(const Vector3& pos);
    /// Utility function to raycast to the cursor position. Return true if hit.
    bool RayCast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post-render update event.
    //void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    ///Jack scene node.
    SharedPtr<Node> jackNode_;
};

#endif // URHO3DTEMPLATE_H































