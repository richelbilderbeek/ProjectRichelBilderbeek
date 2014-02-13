#include "trianglemeshbuilder.h"

#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic pop

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamU() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       volVectorField;\n"
    << "    object      U;\n"
    << "}\n"
    << "\n"
    << "dimensions      [0 1 -1 0 0 0 0];\n"
    << "\n"
    << "internalField   uniform (0 0 0);\n"
    << "\n"
    << "boundaryField\n"
    << "{\n"
    << "    	inlet           \n"
    << "    	{\n"
    << "		type		zeroGradient;\n"
    << "//    		type		pressureInletVelocity;\n"
    << "//		value		uniform (0 0 0);\n"
    << "    	}\n"
    << "\n"
    << "    	outlet          \n"
    << "    	{\n"
    << "        	type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "	side_CW\n"
    << "	{\n"
    << "		type		slip;\n"
    << "	}\n"
    << "\n"
    << "	side_CCW\n"
    << "	{\n"
    << "		type		slip;\n"
    << "	}\n"
    << "\n"
    << "    	defaultFaces\n"
    << "    	{\n"
    << "        	type		fixedValue;\n"
    << "		value		uniform (0 0 0);\n"
    << "    	}\n"
    << "}\n"
  ;
  return s.str();
}
