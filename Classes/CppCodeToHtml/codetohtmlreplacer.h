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
#ifndef CODETOHTMLREPLACER_H
#define CODETOHTMLREPLACER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include "codetohtmlfiletype.h"
#include "codetohtmlfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace c2h {

///The class that does text to HTML conversion
///Stores the re
struct Replacer
{
  Replacer();

  ///Convert text to its HTML equivalent
  std::vector<std::string> ToHtml(
    const std::vector<std::string>& text,
    const FileType file_type
  ) noexcept;

  private:

  ///The C++ replacements
  static boost::scoped_ptr<const Replacements> m_replacements_cpp;

  ///The .pro file replacements
  static boost::scoped_ptr<const Replacements> m_replacements_pro;

  ///The text file replacements
  static boost::scoped_ptr<const Replacements> m_replacements_txt;

  ///CreateCppReplacements creates the (many) replacements when
  ///code is converted to HTML. It uses all the replacements from a .pro file
  static const std::vector<std::pair<std::string,std::string> > CreateCppReplacements() noexcept;

  ///CreateProFileReplacements creates the replacements when
  ///a Qt project file is converted to HTML
  static const std::vector<std::pair<std::string,std::string> > CreateProReplacements() noexcept;

  ///Get the C++ replacements
  ///Lazily create these
  static const Replacements& GetReplacementsCpp();

  ///Get the .pro file replacements
  ///Lazily create these
  static const Replacements& GetReplacementsPro();

  ///Get the text file replacements
  ///Lazily create these
  static const Replacements& GetReplacementsTxt();

  ///Replace all instances in a std::string by the replacements
  static std::string MultiReplace(
    const std::string& line,
    const std::vector<std::pair<std::string,std::string> >& replacements);

  ///Replace all occurrences of replaceWhat by replaceWithWhat in a string
  static std::string ReplaceAll(
    std::string s,
    const std::string& replaceWhat,
    const std::string& replaceWithWhat);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLREPLACER_H
