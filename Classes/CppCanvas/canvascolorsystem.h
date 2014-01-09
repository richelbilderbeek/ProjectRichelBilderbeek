#ifndef CANVASCOLORSYSTEM_H
#define CANVASCOLORSYSTEM_H

namespace ribi {

///The color system used to draw on a Canvas:
///- normal: full/drawn is displayed by M
///- invert: empty/non-drawn is displayed by M
enum class CanvasColorSystem
{
  normal,
  invert,

  n_types //Used for testing
};

} //~namespace ribi

#endif // CANVASCOLORSYSTEM_H
