#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamT() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       volScalarField;\n"
    << "    object      T;\n"
    << "}\n"
    << "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n"
    << "\n"
    << "dimensions      [0 0 0 1 0 0 0];\n"
    << "\n"
    << "internalField   uniform 293;\n"
    << "\n"
    << "boundaryField\n"
    << "{\n"
    << "    	inlet           \n"
    << "    	{\n"
    << " 		type		fixedValue;\n"
    << "		value		uniform 293;		\n"
    << "    	}\n"
    << "\n"
    << "    	outlet          \n"
    << "    	{\n"
    << "        	type		zeroGradient;\n"
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
    << "	defaultFaces\n"
    << "	{\n"
    << "		type		zeroGradient;\n"
    << "    	}\n"
    << "}\n"

  ;
  return s.str();
}
