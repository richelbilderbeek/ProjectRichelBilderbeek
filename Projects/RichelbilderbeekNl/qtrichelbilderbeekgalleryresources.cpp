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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtrichelbilderbeekgalleryresources.h"

#include <cassert>
#include <fstream>

#include <QFile>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::RichelBilderbeek::QtResources::QtResources()
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
        if (!QFile::exists(s.c_str()))
        {
          const std::string filename = ":/images/" + s;
          QFile f(filename.c_str());
          f.copy(s.c_str());
          if (!QFile::exists(s.c_str())) { TRACE(s); }
          assert(QFile::exists(s.c_str()));
        }
        if (!QFile::exists(s.c_str())) { TRACE(s); }
        assert(QFile::exists(s.c_str()));
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
      [this](const std::string& s)
      {
        if (!QFile::exists(s.c_str()))
        {
          const std::string filename = ":/images/" + s;
          QFile f(filename.c_str());
          f.copy(s.c_str());
          if (!IsRegularFile(s)) { TRACE(s); }
          assert(IsRegularFile(s)
            && "Must add the traced resource to Projects/RichelBilderbeekNl/qtrichelbildeekgalleryresources.qrc");
        }
        if (!IsRegularFile(s)) { TRACE(s); }
        assert(IsRegularFile(s));
      }
    );
  }
}

const std::string ribi::RichelBilderbeek::QtResources::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::RichelBilderbeek::QtResources::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-02-19: Version 1.0: initial version");
  return v;
}

bool ribi::RichelBilderbeek::QtResources::IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}
