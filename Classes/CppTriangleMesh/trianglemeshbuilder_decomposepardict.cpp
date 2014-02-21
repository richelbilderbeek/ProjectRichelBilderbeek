/*
#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamDecomposeParDict() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       dictionary;\n"
    << "    location    \"system\";\n"
    << "    object      decomposeParDict;\n"
    << "}\n"
    << "\n"
    << "numberOfSubdomains 4;\n"
    << "\n"
    << "method          	scotch;\n"
    << "\n"
    << "simpleCoeffs\n"
    << "{\n"
    << "    n			( 4 1 1 );\n"
    << "    delta		0.001;\n"
    << "}\n"
    << "\n"
    << "hierarchicalCoeffs\n"
    << "{\n"
    << "    n			( 1 1 1 );\n"
    << "    delta		0.001;\n"
    << "    order		xyz;\n"
    << "}\n"
    << "\n"
    << "metisCoeffs\n"
    << "{\n"
    << "    processorWeights	( 1 1 1 1 );\n"
    << "}\n"
    << "\n"
    << "manualCoeffs\n"
    << "{\n"
    << "    dataFile		"";\n"
    << "}\n"
    << "\n"
    << "distributed		no;\n"
    << "\n"
    << "roots			( );\n"
    << "\n"
    << "\n"
  ;
  return s.str();
}
*/
