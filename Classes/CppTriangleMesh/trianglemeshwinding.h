#ifndef TRIANGLEMESHWINDING_H
#define TRIANGLEMESHWINDING_H

namespace ribi {
namespace trim {

///The winding the Points of a Face have, when viewed from the inside of a Cell
enum class Winding
{
  clockwise,
  counter_clockwise,
  indeterminate ,
  n_types //To be used in debugging only
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHWINDING_H
