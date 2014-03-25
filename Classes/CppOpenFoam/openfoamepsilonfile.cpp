#include "openfoamepsilonfile.h"

#include "openfoamdecomposepardictfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include <QFile>

#include "fileio.h"

#include "openfoamheader.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::EpsilonFile::EpsilonFile(
  const Header header
)
  : m_header{header}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::EpsilonFile::GetDefaultHeader() noexcept
{
  return Header("volScalarField","0","","epsilon");
}

#ifndef NDEBUG
void ribi::foam::EpsilonFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::OpenFoamEpsilonFile::Test");
  TRACE("Finished ribi::foam::OpenFoamEpsilonFile successfully");
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const EpsilonFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
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
  ;
  return os;
}
