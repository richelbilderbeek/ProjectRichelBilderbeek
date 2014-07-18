#include "openfoamthermophysicalpropertiesfile.h"

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


ribi::foam::ThermophysicalPropertiesFile::ThermophysicalPropertiesFile(
  const Header header
)
  : m_header{header},
    m_mixture{},
    m_thermo_type{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::ThermophysicalPropertiesFile::GetDefaultHeader() noexcept
{
  return Header("dictionary","constant","","thermophysicalProperties");
}

#ifndef NDEBUG
void ribi::foam::ThermophysicalPropertiesFile::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::ThermophysicalPropertiesFile::Test");
  TRACE("Finished ribi::foam::ThermophysicalPropertiesFile successfully");
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const ThermophysicalPropertiesFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << "" << '\n'
    << "thermoType " << f.m_thermo_type << ";\n"
    << "mixture " << f.m_mixture << ";\n"
  ;
  return os;
}
