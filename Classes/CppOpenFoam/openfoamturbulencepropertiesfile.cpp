#include "openfoamturbulencepropertiesfile.h"

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


ribi::foam::TurbulencePropertiesFile::TurbulencePropertiesFile(
  const Header header
)
  : m_header{header},
    m_simulation_type{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::TurbulencePropertiesFile::GetDefaultHeader() noexcept
{
  return Header("dictionary","constant","","turbulenceProperties");
}

#ifndef NDEBUG
void ribi::foam::TurbulencePropertiesFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::TurbulencePropertiesFile::Test");
  TRACE("Finished ribi::foam::TurbulencePropertiesFile successfully");
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const TurbulencePropertiesFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << "simulationType " << f.m_simulation_type << ";\n"
  ;
  return os;
}
