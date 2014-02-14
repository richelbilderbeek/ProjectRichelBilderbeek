#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamP() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       volScalarField;\n"
    << "    object      p;\n"
    << "}\n"
    << "\n"
    << "dimensions      [1 -1 -2 0 0 0 0];\n"
    << "\n"
    << "internalField   uniform 1.7e5;\n"
    << "\n"
    << "boundaryField\n"
    << "{\n"
    << "    	inlet           \n"
    << "    	{\n"
    << " 		type		uniformFixedValue;\n"
    << "                uniformValue tableFile;\n"
    << "                tableFileCoeffs\n"
    << "                {\n"
    << "		fileName	\"pIn\"\n"
    << "		outOfBounds	clamp;			\n"
    << "                }\n"
    << "    	}\n"
    << "\n"
    << "    	outlet          \n"
    << "    	{\n"
    << "		type		uniformFixedValue;\n"
    << "                uniformValue tableFile;\n"
    << "                tableFileCoeffs\n"
    << "                {\n"
    << "		fileName	\"pOut\"\n"
    << "                outOfBounds	clamp;			\n"
    << "                }\n"
    << "    	}\n"
    << "\n"
    << "	side_CW\n"
    << "	{\n"
    << "		type		zeroGradient;\n"
    << "	}\n"
    << "\n"
    << "	side_CCW\n"
    << "	{\n"
    << "		type		zeroGradient;\n"
    << "	}\n"
    << "\n"
    << "    	inside\n"
    << "	{\n"
    << "        	type		patch;\n"
    << "    	}\n"
    << "\n"
    << "    	outside\n"
    << "	{\n"
    << "        	type		zeroGradient;\n"
    << "    	}\n"
    << "}\n"
  ;
  return s.str();
}

