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
#ifndef CODETOHTMLREPLACEMENTS_H
#define CODETOHTMLREPLACEMENTS_H

#include <string>
#include <vector>

///\brief
///Contains all code replacements
///
///All code replacements have the following order:
///-m_initial_replacements: converts '&' to '[AMPERSAND]'
///-m_replacements: the replacements it is about
///-m_end_replacements: converts '[AMPERSAND]' back to '&'
///
///m_all_replacements contains all replacements as a single std::vector
struct CodeToHtmlReplacements
{
  CodeToHtmlReplacements(const std::vector<std::pair<std::string,std::string> >& replacements);
  CodeToHtmlReplacements(const CodeToHtmlReplacements&) = delete;
  CodeToHtmlReplacements& operator=(const CodeToHtmlReplacements&) = delete;

  const std::vector<std::pair<std::string,std::string> >& Get() const { return m_replacements; }

  private:
  ///The important replacements
  const std::vector<std::pair<std::string,std::string> > m_replacements;

  private:
  static const std::vector<std::pair<std::string,std::string> > CreateAllReplacements(
    const std::vector<std::pair<std::string,std::string> >& replacements);
  static const std::vector<std::pair<std::string,std::string> > CreateEndReplacements();
  static const std::vector<std::pair<std::string,std::string> > CreateInitialReplacements();
};

#endif // CODETOHTMLREPLACEMENTS_H
