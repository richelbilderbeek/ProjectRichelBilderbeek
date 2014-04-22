//---------------------------------------------------------------------------
/*
ndsmake, tool to generate NDS makefile from Qt Creator project file
Copyright (C) 2010 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolNdsmake.htm
//---------------------------------------------------------------------------
#ifndef NDSMAKE_H
#define NDSMAKE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct QtCreatorProFile;

struct Ndsmake
{
  ///Call ndsmake on a .pro file
  Ndsmake(const std::string filename);

  void CreateMakefile() const noexcept;

  const std::string& GetCommand() const noexcept { return m_command; }
  static const std::vector<std::string> GetHelp() noexcept;
  static const std::vector<std::string> GetHistory() noexcept;
  static const std::vector<std::string> GetLicence() noexcept;

  ///Obtain the TARGET of the possibly multiple QtCreatorProFile::m_targets
  const std::string GetTarget() const noexcept;

  static std::string GetVersion() noexcept { return "1.2"; }

  private:
  ~Ndsmake() noexcept {}
  friend void boost::checked_delete<>(Ndsmake* x);

  const std::string m_command; //A terminal command
  const boost::shared_ptr<const QtCreatorProFile> m_proFile;

  const std::string CreateCommand() const noexcept;
  void CreateHolyMakefile() const noexcept;

  const boost::shared_ptr<const QtCreatorProFile> GetProFile() const noexcept { return m_proFile; }

  //From http://www.richelbilderbeek.nl/CppRemoveExtension.htm
  static const std::string RemoveExtension(const std::string& filename);

};

} //~namespace ribi

#endif // NDSMAKE_H
