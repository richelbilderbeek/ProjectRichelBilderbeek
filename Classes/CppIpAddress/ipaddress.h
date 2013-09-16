//---------------------------------------------------------------------------
/*
IpAddress, class for containing an IP address
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppIpAddress.htm
//---------------------------------------------------------------------------
#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <string>
#include <vector>

#include <boost/checked_delete.hpp>


namespace ribi {

///IpAddress guarantees to contain a valid IP address
struct IpAddress
{
  ///IpAddress constructor throws an exception when
  ///ip_address is not a valid IP address
  explicit IpAddress(const std::string& ip_address);

  ///IpAddress is a base class, so its destructor must be virtual
  virtual ~IpAddress() noexcept {}

  ///Get the IP address as a std::string
  const std::string& Get() const noexcept { return m_ip_address; }

  ///Obtain the IpAddress version
  static const std::string GetVersion() noexcept;

  ///Obtain the IpAddress version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///The std::string guaranteed to hold a valid IP address
  std::string m_ip_address;
};

///SafeIpAddress contains a valid or invalid IP address
struct SafeIpAddress //: public IpAddress
{
  ///SafeIpAddress constructor does not throw an exception
  ///ip_address is not a valid IP address
  SafeIpAddress(const std::string& ip_address) noexcept;
  SafeIpAddress(const SafeIpAddress&) = delete;
  SafeIpAddress& operator=(const SafeIpAddress&) = delete;

  ///Get the possibe IP address as a std::string
  const std::string& Get() const noexcept { return m_ip_address; }

  private:
  ~SafeIpAddress() noexcept {}
  friend void boost::checked_delete<>(SafeIpAddress*);

  ///The std::string that might hold a valid IP address
  std::string m_ip_address;
};

bool operator==(const IpAddress& lhs,const IpAddress& rhs) noexcept;
bool operator==(const SafeIpAddress& lhs,const SafeIpAddress& rhs) noexcept;

} //~namespace ribi

#endif // IPADDRESS_H
