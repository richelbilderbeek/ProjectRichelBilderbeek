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
#ifndef CODETOHTMLINFO_H
#define CODETOHTMLINFO_H

#include <map>
#include <string>
#include <vector>
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>

#include "codetohtml.h"

namespace ribi {
namespace c2h {

///Defines the info of the resulting HTML page
///Info is a heavy class due to the map connecting a page name and its info
struct Info
{
  explicit Info();
  Info(const Info&) = delete;
  Info& operator=(const Info&) = delete;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  static void TestIfAllCreatedPagesAreValid() noexcept;

  std::vector<std::string> ToHtml(const std::string page_name) const;

  private:
  ~Info() noexcept {}
  friend void boost::checked_delete<>(Info*);
  friend void boost::checked_delete<>(const Info*);

  ///For every page name (the key), contains the HTML info (the value)
  const std::map<std::string,std::vector<std::string> > m_page_info;

  ///Create, for every page name (the key), the HTML info (the value)
  ///The purpose of this is to be able to check every HTML info
  ///for validity
  static std::map<std::string,std::vector<std::string> > CreatePageInfo();

  //From http://www.richelbilderbeek.nl/CppGetTime.htm
  static std::string GetTime() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif


};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLINFO_H
