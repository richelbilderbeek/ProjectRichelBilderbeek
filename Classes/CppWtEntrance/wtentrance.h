//---------------------------------------------------------------------------
/*
WtEntrance, online entrance
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppWtEntrance.htm
//---------------------------------------------------------------------------
#ifndef WTENTRANCE_H
#define WTENTRANCE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct IpAddress;

///\brief
///WtEntrance is a virtual entrance for all webpage visitors
///
///WtEntrance is a Singleton
struct WtEntrance
{
  ///Obtain the one-and-only WtEntrance instance
  static WtEntrance * Get() noexcept;

  ///Look up the IP address its name
  std::string GetName(const IpAddress * const ip_address) const;

  ///Get all the IP addresses their names
  std::vector<std::pair<std::string,std::string>> GetNames() const;

  ///Obtain the WtEntrance version
  static std::string GetVersion() noexcept;

  ///Obtain the WtEntrance version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Get all the IP addresses their visits
  std::vector<std::pair<std::string,std::string> > GetVisits() const noexcept;

  ///Set the IP address its name
  void SetName(const IpAddress * const ip_address, const std::string& name) const;

  ///Log a visit
  void Visit(const IpAddress * const ip_address);

  ///This signal emitted when a user changes his/her name
  mutable boost::signals2::signal<void ()> m_signal_name_changed;

  ///This signal emitted when there is a new user visiting
  mutable boost::signals2::signal<void ()> m_signal_new_visit;

  private:
  WtEntrance();

  ///The filename of the file mapping IP addresses to names
  static const std::string m_filename_names;

  ///The filename of the file mapping IP addresses to visits
  static const std::string m_filename_visits;

  ///The one-and-only WtEntrance instance
  static WtEntrance * m_instance;  

  ///Convert a file to a std::vector
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  //static const std::vector<std::string> FileToVector(const std::string& filename);

  ///Returns date in YYYY-MM-DD format
  //From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
  static std::string GetDateIso8601() noexcept;

  ///Get the current time
  //From http://www.richelbilderbeek.nl/CppGetTime.htm
  static std::string GetTime() noexcept;

  ///Returns the current date and time as a YYYY_MM_DD_HH_MM_SS std::string,
  ///for example '2011_07_01_11_35_38'
  //From http://www.richelbilderbeek.nl/CppGetTimestamp.htm
  static std::string GetTimestamp() noexcept;

  ///Split a std::string
  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static std::vector<std::string> SeperateString(
    const std::string& input,
   const char seperator) noexcept;
};

} //~namespace ribi

#endif // WTENTRANCE_H
