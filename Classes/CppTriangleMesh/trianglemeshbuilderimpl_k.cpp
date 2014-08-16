#include "trianglemeshbuilderimpl.h"

#include <sstream>

std::string ribi::trim::TriangleMeshBuilderImpl::CreateOpenFoamK() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       volScalarField;\n"
    << "    location    \"0\";\n"
    << "    object      k;\n"
    << "}\n"
    << "\n"
    << "dimensions      [ 0 2 -2 0 0 0 0 ];\n"
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
    << "       		type		zeroGradient;\n"
    << "    	}\n"
    << "\n"
    << "    	defaultFaces\n"
    << "    	{\n"
    << "       		type		compressible::kqRWallFunction;\n"
    << "        	value		uniform 0;\n"
    << "    	}\n"
    << "}\n"
  ;
  return s.str();
}
