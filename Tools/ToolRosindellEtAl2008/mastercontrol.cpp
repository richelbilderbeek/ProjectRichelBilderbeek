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
#include <string>
#include <vector>

#include <QFile>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
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

#include "rng.h"
#include "tree.h"

DEFINE_APPLICATION_MAIN(MasterControl);

MasterControl::MasterControl(Context *context):
    Application(context)
{
  {
    const int error{std::system("ln -s ../../Libraries/Urho3D/bin/Data")};
    if (error) {}
  }
  {
    const int error{std::system("ln -s ../../Libraries/Urho3D/bin/CoreData")};
    if (error) {}
  }
}


void MasterControl::Setup()
{
  // Modify engine startup parameters.
  //Set custom window title and icon.
  engineParameters_["WindowTitle"] = "RosindellEtAl2008";
  engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs")+"RosindellEtAl2008.log";
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
  UI* const ui = GetSubsystem<UI>();

  //Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will control the camera
  world_.cursor.uiCursor = new Cursor(context_);
  world_.cursor.uiCursor->SetVisible(false);
  ui->SetCursor(world_.cursor.uiCursor);

  //Set starting position of the cursor at the rendering window center
  world_.cursor.uiCursor->SetPosition(graphics_->GetWidth()/2, graphics_->GetHeight()/2);

}

void MasterControl::CreateBackground()
{
  for (int i = -2; i <= 2; i++)
  {
    for (int j = -2; j <= 2; j++)
    {
        world_.backgroundNode = world_.scene->CreateChild("BackPlane");
        world_.backgroundNode->SetScale(Vector3(512.0f, 1.0f, 512.0f));
        world_.backgroundNode->SetPosition(Vector3(512.0*i, -1000.0, 512.0*j));
        StaticModel* backgroundObject = world_.backgroundNode->CreateComponent<StaticModel>();
        backgroundObject->SetModel(cache_->GetResource<Model>("Models/Plane.mdl"));
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

  //Do simulation
  {
    Rng rng(4,Rng::Type::bilderbeek);
    const int area_width{3};
    const int area_length{3};
    const double min_speciation_rate{0.1};
    const int dispersal_distance{1};
    const double tolerance{0.1};
    const DispersalKernel dispersal_kernel{
      DispersalKernel::square
    };

    Tree tree(
      rng,
      area_width,
      area_length,
      min_speciation_rate,
      dispersal_distance,
      tolerance,
      dispersal_kernel
    );
    assert(!tree.IsDone());

    for (int t=0; t!=1000; ++t)
    {
      //Draw all active nodes
      for (const TreeDataPoint& p: GetRelevantActive(tree))
      {
        const int x{p.GetAbsoluteXpos()};
        const int y{p.GetAbsoluteYpos()};
        Node * const node{world_.scene->CreateChild()};
        node->SetPosition(
          Vector3(
            0.5 + (static_cast<double>(x) * 1.0), //Urho: X
            0.5 + (static_cast<double>(t) * 1.0), //Urho: Y
            0.5 + (static_cast<double>(y) * 1.0)  //Urho: Z
          )
        );
        StaticModel * const model = node->CreateComponent<StaticModel>();
        model->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
        model->SetCastShadows(true);
      }
      tree.Update();
    }

  }

  //Create camera
  world_.camera = new CameraMaster(context_, this);
}


void MasterControl::Exit()
{
  engine_->Exit();
}
