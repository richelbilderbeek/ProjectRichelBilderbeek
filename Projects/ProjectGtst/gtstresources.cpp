//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <QFile>

#include "fileio.h"
#include "gtstresources.h"
#include "trace.h"

///#include Qt files after Wt files
#pragma GCC diagnostic pop


ribi::gtst::Resources::Resources()
{
  TRACE_FUNC();
  //Create the default parameters file
  {
    const std::string filename  = "wt.css";

    if (!fileio::FileIo().IsRegularFile(filename))
    {
      SaveStylesheet();
    }
    assert(fileio::FileIo().IsRegularFile(filename));
  }
  const std::vector<std::string> image_names
    =
  {
    //GetImageFilenameBackground(),
    GetImageFilenameCycle(),
    GetImageFilenameExperiment(),
    GetImageFilenameGroups(),
    GetImageFilenameParticipantDialogAssignPayoff(),
    GetImageFilenameParticipantDialogChat(),
    GetImageFilenameParticipantDialogChooseAction(),
    GetImageFilenameParticipantDialogFinished(),
    GetImageFilenameParticipantDialogGroupAssign(),
    GetImageFilenameParticipantDialogGroupReAssign(),
    GetImageFilenameParticipantDialogLoggedIn(),
    GetImageFilenameParticipantDialogNotLoggedIn(),
    GetImageFilenameParticipantDialogViewResultsGroup(),
    GetImageFilenameParticipantDialogViewResultsVoting(),
    GetImageFilenameParticipantDialogVoting(),
    GetImageFilenamePeriod()
  };
  std::for_each(image_names.begin(),image_names.end(),
    [](const std::string& filename)
    {
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        QFile f( (std::string(":/images/") + filename).c_str() );
        f.copy(filename.c_str());
        if (!fileio::FileIo().IsRegularFile(filename))
        {
          const std::string s = "File not found: " + filename;
          std::cerr << s << '\n';
          std::clog << s << '\n';
          std::cout << s << '\n';
        }
      }
      assert(fileio::FileIo().IsRegularFile(filename));
    }
  );
}

///Create the CSS for this application
const std::vector<std::string> ribi::gtst::Resources::CreateStylesheet() const
{
  std::vector<std::string> v;

  v.push_back("*");
  v.push_back("{");
  v.push_back("  font-family:\"Verdana\",\"Arial\"\"Sans-serif\";");
  v.push_back("  font-size:large;");
  v.push_back("}");
  v.push_back("");
  v.push_back("body");
  v.push_back("{");
  //v.push_back("  background-image:url('Background.png');");
  //v.push_back("  background-position:center center;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".read_only_textarea");
  v.push_back("{");
  //v.push_back("  background-color:#bbbbbb;"); //Gray
  v.push_back("  background-color:transparent;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".title");
  v.push_back("{");
  v.push_back("  font-weight:bold;");
  v.push_back("  font-size:x-large;");
  v.push_back("}");
  v.push_back("");
  v.push_back("table, th, td");
  v.push_back("{");
  v.push_back("  border: 1px solid black;");
  v.push_back("}");
  v.push_back("");
  v.push_back("td");
  v.push_back("{");
  v.push_back("  padding:12px;");
  v.push_back("}");
  v.push_back("");
  //Items in main menu
  v.push_back(".menu * .item");
  v.push_back("{");
  v.push_back("  cursor: pointer; cursor: hand;");
  v.push_back("  font-size:x-large;");
  v.push_back("  color: black;");
  //v.push_back("  background-color:rgb(160,160,160);");
  v.push_back("  padding:12px;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".menu * .itemselected {");
  v.push_back("  font-size:x-large;");
  v.push_back("  font-weight: bold;");
  v.push_back("  color: blue;");
  //v.push_back("  background-color:rgb(160,160,160);");
  v.push_back("  padding:12px;");
  v.push_back("}");
  v.push_back("");
  v.push_back(".wtwebsitemenu * .item");
  v.push_back("{");
  v.push_back("  cursor: pointer; cursor: hand;");
  v.push_back("  font-size:x-large;");
  v.push_back("  color: black;");
  v.push_back("  padding:4px;");
  //v.push_back("  background-color:rgb(160,160,160);");
  v.push_back("  border:0px");
  v.push_back("}");
  v.push_back("");
  v.push_back(".wtwebsitemenu * .itemselected {");
  v.push_back("  font-size:x-large;");
  v.push_back("  font-weight:bold;");
  v.push_back("  color: blue;");
  v.push_back("  padding:4px;");
  //v.push_back("  background-color:rgb(196,196,196);");
  v.push_back("  border:0px");
  v.push_back("}");
  return v;
}

///Save the stylesheet for this application to file
void ribi::gtst::Resources::SaveStylesheet() const
{
  const std::vector<std::string> v = CreateStylesheet();
  std::ofstream f("wt.css");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
}

