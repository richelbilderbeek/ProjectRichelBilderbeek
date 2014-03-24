#include "openfoamcontroldictfile.h"

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


ribi::foam::ControlDictFile::ControlDictFile(
  const Header header
)
  : m_adjust_time_step{},
    m_application{},
    m_delta_t{},
    m_end_time{},
    m_header{header},
    m_purge_write{},
    m_start_from{},
    m_start_time{},
    m_stop_at{},
    m_time_format{},
    m_time_precision{},
    m_run_time_modifiable{},
    m_write_compression{},
    m_write_control{},
    m_write_format{},
    m_write_interval{},
    m_write_precision{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::foam::Header ribi::foam::ControlDictFile::GetDefaultHeader() noexcept
{
  return Header("dictionary","system","","controlDict");
}

#ifndef NDEBUG
void ribi::foam::ControlDictFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::ControlDictFile::Test");
  TRACE("Finished ribi::foam::ControlDictFile successfully");
}
#endif

std::ostream& ribi::foam::operator<<(std::ostream& os, const ControlDictFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << "application " << f.m_application << ";\n"
    << "startFrom " << f.m_start_from <<";\n"
    << "startTime " << f.m_start_time << ";\n"
    << "stopAt " << f.m_stop_at << ";\n"
    << "endTime " << f.m_end_time << ";\n"
    << "deltaT " << f.m_delta_t << ";\n"
    << "writeControl " << f.m_write_control << ";\n"
    << "writeInterval " << f.m_write_interval << ";\n"
    << "purgeWrite " << f.m_purge_write << ";\n"
    << "writeFormat " << f.m_write_format << ";\n"
    << "writePrecision " << f.m_write_precision << ";\n"
    << "writeCompression " << f.m_write_compression << ";\n"
    << "timeFormat " << f.m_time_format << ";\n"
    << "timePrecision " << f.m_time_precision << ";\n"
    << "runTimeModifiable " << (f.m_run_time_modifiable ? "yes" : "no") << ";\n"
    << "adjustTimeStep " << (f.m_adjust_time_step ? "yes" : "no") << ";\n"
  ;
  return os;
}
