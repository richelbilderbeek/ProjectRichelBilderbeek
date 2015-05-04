#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#define BT_INFINITY
#include <Urho3D/Input/Input.h>
#pragma GCC diagnostic pop

#include "mastercontrol.h"

namespace Urho3D {
class Drawable;
class Node;
class Scene;
class Sprite;
}

using namespace Urho3D;

class InputMaster : public Object
{
  OBJECT(InputMaster);
public:
  InputMaster(
    Context * const context,
    MasterControl * const masterControl
  );

private:
  MasterControl * const masterControl_;
  void HandleMouseDown(StringHash eventType, VariantMap &eventData);
  void HandleKeyDown(StringHash eventType, VariantMap &eventData);
  void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};
