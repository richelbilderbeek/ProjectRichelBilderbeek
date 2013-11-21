//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
#ifndef CODETOHTMLCONTENT_H
#define CODETOHTMLCONTENT_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

#include "codetohtml.h"
#include "codetohtmlfiletype.h"
#include "codetohtmlreplacements.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace c2h {

///File (previous name: Content) contains a piece of content like
///C++ source code, a text file, a .pro file, a .sh file
struct File
{
  ///Convert a file to its HTML equivalent
  ///Deduce the content type from the filename
  File(const std::string& filename);

  ///Convert a file to its HTML equivalent
  ///The content type is given manually
  File(
    const std::string& filename,
    const FileType content_type
  );

  ///Get the HTML version of the file.
  ///The content is created by CreateHtml
  const std::vector<std::string>& GetHtml() const { return m_html; }

  private:
  ~File() noexcept {}
  friend void boost::checked_delete<>(File*);
  friend void boost::checked_delete<>(const File*);

  const std::vector<std::string> m_html;

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

  ///Create the HTML of the file
  static const std::vector<std::string> CreateHtml(
    const std::string& filename,
    const FileType content_type);

  ///Deduce the content type from a filename
  static FileType DeduceFileType(const std::string& filename);

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
  static const std::string MultiReplace(
    const std::string& line,
    const std::vector<std::pair<std::string,std::string> >& replacements);

  ///Replace all occurrences of replaceWhat by replaceWithWhat in a string
  static const std::string ReplaceAll(
    std::string s,
    const std::string& replaceWhat,
    const std::string& replaceWithWhat);

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLCONTENT_H
