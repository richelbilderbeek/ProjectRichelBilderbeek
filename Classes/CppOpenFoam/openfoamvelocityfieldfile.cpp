#include "openfoamvelocityfieldfile.h"

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
#include "openfoampatchfieldtypes.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::VelocityFieldFile::VelocityFieldFile(
  const Header header
) noexcept
  : m_boundary_field{},
    m_dimensions{{}},
    m_header{header},
    m_internal_field{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::VelocityFieldFile::GetDefaultHeader() noexcept
{
  return Header("volVectorField","0","","U");
}

#ifndef NDEBUG
void ribi::foam::VelocityFieldFile::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const VelocityFieldFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << "dimensions ["
      << f.m_dimensions[0] << " "
      << f.m_dimensions[1] << " "
      << f.m_dimensions[2] << " "
      << f.m_dimensions[3] << " "
      << f.m_dimensions[4] << " "
      << f.m_dimensions[5] << " "
      << f.m_dimensions[6]
      << "];" << '\n'
    << "\n"
    << "internalField " << f.m_internal_field << ";\n"
    << "\n"
    << "boundaryField\n"
    << "{\n" << '\n'
  ;
  os << f.m_boundary_field << '\n';
  /*
  for (const auto& p: f.m_boundary_field)
  {
    os
      << "  " << p.first << '\n'
      << "  {\n"
      << "    type " << PatchFieldTypes::ToStr(p.second) << ";\n"
      << "  }\n"
    ;
  }
  */
  os
    << "}\n";
    return os;
  ;
  return os;
}
