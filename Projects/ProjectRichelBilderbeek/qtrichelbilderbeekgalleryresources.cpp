//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtrichelbilderbeekgalleryresources.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include <QFile>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtResources::QtResources()
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
    for (const std::string& s: files)
    {
      if (!fileio::FileIo().IsRegularFile(s.c_str()))
      {
        const std::string filename = ":/images/" + s;
        QFile f(filename.c_str());
        f.copy(s.c_str());
        if (!QFile::exists(s.c_str()))
        {
          TRACE("ERROR: FILE NOT FOUND:");
          TRACE(s);
          TRACE("SOLUTION: add file to /Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.qrc");
          const std::string error { "QtResources::QtResources: file not found: '" + s + '\'' };
          throw std::logic_error(s.c_str());
        }
        assert(QFile::exists(s.c_str()));
      }
      if (!fileio::FileIo().IsRegularFile(s)) { TRACE(s); }
      assert(fileio::FileIo().IsRegularFile(s));
    }
  }
  //Try to create the screenshots
  {
    const std::vector<boost::shared_ptr<Program>> ps = Program::GetAllPrograms();

    std::vector<std::string> files;
    std::for_each(ps.begin(),ps.end(),
      [&files](const boost::shared_ptr<Program>& p)
      {
        if (!p->GetFilenameConsole().empty()) files.push_back(p->GetFilenameConsole());
        if (!p->GetFilenameDesktop().empty()) files.push_back(p->GetFilenameDesktop());
        if (!p->GetFilenameDesktopWindowsOnly().empty()) files.push_back(p->GetFilenameDesktopWindowsOnly());
        if (!p->GetFilenameWeb().empty()) files.push_back(p->GetFilenameWeb());
      }
    );

    for(const std::string& s: files)
    {
      if (!fileio::FileIo().IsRegularFile(s.c_str()))
      {
        const std::string filename = ":/images/" + s;
        QFile f(filename.c_str());
        f.copy(s.c_str());
        if (!fileio::FileIo().IsRegularFile(s)) { TRACE(s); }
        assert(fileio::FileIo().IsRegularFile(s)
          && "Must add the traced resource to Projects/RichelBilderbeekNl/qtrichelbildeekgalleryresources.qrc");
      }
      if (!fileio::FileIo().IsRegularFile(s)) { TRACE(s); }
      assert(fileio::FileIo().IsRegularFile(s));
    }
  }
}

std::string ribi::QtResources::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtResources::GetVersionHistory() noexcept
{
  return {
    "2012-02-19: Version 1.0: initial version",
    "2013-09-20: Version 1.1: correct use of noexcept",
    "2013-11-19: Version 1.2: use of ribi::fileio"
  };
}
