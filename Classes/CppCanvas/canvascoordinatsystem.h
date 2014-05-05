#ifndef RIBI_CANVASCOORDINATSYSTEM_H
#define RIBI_CANVASCOORDINATSYSTEM_H

namespace ribi {

///The coordinat system used in displayal:
///- screen: origin is at top-left of the screen
///- graph: origin is at bottom-left of the screen
enum class CanvasCoordinatSystem
{
  graph,
  screen,

  n_types //Used for testing
};

///View canvascoordinatsystem.h for functions to work with this enum class

} //~namespace ribi

#endif // RIBI_CANVASCOORDINATSYSTEM_H
