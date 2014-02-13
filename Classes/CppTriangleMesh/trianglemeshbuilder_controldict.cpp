#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamControlDict() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       dictionary;\n"
    << "    location    \"system\";\n"
    << "    object      controlDict;\n"
    << "}\n"
    << "\n"
    << "application			sonicFoam;\n"
    << "\n"
    << "startFrom       	latestTime;\n"
    << "\n"
    << "startTime       	0;\n"
    << "\n"
    << "stopAt          	endTime;\n"
    << "\n"
    << "endTime         	7e-3;			//ten times the pressure build-up time pInlet\n"
    << "\n"
    << "deltaT         		1e-8;\n"
    << "\n"
    << "writeControl    	adjustableRunTime;\n"
    << "\n"
    << "writeInterval   	1e-6;			//don't create too much data \n"
    << "\n"
    << "purgeWrite      	0;\n"
    << "\n"
    << "writeFormat     	ascii;\n"
    << "\n"
    << "writePrecision  	6;\n"
    << "\n"
    << "writeCompression 	uncompressed;\n"
    << "\n"
    << "timeFormat      	general;\n"
    << "\n"
    << "timePrecision   	6;\n"
    << "\n"
    << "runTimeModifiable 	yes;\n"
    << "\n"
    << "adjustTimeStep   	no;\n"






    << "\n"
    << "\n"
    << "// ************************************************************************* //\n"
  ;
  return s.str();
}
