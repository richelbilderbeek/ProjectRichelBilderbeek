#include "trianglecppvertex.h"

int tricpp::triunsuitable(
  const Vertex triorg,
  const Vertex tridest,
  const Vertex triapex,
  double /* area */
)
{
  const double dxoa = triorg[0] - triapex[0];
  const double dyoa = triorg[1] - triapex[1];
  const double dxda = tridest[0] - triapex[0];
  const double dyda = tridest[1] - triapex[1];
  const double dxod = triorg[0] - tridest[0];
  const double dyod = triorg[1] - tridest[1];
  /* Find the squares of the lengths of the triangle's three edges. */
  const double oalen = dxoa * dxoa + dyoa * dyoa;
  const double dalen = dxda * dxda + dyda * dyda;
  const double odlen = dxod * dxod + dyod * dyod;
  /* Find the square of the length of the longest edge. */
  double maxlen = (dalen > oalen) ? dalen : oalen;
  maxlen = (odlen > maxlen) ? odlen : maxlen;

  if (maxlen > 0.05 * (triorg[0] * triorg[0] + triorg[1] * triorg[1]) + 0.02) {
    return 1;
  } else {
    return 0;
  }
}
