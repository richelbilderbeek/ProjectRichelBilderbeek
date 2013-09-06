//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "ipaddress.h"
#include "trace.h"
#include "wtautoconfig.h"
#include "wtentrance.h"
#include "wtselectfiledialog.h"
#include "wtrichelbilderbeekmenudialog.h"

///TODO
///List sorted on my priority
/// - Add an IP-address/'personal' page
/// - Add SearchAndDestroyChess
/// - Add TestCss to change IP-address/'personal' CSS
/// - Let all WtRichelBilderbeek classes be documented using Doxygen
/// - Test Wt real-time gaming possibilities

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("Project Richel Bilderbeek");
    this->useStyleSheet("wt.css");
    this->enableUpdates(true);
    boost::shared_ptr<const ribi::IpAddress> ip_address(new ribi::IpAddress(env.clientAddress()));
    ribi::WtEntrance::Get()->Visit(ip_address.get());
    root()->addWidget(new ribi::RichelBilderbeek::WtMenuDialog(ip_address->Get()));
  }
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  START_TRACE();
  ribi::WtSelectFileDialog::SetPath(boost::filesystem::path(argv[0]).parent_path().string());
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  ribi::WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}

/*

win32 {

  #Boost libraries
  INCLUDEPATH += \
    ../../Libraries/boost_1_53_0

  #Prevent the following error:
  #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
  #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
  DEFINES += __COMO_VERSION__

  #Boost.Filesystem
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/codecvt_error_category.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/operations.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/path.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/path_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/portability.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/unique_path.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/utf8_codecvt_facet.cpp \ #Keep, comment program_options/src/utf8_codecvt_facet.cpp
    ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.cpp

  #Boost.Program_options
  #
  #This lib does not seem to work well together with Boost.Filesystem
  #when compiled from source like this
  #
  #SOURCES += \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/cmdline.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/config_file.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/convert.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/options_description.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/positional_options.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/split.cpp \
  #  #../../Libraries/boost_1_53_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/value_semantic.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/variables_map.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/winmain.cpp

  #Boost.Regex
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/regex/src/internals.hpp

  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/regex/src/winstances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/wide_posix_api.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/wc_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/w32_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/usinstances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/static_mutex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_traits_defaults.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_raw_buffer.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_debug.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/posix_api.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/instances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/icu.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/fileiter.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/c_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/cregex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/cpp_regex_traits.cpp

  #Boost.System
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/system/src/local_free_on_destruction.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/system/src/error_code.cpp
}


*/
