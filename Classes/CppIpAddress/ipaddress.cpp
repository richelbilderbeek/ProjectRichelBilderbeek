//---------------------------------------------------------------------------
/*
IpAddress, class for containing an IP address
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
//From http://www.richelbilderbeek.nl/CppIpAddress.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "ipaddress.h"

#include <stdexcept>

#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

ribi::IpAddress::IpAddress(const std::string& ip_address)
  : m_ip_address{ip_address}
{
  const boost::xpressive::sregex regex_ip_address
    = boost::xpressive::sregex::compile("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
  if(!boost::xpressive::regex_match(ip_address,regex_ip_address))
  {
    throw std::logic_error("Invalid IP address");
  }
}

std::string ribi::IpAddress::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::IpAddress::GetVersionHistory() noexcept
{
  return {
    "2011-06-08: version 1.0: initial version",
    "2013-09-02: version 1.1: replaced Boost.Regex by Boost.Xpressive"
  };
}

ribi::SafeIpAddress::SafeIpAddress(const std::string& ip_address) noexcept
  : m_ip_address(ip_address)
{

}

bool ribi::operator==(const IpAddress& lhs,const IpAddress& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

bool ribi::operator==(const SafeIpAddress& lhs,const SafeIpAddress& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}
