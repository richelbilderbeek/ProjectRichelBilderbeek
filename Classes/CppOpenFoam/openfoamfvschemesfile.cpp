#include "openfoamfvschemesfile.h"

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
#include "filename.h"
#include "openfoamheader.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::FvSchemesFile::FvSchemesFile(
  const Header header
) : m_header(header)
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::FvSchemesFile::GetDefaultHeader() noexcept
{
  return Header("dictionary","system","","fvSchemes");
}

#ifndef NDEBUG
void ribi::foam::FvSchemesFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::FvSchemesFile::Test");
  TRACE("Finished ribi::foam::FvSchemesFile successfully");
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const FvSchemesFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << "ddtSchemes\n"
    << "{\n"
    << "  default Euler;\n"
    << "}\n"
    << "\n"
    << "gradSchemes\n"
    << "{\n"
    << "  default Gauss linear;\n"
    << "}\n"
    << "\n"
    << "divSchemes\n"
    << "{\n"
    << "  default none;\n"
    << "  div(phi,U) Gauss limitedLinearV 1;\n"
    << "  div(phi,e) Gauss limitedLinear 1;\n"
    << "  div(phid,p) Gauss limitedLinear 1;\n"
    << "  div(phi,K) Gauss limitedLinear 1;\n"
    << "  div(phiv,p) Gauss limitedLinear 1;\n"
    << "  div(phi,k) Gauss upwind;\n"
    << "  div(phi,epsilon) Gauss upwind;\n"
    << "  div((muEff*dev2(T(grad(U))))) Gauss linear;\n"
    << "}\n"
    << "\n"
    << "laplacianSchemes\n"
    << "{\n"
    << "  default Gauss linear corrected;\n"
    << "}\n"
    << "\n"
    << "interpolationSchemes\n"
    << "{\n"
    << "  default linear;\n"
    << "}\n"
    << "\n"
    << "snGradSchemes\n"
    << "{\n"
    << "  default corrected;\n"
    << "}\n"
    << "\n"
    << "fluxRequired\n"
    << "{\n"
    << "  default no;\n"
    << "  p;\n"
    << "}\n";
  return os;
}
