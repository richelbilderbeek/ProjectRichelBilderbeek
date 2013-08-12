#include <cassert>
#include "irrlicht.h"

int main()
{
  irr::IrrlichtDevice * const device = irr::createDevice(irr::video::EDT_SOFTWARE);

  device->setWindowCaption(L"HelloIrrlicht");

  irr::video::IVideoDriver * const driver = device->getVideoDriver();
  irr::scene::ISceneManager * const scene_manager = device->getSceneManager();
  irr::gui::IGUIEnvironment * const gui_environment = device->getGUIEnvironment();
  irr::scene::IAnimatedMesh * const mesh = scene_manager->getMesh("../../Libraries/irrlicht-1.8/media/sydney.md2");
  assert(mesh);

  irr::scene::IAnimatedMeshSceneNode * const node = scene_manager->addAnimatedMeshSceneNode( mesh );
  assert(node);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setMD2Animation(irr::scene::EMAT_STAND);
  node->setMaterialTexture( 0, driver->getTexture("../../Libraries/irrlicht-1.8/media/sydney.bmp") );

  scene_manager->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

  while(device->run())
  {
    driver->beginScene(
      true,
      true,
      irr::video::SColor(0,195,195,195));
    scene_manager->drawAll();
    gui_environment->drawAll();
    driver->endScene();
  }
  device->drop();
}
