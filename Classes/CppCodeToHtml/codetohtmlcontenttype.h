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
#ifndef CODETOHTMLCONTENTTYPE_H
#define CODETOHTMLCONTENTTYPE_H

#include <string>
#include <vector>

namespace c2h {

///The types of content
enum class ContentType
{
  code_snippet, //When content is not loaded from a file
  cpp,          //.cpp file
  pri,          //.pri file
  pro,          //.pro file
  py,           //.py file
  sh,           //.sh file
  txt,          //.txt file
  other,        //File with another extension
  n_types       //Used for debugging, keep it as last element
};

bool CanStrToContentType(const std::string& s) noexcept;
const std::string ContentTypeToStr(const ContentType t);
const std::vector<ContentType> GetAllContentTypes() noexcept;
ContentType StrToContentType(const std::string& s);

} //~namespace CodeToHtml

#endif // CODETOHTMLCONTENTTYPE_H
