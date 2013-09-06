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
#include <boost/noncopyable.hpp>

namespace ribi {

///IpAddress guarantees to contain a valid IP address
struct IpAddress
{
  ///IpAddress constructor throws an exception when
  ///ip_address is not a valid IP address
  explicit IpAddress(const std::string& ip_address);

  ///IpAddress is a base class, so its destructor must be virtual
  virtual ~IpAddress()  {}


  ///Set the IP address. Will throws an exception when
  ///the ip_address is not a valid IP address
  void Set(const std::string& ip_address);

  ///Get the IP address as a std::string
  const std::string& Get() const { return m_ip_address; }

  ///Obtain the IpAddress version
  static const std::string GetVersion();

  ///Obtain the IpAddress version history
  static const std::vector<std::string> GetVersionHistory();

  private:
  ///The std::string guaranteed to hold a valid IP address
  std::string m_ip_address;
};

///SafeIpAddress guarantees to contain a valid IP address
///and only be of a complete type
struct SafeIpAddress : public IpAddress, boost::noncopyable
{
  ///SafeIpAddress constructor throws an exception when
  ///ip_address is not a valid IP address
  SafeIpAddress(const std::string& ip_address);

  private:
  ///To prevent the following trouble,
  ///cited from http://www.boost.org/libs/utility/checked_delete.html:
  ///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  ///class types to be deleted with a delete-expression.
  ///When the class has a non-trivial destructor, or a class-specific operator
  ///delete, the behavior is undefined. Some compilers issue a warning when an
  ///incomplete type is deleted, but unfortunately, not all do, and programmers
  ///sometimes ignore or disable warnings.
  ~SafeIpAddress()  {}
  ///Template syntax from Herb Sutter. Exceptional C++ style. 2005.
  ///ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(SafeIpAddress*);
};

///Test for equal IP addresses
bool operator==(const IpAddress& lhs,const IpAddress& rhs);
///Test for equal IP addresses
bool operator==(const SafeIpAddress& lhs,const SafeIpAddress& rhs);

} //~namespace ribi

#endif // IPADDRESS_H
