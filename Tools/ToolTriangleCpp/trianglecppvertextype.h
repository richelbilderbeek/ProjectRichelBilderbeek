#ifndef TRIANGLECPPVERTEXTYPE_H
#define TRIANGLECPPVERTEXTYPE_H

namespace ribi {
namespace tricpp {

enum class VertexType
{
  INPUTVERTEX   = 0,
  SEGMENTVERTEX = 1,
  FREEVERTEX    = 2,
  DEADVERTEX    = -32768,
  UNDEADVERTEX  = -32767
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPVERTEXTYPE_H
