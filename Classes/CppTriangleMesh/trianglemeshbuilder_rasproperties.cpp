#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamRasProperties() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       dictionary;\n"
    << "    location    \"constant\";\n"
    << "    object      RASProperties;\n"
    << "}\n"
    << "\n"
    << "RASModel        realizableKE;\n"
    << "\n"
    << "turbulence      on;\n"
    << "\n"
    << "printCoeffs     on;\n"
  ;
  return s.str();
}
