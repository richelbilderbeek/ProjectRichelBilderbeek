#include "openfoamfvsolutionfile.h"

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


ribi::foam::FvSolutionFile::FvSolutionFile(
  const Header header
) : m_header(header)
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::FvSolutionFile::GetDefaultHeader() noexcept
{
  return Header("dictionary","system","","fvSolution");
}

#ifndef NDEBUG
void ribi::foam::FvSolutionFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::FvSolutionFile::Test");
  TRACE("Finished ribi::foam::FvSolutionFile successfully");
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const FvSolutionFile& f) noexcept
{
  os
    << f.GetHeader() << '\n';
  return os;
}



/*

#include "trianglemeshbuilder.h"

#include <sstream>

const std::string ribi::trim::TriangleMeshBuilder::CreateOpenFoamFvSolution() const noexcept
{
  std::stringstream s;
  s
    << "FoamFile\n"
    << "{\n"
    << "    version     2.0;\n"
    << "    format      ascii;\n"
    << "    class       dictionary;\n"
    << "    location    \"system\";\n"
    << "    object      fvSolution;\n"
    << "}\n"
    << "\n"
    << "solvers\n"
    << "{\n"
    << "    \"rho.*\"\n"
    << "    {\n"
    << "        solver          diagonal;\n"
    << "    }\n"
    << "\n"
    << "    \"p.*\"\n"
    << "    {\n"
    << "        solver          PBiCG;\n"
    << "        preconditioner  DILU;\n"
    << "        tolerance       1e-08;\n"
    << "        relTol          0;\n"
    << "    }\n"
    << "\n"
    << "    \"(U|e|R).*\"\n"
    << "    {\n"
    << "        $p;\n"
    << "        tolerance       1e-05;\n"
    << "    }\n"
    << "\n"
    << "    \"(k|epsilon).*\"\n"
    << "    {\n"
    << "        $p;\n"
    << "        tolerance       1e-08;\n"
    << "    }\n"
    << "}\n"
    << "\n"
    << "PIMPLE\n"
    << "{\n"
    << "    nOuterCorrectors 2;\n"
    << "    nCorrectors      1;\n"
    << "    nNonOrthogonalCorrectors 0;\n"
    << "}\n";
  return s.str();
}


*/
