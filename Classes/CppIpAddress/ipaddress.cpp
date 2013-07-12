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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "ipaddress.h"

#include <stdexcept>

#include <boost/regex.hpp>

IpAddress::IpAddress(const std::string& ip_address)
{
  Set(ip_address);
}

const std::string IpAddress::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> IpAddress::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-08: version 1.0: initial version");
  return v;
}

void IpAddress::Set(const std::string& ip_address)
{
  const boost::regex regex_ip_address("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
  if(!boost::regex_match(ip_address,regex_ip_address))
  {
    throw std::logic_error("Invalid IP address");
  }
  m_ip_address = ip_address;
}

SafeIpAddress::SafeIpAddress(const std::string& ip_address)
  : IpAddress(ip_address)
{
}

bool operator==(const IpAddress& lhs,const IpAddress& rhs)
{
  return lhs.Get() == rhs.Get();
}

bool operator==(const SafeIpAddress& lhs,const SafeIpAddress& rhs)
{
  return lhs.Get() == rhs.Get();
}

