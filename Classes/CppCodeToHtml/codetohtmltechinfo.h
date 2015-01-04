//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifndef CODETOHTMLTECHINFO_H
#define CODETOHTMLTECHINFO_H

#include <set>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "codetohtml.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace c2h {

///Defines the header of the resulting HTML page
struct TechInfo
{
  enum class ApplicationType { desktop, mobile, web };
  enum class Compiler { gpp, bcc32 };
  enum class Ide { command_line, cpp_builder, qt_creator };
  enum class Library { big_int, boost, cln, libnds, qt, stl, vcl, wt };
  enum class OperatingSystem { android,cygwin,lubuntu,maemo,nds,raspbian,symbian,ubuntu,virtualbox,windows,wine };
  enum class ProjectType { console, gui };
  enum class Standard { cpp98, cpp11 };

  ///Construct a TechInfo from zero, one ore more QtCreatorProFiles
  explicit TechInfo(const std::vector<std::string>& profile_filenames);

  ///Convert the TechInfo to HTML
  std::vector<std::string> ToHtml() const;

  private:
  ~TechInfo() noexcept {}
  friend void boost::checked_delete<>(TechInfo*);
  friend void boost::checked_delete<>(const TechInfo*);

  ///The application types for this project
  std::set<ApplicationType> m_application_types;
  ///The compiler used for this project
  std::set<Compiler> m_compilers;
  ///The IDE used for this project
  std::set<Ide> m_ides;
  ///The libraries used for this project
  std::set<Library> m_libraries;
  ///The operating system used for this project
  std::set<OperatingSystem> m_operating_systems;
  ///The project types this project has
  std::set<ProjectType> m_project_types;
  ///The C++ standard(s) this project uses
  std::set<Standard> m_standards;
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLTECHNICALINFO_H
