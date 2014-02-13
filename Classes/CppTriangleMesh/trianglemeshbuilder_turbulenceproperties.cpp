#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamTurbulenceProperties() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       dictionary;\n"
    << "    location    \"constant\";\n"
    << "    object      turbulenceProperties;\n"
    << "}\n"
    << "\n"
    << "simulationType  RASModel;\n"
  ;
  return s.str();
}
