#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamMut() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       volScalarField;\n"
    << "    location    \"0\";\n"
    << "    object      mut;\n"
    << "}\n"
    << "\n"
    << "dimensions      [ 1 -1 -1 0 0 0 0 ];\n"
    << "\n"
    << "internalField   uniform 0;\n"
    << "\n"
    << "boundaryField\n"
    << "{\n"
    << "    	inlet\n"
    << "    	{\n"
    << "		type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "    	outlet\n"
    << "    	{\n"
    << "        	type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "    	side_CW\n"
    << "    	{\n"
    << "        	type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "    	side_CCW\n"
    << "    	{\n"
    << "        	type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "    	defaultFaces\n"
    << "    	{\n"
    << "        	type		mutkWallFunction;\n"
    << "        	value		uniform 0;\n"
    << "    	}\n"
    << "}\n"
  ;
  return s.str();
}
