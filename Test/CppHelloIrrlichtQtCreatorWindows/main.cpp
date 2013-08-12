#include "irrlicht.h"

int main()
{
  irr::IrrlichtDevice * const device = irr::createDevice(irr::video::EDT_SOFTWARE);

  device->setWindowCaption(L"HelloIrrlicht");

  irr::video::IVideoDriver * const driver = device->getVideoDriver();
  irr::scene::ISceneManager * const scene_manager = device->getSceneManager();
  irr::gui::IGUIEnvironment * gui_environment = device->getGUIEnvironment();

  gui_environment->addStaticText(
    L"HelloIrrlicht!",
    irr::core::rect<int>(320-32,240-8,320+32,240+8),
    true);

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
