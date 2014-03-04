/*
#include "trianglemeshbuilder.h"

#include <sstream>

std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamT() const noexcept
{
  std::stringstream s;
  s
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
*/
