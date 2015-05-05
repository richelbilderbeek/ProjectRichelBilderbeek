//Music from https://www.jamendo.com/en/list/a142918/meditations

#include <vector>

#include <QFile>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#define BT_INFINITY

#include <Urho3D/Urho3D.h>

#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/DebugNew.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Resource.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>

#pragma GCC diagnostic pop

#include "mastercontrol.h"
#include "cameramaster.h"
#include "inputmaster.h"

DEFINE_APPLICATION_MAIN(MasterControl);

MasterControl::MasterControl(Context *context):
    Application(context)
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

  {
    Sound * const music = cache_->GetResource<Sound>("MacroformDreaming.ogg");
    music->SetLooped(true);
    Node * const musicNode = world_.scene->CreateChild("Music");
    SoundSource * const musicSource = musicNode->CreateComponent<SoundSource>();
    musicSource->SetSoundType(SOUND_MUSIC);
    musicSource->Play(music);
  }
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
  UI* const ui = GetSubsystem<UI>();

  //Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will control the camera
  world_.cursor.uiCursor = new Cursor(context_);
  world_.cursor.uiCursor->SetVisible(false);
  ui->SetCursor(world_.cursor.uiCursor);

  //Set starting position of the cursor at the rendering window center
  world_.cursor.uiCursor->SetPosition(graphics_->GetWidth()/2, graphics_->GetHeight()/2);

  {
    //Construct new Text object, set string to display and font to use
    Text* const instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("TestVoxelWidget");
    instructionText->SetFont(cache_->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 32);
    instructionText->SetColor(Color(1.0,0.5,0.0));
    //The text has multiple rows. Center them in relation to each other
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0,
      ui->GetRoot()->GetHeight() / 8
    );
  }
}

void MasterControl::CreateBackground()
{
  for (int i = -2; i <= 2; i++)
  {
    for (int j = -2; j <= 2; j++)
    {
        world_.backgroundNode = world_.scene->CreateChild("BackPlane");
        world_.backgroundNode->SetScale(Vector3(512.0f, 1.0f, 512.0f));
        world_.backgroundNode->SetPosition(Vector3(512.0f*i, -200.0f, 512.0f*j));
        StaticModel* backgroundObject = world_.backgroundNode->CreateComponent<StaticModel>();
        backgroundObject->SetModel(cache_->GetResource<Model>("Models/Plane.mdl"));
        //backgroundObject->SetMaterial(cache_->GetResource<Material>("Materials/LitSmoke.xml"));
        backgroundObject->SetMaterial(cache_->GetResource<Material>("Materials/JackEnvMap.xml"));
    }
  }
}

void MasterControl::CreateScene()
{
  world_.scene = new Scene(context_);

  //Create octree, use default volume (-1000, -1000, -1000) to (1000,1000,1000)
  {
    world_.scene->CreateComponent<Octree>();
  }
  //Create the physics
  {
    PhysicsWorld * const physicsWorld = world_.scene->CreateComponent<PhysicsWorld>();
    physicsWorld->SetGravity(Vector3::ZERO);
  }

  world_.scene->CreateComponent<DebugRenderer>();

  //Create cursor
  {
    world_.cursor.sceneCursor = world_.scene->CreateChild("Cursor");
    world_.cursor.sceneCursor->SetPosition(Vector3(0.0f,0.0f,0.0f));
    StaticModel * const cursorModel = world_.cursor.sceneCursor->CreateComponent<StaticModel>();
    cursorModel->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
    cursorModel->SetMaterial(cache_->GetResource<Material>("Materials/Water.xml"));
  }

  //Create an invisible plane for mouse raycasting
  world_.voidNode = world_.scene->CreateChild("Void");
  //Location is set in update since the plane moves with the camera.
  world_.voidNode->SetScale(Vector3(1000.0f, 1.0f, 1000.0f));
  StaticModel* planeModel = world_.voidNode->CreateComponent<StaticModel>();
  planeModel->SetModel(cache_->GetResource<Model>("Models/Plane.mdl"));
  planeModel->SetMaterial(cache_->GetResource<Material>("Materials/Terrain.xml"));

  CreateBackground();

  {
    // Create skybox. The Skybox component is used like StaticModel, but it will be always located at the camera, giving the
    // illusion of the box planes being far away. Use just the ordinary Box model and a suitable material, whose shader will
    // generate the necessary 3D texture coordinates for cube mapping
    Node* skyNode = world_.scene->CreateChild("Sky");
    skyNode->SetScale(500.0f); // The scale actually does not matter
    Skybox* skybox = skyNode->CreateComponent<Skybox>();
    skybox->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
    skybox->SetMaterial(cache_->GetResource<Material>("Materials/Skybox.xml"));
  }

  //Create a directional light to the world. Enable cascaded shadows on it
  {
    Node* lightNode = world_.scene->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.0f, -1.0f, 0.0f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetBrightness(1.0f);
    light->SetColor(Color(1.0f, 0.8f, 0.7f));
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));

    //Set cascade splits at 10, 50, 200 world unitys, fade shadows at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(7.0f, 23.0f, 42.0f, 500.0f, 0.8f));
  }

  //Create a second directional light without shadows
  {
    Node * const lightNode = world_.scene->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.0, 1.0, 0.0));
    Light * const light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetBrightness(0.25);
    light->SetColor(Color(1.0, 1.0, 1.0));
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
  }
  //Create boxes
  for (int z=-4; z!=5; ++z)
  {
    for (int y=0; y!=8; ++y)
    {
      for (int x=-4; x!=5; ++x)
      {
        if (std::rand() % 2) continue;
        Node * const node{world_.scene->CreateChild()};
        node->SetPosition(
          Vector3(
            0.5 + (static_cast<double>(x) * 1.0),
            0.5 + (static_cast<double>(y) * 1.0),
            0.5 + (static_cast<double>(z) * 1.0)
          )
        );
        StaticModel * const model = node->CreateComponent<StaticModel>();
        model->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
        model->SetCastShadows(true);

        Material * const material = cache_->GetResource<Material>("Materials/Stone.xml");
        material->SetShaderParameter("DiffColor", "1.0 0.0 0.0");
        model->SetMaterial(material);

      }
    }
  }

  //Create camera
  world_.camera = new CameraMaster(context_, this);
}


void MasterControl::HandleUpdate(StringHash /* eventType */, VariantMap & /* eventData */)
{

}

void MasterControl::HandleSceneUpdate(StringHash /* eventType */, VariantMap &eventData)
{
  using namespace Update;
  double timeStep = eventData[P_TIMESTEP].GetFloat();
  //Let world move along
  //world_.voidNode->SetPosition((2.0f*Vector3::DOWN) + (world_.camera->GetWorldPosition()*Vector3(1.0f,0.0f,1.0f)));
  UpdateCursor(timeStep);
}

void MasterControl::UpdateCursor(double timeStep)
{
  world_.cursor.sceneCursor->Rotate(Quaternion(0.0f,100.0f*timeStep,0.0f));

  //Keep the raycasted cursor a constant size
  //world_.cursor.sceneCursor->SetScale((world_.cursor.sceneCursor->GetWorldPosition() - world_.camera->GetWorldPosition()).Length()*0.05f);
  if (CursorRayCast(250.0f, world_.cursor.hitResults))
  {
    const int n_hits{static_cast<int>(world_.cursor.hitResults.Size())};
    for (int i = 0; i!=n_hits; ++i)
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
  return hitResults.Size();
}

void MasterControl::Exit()
{
  engine_->Exit();
}

void MasterControl::HandlePostRenderUpdate(StringHash /* eventType */, VariantMap & /* eventData */)
{
  //world.scene->GetComponent<PhysicsWorld>()->DrawDebugGeometry(true);
}
