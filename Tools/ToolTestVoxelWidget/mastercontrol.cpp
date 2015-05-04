//Music from https://www.jamendo.com/en/list/a142918/meditations

#include <vector>

#include <QFile>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#define BT_INFINITY

#include <Urho3D/Urho3D.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/DebugNew.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Resource/Resource.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource.h>

#include <Urho3D/IO/Log.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/OctreeQuery.h>

#pragma GCC diagnostic pop

#include "mastercontrol.h"
#include "oneirocam.h"
#include "inputmaster.h"

DEFINE_APPLICATION_MAIN(MasterControl);

MasterControl::MasterControl(Context *context):
    Application(context)
    //,
    //paused_(false)
{
  std::system("ln -s ../../Libraries/Urho3D/bin/Data");
  std::system("ln -s ../../Libraries/Urho3D/bin/CoreData");
}


void MasterControl::Setup()
{
    // Modify engine startup parameters.
    //Set custom window title and icon.
    engineParameters_["WindowTitle"] = "TestVoxelWidget";
    engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs")+"TestVoxelWidget.log";
    engineParameters_["FullScreen"] = false;
    engineParameters_["Headless"] = false;
    engineParameters_["WindowWidth"] = 1024;
    engineParameters_["WindowHeight"] = 600;
}
void MasterControl::Start()
{
    new InputMaster(context_, this);
    cache_ = GetSubsystem<ResourceCache>();
    graphics_ = GetSubsystem<Graphics>();
    renderer_ = GetSubsystem<Renderer>();

    // Get default style
    defaultStyle_ = cache_->GetResource<XMLFile>("UI/DefaultStyle.xml");
    SetWindowTitleAndIcon();
    //Create console and debug HUD.
    CreateConsoleAndDebugHud();
    //Create the scene content
    CreateScene();
    //Create the UI content
    CreateUI();
    //Hook up to the frame update and render post-update events
    SubscribeToEvents();


    for (const std::string& resource:
      {
        "MacroformDreaming.ogg"
      }
    )
    {
      if (!QFile::exists(resource.c_str()))
      {
        QFile f( (":/files/"+resource).c_str());
        f.copy(resource.c_str());
      }
      assert(QFile::exists(resource.c_str()));
    }

    Sound * const music = cache_->GetResource<Sound>("MacroformDreaming.ogg");
    music->SetLooped(true);
    Node * const musicNode = world_.scene->CreateChild("Music");
    SoundSource * const musicSource = musicNode->CreateComponent<SoundSource>();
    musicSource->SetSoundType(SOUND_MUSIC);
    musicSource->Play(music);
}
void MasterControl::Stop()
{
    engine_->DumpResources(true);
}

void MasterControl::SubscribeToEvents()
{
    //Subscribe scene update event.
    SubscribeToEvent(E_SCENEUPDATE, HANDLER(MasterControl, HandleSceneUpdate));
    //Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(MasterControl, HandleUpdate));
    //Subscribe scene update event.
    SubscribeToEvent(E_SCENEUPDATE, HANDLER(MasterControl, HandleSceneUpdate));
}

void MasterControl::SetWindowTitleAndIcon()
{
    //Create console
    Console* console = engine_->CreateConsole();
    console->SetDefaultStyle(defaultStyle_);
    console->GetBackground()->SetOpacity(0.0f);

    //Create debug HUD
    DebugHud* debugHud = engine_->CreateDebugHud();
    debugHud->SetDefaultStyle(defaultStyle_);
}

void MasterControl::CreateConsoleAndDebugHud()
{
    // Create console
    Console* console = engine_->CreateConsole();
    console->SetDefaultStyle(defaultStyle_);
    console->GetBackground()->SetOpacity(0.8f);

    // Create debug HUD.
    DebugHud* debugHud = engine_->CreateDebugHud();
    debugHud->SetDefaultStyle(defaultStyle_);
}

void MasterControl::CreateUI()
{
    //ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    //Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will control the camera
    world_.cursor.uiCursor = new Cursor(context_);
    world_.cursor.uiCursor->SetVisible(false);
    ui->SetCursor(world_.cursor.uiCursor);

    //Set starting position of the cursor at the rendering window center
    world_.cursor.uiCursor->SetPosition(graphics_->GetWidth()/2, graphics_->GetHeight()/2);

    //Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
                "TestVoxelWidget"
                );
    //instructionText->SetFont(cache->GetResource<Font>("Resources/Fonts/Riau.ttf"), 32);
    //The text has multiple rows. Center them in relation to each other
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight()/2.1);
}

void MasterControl::CreateScene()
{
    world_.scene = new Scene(context_);

    //Create octree, use default volume (-1000, -1000, -1000) to (1000,1000,1000)
    /*Octree* octree = */world_.scene->CreateComponent<Octree>();
    //octree->SetSize(BoundingBox(Vector3(-10000, -100, -10000), Vector3(10000, 1000, 10000)), 1024);
    PhysicsWorld* physicsWorld = world_.scene->CreateComponent<PhysicsWorld>();
    physicsWorld->SetGravity(Vector3::ZERO);
    world_.scene->CreateComponent<DebugRenderer>();

    //Create cursor
    world_.cursor.sceneCursor = world_.scene->CreateChild("Cursor");
    world_.cursor.sceneCursor->SetPosition(Vector3(0.0f,0.0f,0.0f));
    StaticModel* cursorModel = world_.cursor.sceneCursor->CreateComponent<StaticModel>();
    cursorModel->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
    cursorModel->SetMaterial(cache_->GetResource<Material>("Materials/Jack.xml"));

    //Create an invisible plane for mouse raycasting
    world_.voidNode = world_.scene->CreateChild("Void");
    //Location is set in update since the plane moves with the camera.
    world_.voidNode->SetScale(Vector3(1000.0f, 1.0f, 1000.0f));
    StaticModel* planeModel = world_.voidNode->CreateComponent<StaticModel>();
    planeModel->SetModel(cache_->GetResource<Model>("Models/Plane.mdl"));
    planeModel->SetMaterial(cache_->GetResource<Material>("Materials/Jack.xml"));

    //Create background
    for (int i = -2; i <= 2; i++){
        for (int j = -2; j <= 2; j++){
            world_.backgroundNode = world_.scene->CreateChild("BackPlane");
            world_.backgroundNode->SetScale(Vector3(512.0f, 1.0f, 512.0f));
            world_.backgroundNode->SetPosition(Vector3(512.0f*i, -200.0f, 512.0f*j));
            StaticModel* backgroundObject = world_.backgroundNode->CreateComponent<StaticModel>();
            backgroundObject->SetModel(cache_->GetResource<Model>("Models/Plane.mdl"));
            //backgroundObject->SetMaterial(cache_->GetResource<Material>("Resources/Materials/dreamsky.xml"));
        }
    }
    //Create a Zone component for ambient lighting & fog control
    /*Node* zoneNode = world.scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(Vector3(-1000.0f, -10.0f, -1000.0f),Vector3(1000.0f, 20.0f, 1000.0f)));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.2f, 0.1f, 0.3f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(110.0f);*/

    //Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = world_.scene->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.0f, -1.0f, 0.0f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetBrightness(1.0f);
    light->SetColor(Color(1.0f, 0.8f, 0.7f));
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));

    //Create a second directional light without shadows
    Node* lightNode2 = world_.scene->CreateChild("DirectionalLight");
    lightNode2->SetDirection(Vector3(0.0f, 1.0f, 0.0f));
    Light* light2 = lightNode2->CreateComponent<Light>();
    light2->SetLightType(LIGHT_DIRECTIONAL);
    light2->SetBrightness(0.25f);
    light2->SetColor(Color(1.0f, 1.0f, 0.9f));
    light2->SetCastShadows(true);
    light2->SetShadowBias(BiasParameters(0.00025f, 0.5f));

    //Set cascade splits at 10, 50, 200 world unitys, fade shadows at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(7.0f, 23.0f, 42.0f, 500.0f, 0.8f));

    //Create camera
    world_.camera = new OneiroCam(context_, this);
}


void MasterControl::HandleUpdate(StringHash /* eventType */, VariantMap & /* eventData */)
{

}

void MasterControl::HandleSceneUpdate(StringHash /* eventType */, VariantMap &eventData)
{
    using namespace Update;
    double timeStep = eventData[P_TIMESTEP].GetFloat();
    world_.voidNode->SetPosition((2.0f*Vector3::DOWN) + (world_.camera->GetWorldPosition()*Vector3(1.0f,0.0f,1.0f)));
    UpdateCursor(timeStep);
}

void MasterControl::UpdateCursor(double timeStep)
{
    world_.cursor.sceneCursor->Rotate(Quaternion(0.0f,100.0f*timeStep,0.0f));
    world_.cursor.sceneCursor->SetScale((world_.cursor.sceneCursor->GetWorldPosition() - world_.camera->GetWorldPosition()).Length()*0.05f);
    if (CursorRayCast(250.0f, world_.cursor.hitResults))
    {
        for (int i = 0; i != static_cast<int>(world_.cursor.hitResults.Size()); ++i)
        {
            if (world_.cursor.hitResults[i].node_->GetNameHash() == N_VOID)
            {
                Vector3 camHitDifference = world_.camera->translationNode_->GetWorldPosition() - world_.cursor.hitResults[i].position_;
                camHitDifference /= world_.camera->translationNode_->GetWorldPosition().y_ - world_.voidNode->GetPosition().y_;
                camHitDifference *= world_.camera->translationNode_->GetWorldPosition().y_;
                world_.cursor.sceneCursor->SetWorldPosition(world_.camera->translationNode_->GetWorldPosition()-camHitDifference);
            }
        }
    }
}

bool MasterControl::CursorRayCast(double maxDistance, PODVector<RayQueryResult> &hitResults)
{
    Ray cameraRay = world_.camera->camera_->GetScreenRay(0.5f,0.5f);
    RayOctreeQuery query(hitResults, cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY);
    world_.scene->GetComponent<Octree>()->Raycast(query);
    if (hitResults.Size()) return true;
    else return false;
}

void MasterControl::Exit()
{
    engine_->Exit();
}

void MasterControl::HandlePostRenderUpdate(StringHash /* eventType */, VariantMap & /* eventData */)
{
    //world.scene->GetComponent<PhysicsWorld>()->DrawDebugGeometry(true);
}
