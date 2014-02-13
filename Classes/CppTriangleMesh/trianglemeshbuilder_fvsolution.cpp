#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamFvSolution() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       dictionary;\n"
    << "    location    \"system\";\n"
    << "    object      fvSolution;\n"
    << "}\n"
    << "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n"
    << "\n"
    << "solvers\n"
    << "{\n"
    << "    \"rho.*\"\n"
    << "    {\n"
    << "        solver          diagonal;\n"
    << "    }\n"
    << "\n"
    << "    \"p.*\"\n"
    << "    {\n"
    << "        solver          PBiCG;\n"
    << "        preconditioner  DILU;\n"
    << "        tolerance       1e-08;\n"
    << "        relTol          0;\n"
    << "    }\n"
    << "\n"
    << "    \"(U|e|R).*\"\n"
    << "    {\n"
    << "        $p;\n"
    << "        tolerance       1e-05;\n"
    << "    }\n"
    << "\n"
    << "    \"(k|epsilon).*\"\n"
    << "    {\n"
    << "        $p;\n"
    << "        tolerance       1e-08;\n"
    << "    }\n"
    << "}\n"
    << "\n"
    << "PIMPLE\n"
    << "{\n"
    << "    nOuterCorrectors 2;\n"
    << "    nCorrectors      1;\n"
    << "    nNonOrthogonalCorrectors 0;\n"
    << "}\n";
  return s.str();
}

