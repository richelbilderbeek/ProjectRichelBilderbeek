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
#ifndef CODETOHTMLVERSION_H
#define CODETOHTMLVERSION_H

#include <string>
#include <vector>

namespace ribi {
namespace c2h {

namespace Version
{

///GetBoostVersion returns the version of the current Boost library.
///From http://www.richelbilderbeek.nl/CppGetBoostVersion.htm
std::string GetBoostVersion() noexcept;

#ifndef _WIN32
///GetLubuntuVersion returns the version number of the Lubuntu distribution currently installed.
///From http://www.richelbilderbeek.nl/CppGetLubuntuVersion.htm
std::string GetLubuntuVersion() noexcept;
#endif

#ifndef _WIN32
///GetLubuntuVersionCodename returns the codename of the Lubuntu distribution currently installed.
///From http://www.richelbilderbeek.nl/CppGetLubuntuVersionCodename.htm
std::string GetLubuntuVersionCodename() noexcept;
#endif

///GetGccVersion returns the version number of GCC currently installed.
///From http://www.richelbilderbeek.nl/CppGetGccVersion.htm
std::string GetGccVersion() noexcept;

///GetQtVersion returns the version of the Qt library installed.
///From http://www.richelbilderbeek.nl/CppGetQtVersion.htm
std::string GetQtVersion() noexcept;

#ifndef _WIN32
///GetQtCreatorVersion returns the version Qt Creator currently installed.
///From http://www.richelbilderbeek.nl/CppGetQtCreatorVersion.htm
std::string GetQtCreatorVersion() noexcept;
#endif

///GetStlVersion returns the version number of the GCC STL currently installed.
///From http://www.richelbilderbeek.nl/CppGetStlVersion.htm
std::string GetStlVersion() noexcept;

#ifndef _WIN32
///GetUbuntuVersion returns the version number of the Ubuntu distribution currently installed.
///From http://www.richelbilderbeek.nl/CppGetUbuntuVersion.htm
std::string GetUbuntuVersion() noexcept;
#endif

#ifndef _WIN32
///GetUbuntuVersionCodename returns the codename of the Ubuntu distribution currently installed.
///From http://www.richelbilderbeek.nl/CppGetUbuntuVersionCodename.htm
std::string GetUbuntuVersionCodename() noexcept;
#endif

///GetVirtualBoxVersion returns the version of the currently installed VirtualBox
///From http://www.richelbilderbeek.nl/CppGetVirtualBoxVersion.htm
std::string GetVirtualBoxVersion() noexcept;

///GetWineVersion returns the version of the currently installed Wine
///From http://www.richelbilderbeek.nl/CppGetWineVersion.htm
std::string GetWineVersion() noexcept;

///GetWtVersion returns the version of the currently installed Wt library
///From http://www.richelbilderbeek.nl/CppGetWtVersion.htm
std::string GetWtVersion() noexcept;
}

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLVERSION_H
