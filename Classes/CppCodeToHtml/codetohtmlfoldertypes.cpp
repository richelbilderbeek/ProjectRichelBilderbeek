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
#include "codetohtmlfoldertypes.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>

#include "fileio.h"
#include "trace.h"
#include "codetohtmlfoldertype.h"
#pragma GCC diagnostic pop

ribi::c2h::FolderType ribi::c2h::FolderTypes::DeduceFolderType(const std::string& folder_name)
{
  assert(fileio::FileIo().IsFolder(folder_name));

  const std::vector<std::string> files {
    fileio::FileIo().GetFilesInFolder(folder_name)
  };

  //Search for pro or cppfiles
  {
    //Copy all filenames matching the regex in the resulting std::vector
    const int n_pro_files {
      std::count_if(files.begin(),files.end(),
        [](const std::string& s)
        {
          static const boost::xpressive::sregex pro_file_regex {
            boost::xpressive::sregex::compile(".*\\.(pro)\\>")
          };
          boost::xpressive::smatch what;
          return boost::xpressive::regex_match(s, what, pro_file_regex);
        }
      )
    };
    const int n_cpp_files {
      std::count_if(files.begin(),files.end(),
        [](const std::string& s)
        {
          static const boost::xpressive::sregex cpp_file_regex {
            boost::xpressive::sregex::compile(".*\\.(cpp)\\>")
          };
          boost::xpressive::smatch what;
          return boost::xpressive::regex_match(s, what, cpp_file_regex);
        }
      )
    };
    if (n_pro_files + n_cpp_files > 0) return FolderType::pro;
  }

  //Search for foam files
  {
    //Copy all filenames matching the regex in the resulting std::vector
    const int n_foam_files {
      std::count_if(files.begin(),files.end(),
        [](const std::string& s)
        {
          static const boost::xpressive::sregex foam_file_regex {
            boost::xpressive::sregex::compile(".*\\.(foam)\\>")
          };
          boost::xpressive::smatch what;
          return boost::xpressive::regex_match(s, what, foam_file_regex);
        }
      )
    };
    if (n_foam_files > 0) return FolderType::foam;
  }
  return FolderType::txt;
}
