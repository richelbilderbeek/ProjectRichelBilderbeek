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

#include <Urho3D/Urho3D.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Graphics/Zone.h>

#include <Urho3D/DebugNew.h>

#include "urho3dtemplate.h"

DEFINE_APPLICATION_MAIN(Urho3DTemplate);

Urho3DTemplate::Urho3DTemplate(Context *context):
    Application(context),
    cameraYaw_(0.0f),
    cameraPitch_(0.0f),
    paused_(false)
{
}

void Urho3DTemplate::Setup()
{
    // Modify engine startup parameters.
    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs")+GetTypeName()+".log";
    engineParameters_["FullScreen"] = true;
    engineParameters_["Headless"] = true;
}

void Urho3DTemplate::Start()
{
    //Set custom window title and icon.
    SetWindowTitleAndIcon();
    //Create console and debug HUD.
    CreateConsoleAndDebugHud();
    //Subscribe key down event.
    SubscribeToEvent(E_KEYDOWN, HANDLER(Urho3DTemplate, HandleKeyDown));
    //Subscribe scene update event.
    //SubscribeToEvent(E_SCENEUPDATE, HANDLER(Urho3DTemplate, HandleSceneUpdate));

    //Create the scene content
    CreateScene();
    //Create the UI content
    CreateUI();
    //Setup the viewport for displaying the scene
    SetupViewport();
    //Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void Urho3DTemplate::Stop()
{
    engine_->DumpResources(true);
}

void Urho3DTemplate::SetWindowTitleAndIcon()
{
    //Get default style
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* xmlfile = cache->GetResource<XMLFile>("UI/DefaulStyle.xml");

    //Create console
    Console* console = engine_->CreateConsole();
    console->SetDefaultStyle(xmlfile);
    console->GetBackground()->SetOpacity(0.0f);

    //Create debug HUD
    DebugHud* debugHud = engine_->CreateDebugHud();
    debugHud->SetDefaultStyle(xmlfile);
}

void Urho3DTemplate::HandleKeyDown(String eventType, VariantMap &eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    //Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESC)
    {
        Console* console = GetSubsystem<Console>();
        if (console->IsVisible())
            console->SetVisible(false);
        else
            engine_->Exit();
    }
    //Toggle console with F1
    else if (key == KEY_F1)
        GetSubsystem<Console>()->Toggle();
    //Toggle debug HUD with F2
    else if (key == KEY_F2)
        GetSubsystem<DebugHud>()->ToggleAll();
    //Rendering quality controls, only when UI has no focused element
    else if (!GetSubsystem<UI>()->GetFocusElement())
    {
        Renderer* renderer = GetSubsystem<Renderer>();

        /*// Preferences / Pause
        if (key == KEY_SELECT && touchEnabled_)
        {
            paused_ = !paused_;

            Input* input = GetSubsystem<Input>();
            if (screenJoystickSettingsIndex_ == M_MAX_UNSIGNED)
            {
                // Lazy initialization
                ResourceCache* cache = GetSubsystem<ResourceCache>();
                screenJoystickSettingsIndex_ = input->AddScreenJoystick(cache->GetResource<XMLFile>("UI/ScreenJoystickSettings_Samples.xml"), cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
            }
            else
                input->SetScreenJoystickVisible(screenJoystickSettingsIndex_, paused_);
        }*/

        //Texture quality
        /*else*/ if (key == '1')
        {
            int quality = renderer->GetTextureQuality();
            ++quality;
            if (quality>QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer->SetTextureQuality(quality);
        }

        //Material quality
        else if (key == '2')
        {
            int quality = renderer->GetMaterialQuality();
            ++quality;
            if (quality>QUALITY_HIGH)
                quality = QUALITY_LOW;
            renderer->SetMaterialQuality(quality);
        }

        //Specular lighting
        else if (key == '3')
            renderer->SetSpecularLighting(!renderer->GetSpecularLighting());
        //Shadow rendering
        else if (key == '4')
            renderer->SetDrawShadows(!renderer->GetDrawShadows());
        //Shadow map resolution
        else if (key == '5')
        {
            int shadowMapSize = renderer->GetShadowMapSize();
            shadowMapSize *= 2;
            if (shadowMapSize > 4096)
                shadowMapSize = 512;
            renderer->SetShadowMapSize(shadowMapSize);
        }
        //Shadow depth and filtering quality
        else if (key == '6')
        {
            int quality = renderer->GetShadowQuality();
            ++quality;
            if (quality > SHADOWQUALITY_HIGH_24BIT)
                quality = SHADOWQUALITY_LOW_16BIT;
            renderer->SetShadowQuality(quality);
        }
        //Occlusion culling
        else if (key == '7')
        {
            bool occlusion = renderer->GetMaxOccluderTriangles() > 0;
            occlusion = !occlusion;
            renderer->SetMaxOccluderTriangles(occlusion ? 5000 : 0);
        }
        //Instancing
        else if (key == '8')
            renderer->SetDynamicInstancing(!renderer->GetDynamicInstancing());
        //Take screenshot
        else if (key == '9')
        {
            Graphics* graphics = GetSubsystem<Graphics>();
            Image screenshot(context_);
            graphics->TakeScreenShot(screenshot);
            //Here we save in the Data folder with date and time appended
            screenshot.SavePNG(GetSubsystem<FileSystem>()->GetProgramDir() + "Screenshots/Screenshot_" + Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_')+".png");
        }
    }
}

/*void Urho3DTemplate::HandleSceneUpdate(StringHash eventType, VariantMap &eventData)
{
}*/

void Urho3DTemplate::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);

    //Create octree, use default volume (-1000, -1000, -1000) to (1000,1000,1000)
    //Also create a DebugRenderer component so that we can draw debug geometry
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();

    //Create scene node & StaticModel component for showing a static plane
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    //Create a Zone component for ambient lighting & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);

    //Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));

    //Set cascade splits at 10, 50, 200 world unitys, fade shadows at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    //Create some mushrooms
    const unsigned NUM_MUSHROOMS = 100;
    for (unsigned i = 0; i < NUM_MUSHROOMS; ++i)
        CreateMushroom(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));

    //Create randomly sized boxes. If boxes are big enough make them occluders
    const unsigned NUM_BOXES = 20;
    for (unsigned i = 0; i <NUM_BOXES; ++i)
    {
        Node* boxNode = scene_->CreateChild("Box");
        float size = 1.0f + Random(10.0f);
        boxNode->SetPosition(Vector3(Random(80.0f) - 40.0f, size * 0.5f, Random(80.0f) - 40.0f));
        boxNode->SetScale(size);
        StaticModel* boxObject = boxNode->CreateComponent<StaticModel>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        boxObject->SetCastShadows(true);
        if (size >= 3.0f)
            boxObject->SetOccluder(true);
    }

    //Create Jack node that will follow the path
    jackNode_ = scene_->CreateChild("Jack");
    jackNode_->SetPosition(Vector3(-5.0f, 0.0f, 20.0f));
    AnimatedModel* modelObject = jackNode_->CreateComponent<AnimatedModel>();
    modelObject->SetModel(cache->GetResource<Model>("Model/Jack.mdl"));
    modelObject->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    modelObject->SetCastShadows(true);

    //Create the camera. Limit far clip distance to match the fog
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);

    //Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
}

void Urho3DTemplate::CreateUI()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    //Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will control the camera, and when visible it will point the raycast target
    XMLFile* style = cache->GetResource<XMLFile>("UI/Defaultstyle.xml");
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto(style);
    ui->SetCursor(cursor);

    //Set starting position of the cursor at the rendering window center
    Graphics* graphics = GetSubsystem<Graphics>();
    cursor->SetPosition(graphics->GetWidth()/2, graphics->GetHeight()/2);

    //Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
                "Lorum ipsum, dolor set amet"
                );
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    //The text has multiple rows. Center them in relation to each other
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight()/4);
}

void Urho3DTemplate::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    //Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void Urho3DTemplate::SubscribeToEvents()
{
    //Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Urho3DTemplate, HandleUpdate));

    //Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request debug geometry
    //SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(Urho3DTemplate, HandlePostRenderUpdate));
}

void Urho3DTemplate::MoveCamera(float timeStep)
{
    //Right mouse button controls mouse cursor visibility: hide when pressed
    UI* ui = GetSubsystem<UI>();
    Input* input = GetSubsystem<Input>();
    ui->GetCursor()->SetVisible(!input->GetMouseButtonDown(MOUSEB_RIGHT));

    //Do not move if the UI has a focused element (the console)
    if (ui->GetFocusElement())
        return;

    //Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    //Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    //Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees. Only move the camera when the cursor is hidden.
    if (!ui->GetCursor()->IsVisible())
    {
        IntVector2 mouseMove = input->GetMouseMove();
        cameraYaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        cameraPitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        cameraPitch_ = Clamp(cameraPitch_, -90.0f, 90.0f);

        //Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
        cameraNode_->SetRotation(Quaternion(cameraPitch_, cameraYaw_, 0.0f));
    }

    //Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown('W'))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);

    //Add or remove objects with left mouse button
    if (input->GetMouseButtonPress(MOUSEB_LEFT))
        AddOrRemoveObject();
}

void Urho3DTemplate::AddOrRemoveObject()
{
    //Raycast and check if we hit a mushroom node. If yes, remove it, if no create a new one
    Vector3 hitPos;
    Drawable* hitDrawable;

    if (RayCast(250.0f, hitPos, hitDrawable))
    {
        Node* hitNode = hitDrawable->GetNode();
        if (hitNode->GetName() == "Mushroom")
        {
            hitNode->Remove();
        }
        else
        {
            CreateMushroom(hitPos);
        }
    }
}

Node* Urho3DTemplate::CreateMushroom(const Vector3 &pos)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Node* mushroomNode = scene_->CreateChild("Mushroom");
    mushroomNode->SetPosition(pos);
    mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
    mushroomNode->SetScale(2.0f + Random(0.5f));
    StaticModel* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
    mushroomObject->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
    mushroomObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
    mushroomObject->SetCastShadows(true);

    return mushroomNode;
}

bool Urho3DTemplate::RayCast(float maxDistance, Vector3 &hitPos, Drawable *&hitDrawable)
{
    hitDrawable = 0;

    UI* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    //Check the cursor is visible and there is no UI element in front of the cursor
    if (!ui->GetCursor()->IsVisible() || ui->GetElementAt(pos, true))
        return false;

    Graphics* graphics = GetSubsystem<Graphics>();
    Camera* camera = cameraNode_->GetComponent<Camera>();
    Ray cameraRay = camera->GetScreenRay((float)pos.x_/graphics->GetWidth(), (float)pos.y_/graphics->GetHeight());
    //Pick only geometry objects, not eg zones or lights, only get the first (closest) hit
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY);
    scene_->GetComponent<Octree>()->RaycastSingle(query);
    if (results.Size())
    {
        RayQueryResult& result = results[0];
        hitPos = result.position_;
        hitDrawable = result.drawable_;
        return true;
    }

    return false;
}

void Urho3DTemplate::HandleUpdate(StringHash eventType, VariantMap &eventData)
{
    using namespace Update;

    //Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    //Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

/*void Urho3DTemplate::HandlePostRenderUpdate(StringHash eventType, VariantMap &eventData)
{
}*/







































