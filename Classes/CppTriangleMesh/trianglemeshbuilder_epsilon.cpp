#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamEpsilon() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       volScalarField;\n"
    << "    location    \"0\";\n"
    << "    object      epsilon;\n"
    << "}\n"
    << "\n"
    << "dimensions      [ 0 2 -3 0 0 0 0 ];\n"
    << "\n"
    << "internalField   uniform 500000;\n"
    << "\n"
    << "boundaryField\n"
    << "{\n"
    << "\n"
    << "    	inlet\n"
    << "    	{\n"
    << "		type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "    	outlet\n"
    << "	{\n"
    << "        	type		zeroGradient;\n"
    << "   	}\n"
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
    << " \n"
    << "    	defaultFaces\n"
    << "    	{\n"
    << "        	type		compressible::epsilonWallFunction;\n"
    << "        	value		uniform 500000;\n"
    << "    	}\n"
    << "}\n"
    << "\n"
  ;
  return s.str();
}
