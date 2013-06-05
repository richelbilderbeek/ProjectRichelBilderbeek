//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrichelbilderbeekgalleryresources.h"

#include <cassert>

#include <boost/filesystem.hpp>

#include "richelbilderbeekprogram.h"
#include "trace.h"

//Must be #included after Wt header files
#include <QFile>

namespace RichelBilderbeek {

QtResources::QtResources()
{
  //Create the obligatory resources
  {
    const std::vector<std::string> files
      =
      {
        GetBackground(),
        GetBep(),
        GetBlack(),
        GetCl(),
        //GetCppBuilder(),
        GetDesktop(),
        GetGreen(),
        //GetLinux(),
        //GetLinuxMacWindows(),
        //GetMac(),
        GetOrange(),
        //GetQt(),
        //GetR(),
        GetRed(),
        GetYellow(),
        GetWeb(),
        GetWindows()
      };
    std::for_each(files.begin(),files.end(),
      [](const std::string& s)
      {
        if (!boost::filesystem::exists(s))
        {
          const std::string filename = ":/images/" + s;
          QFile f(filename.c_str());
          f.copy(s.c_str());
          if (!boost::filesystem::exists(s)) { TRACE(s); }
          assert(boost::filesystem::exists(s));
        }
        if (!boost::filesystem::exists(s)) { TRACE(s); }
        assert(boost::filesystem::exists(s));
      }
    );
  }
  //Try to create the screenshots
  {
    const std::vector<boost::shared_ptr<RichelBilderbeek::Program> > ps = RichelBilderbeek::Program::GetAllPrograms();

    std::vector<std::string> files;
    std::for_each(ps.begin(),ps.end(),
      [&files](const boost::shared_ptr<RichelBilderbeek::Program>& p)
      {
        if (!p->GetFilenameConsole().empty()) files.push_back(p->GetFilenameConsole());
        if (!p->GetFilenameDesktop().empty()) files.push_back(p->GetFilenameDesktop());
        if (!p->GetFilenameDesktopWindowsOnly().empty()) files.push_back(p->GetFilenameDesktopWindowsOnly());
        if (!p->GetFilenameWeb().empty()) files.push_back(p->GetFilenameWeb());
      }
    );

    std::for_each(files.begin(),files.end(),
      [](const std::string& s)
      {
        if (!boost::filesystem::exists(s))
        {
          const std::string filename = ":/images/" + s;
          QFile f(filename.c_str());
          f.copy(s.c_str());
          if (!boost::filesystem::is_regular_file(s)) { TRACE(s); }
          assert(boost::filesystem::is_regular_file(s)
            && "Must add the traced resource to Projects/RichelBilderbeekNl/qtrichelbildeekgalleryresources.qrc");
        }
        if (!boost::filesystem::is_regular_file(s)) { TRACE(s); }
        assert(boost::filesystem::is_regular_file(s));
      }
    );
  }
}

const std::string QtResources::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtResources::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-02-19: Version 1.0: initial version");
  return v;
}

} //~namespace RichelBilderbeek

