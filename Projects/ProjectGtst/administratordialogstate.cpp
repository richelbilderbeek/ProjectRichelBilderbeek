//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011 Richel Bilderbeek

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
#include <cassert>
#include <fstream>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
//---------------------------------------------------------------------------
#include "all_parameters.h"
#include "all_serverstates.h"
#include "administrator.h"
#include "serverstatechooseaction.h"
#include "serverstatefinished.h"
#include "serverstateviewresultsgroup.h"
#include "serverstatewaiting.h"
#include "stopwatch.h" //In the precompiled header
#include "administratordialog.h"
#include "administratordialogstate.h"
//---------------------------------------------------------------------------
ribi::gtst::AdministratorDialogState::AdministratorDialogState(
  Server * const server,
  AdministratorDialog * const dialog)
  : m_dialog(dialog),
    m_server(server)
{
  assert(m_dialog);
  assert(m_server);
}
//---------------------------------------------------------------------------
///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> ribi::gtst::AdministratorDialogState::FileToVector(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
const std::vector<std::string> ribi::gtst::AdministratorDialogState::GetFilesInFolder(const std::string& folder)
{
  std::vector<std::string> v;

  const boost::filesystem::path my_folder
    = boost::filesystem::system_complete(
        boost::filesystem::path(folder));

  if (!boost::filesystem::is_directory(my_folder)) return v;

  const boost::filesystem::directory_iterator j;
  for ( boost::filesystem::directory_iterator i(my_folder);
        i != j;
        ++i)
  {
    if ( boost::filesystem::is_regular_file( i->status() ) )
    {
      const std::string filename = i->path().filename().string();
      //const std::string full_filename = folder + "/" + filename;
      v.push_back(filename);
    }
  }
  return v;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetTextFilesInFolder.htm
const std::vector<std::string> ribi::gtst::AdministratorDialogState::GetTextFilesInFolder(const std::string& folder)
{
  //Get all filenames
  const std::vector<std::string> v = GetFilesInFolder(folder);

  //Create the regex for a text file
  const boost::regex txt_file_regex(".*\\.txt\\z");

  //Create the resulting std::vector
  std::vector<std::string> w;

  //Copy all filenames matching the regex in the resulting std::vector
  std::copy_if(v.begin(),v.end(),
    std::back_inserter(w),
    [txt_file_regex](const std::string& s)
    {
      return boost::regex_match(s,txt_file_regex);
    }
  );
  return w;
}
//---------------------------------------------------------------------------
bool ribi::gtst::AdministratorDialogState::IsLoggedIn() const
{
  assert(GetDialog() && "Assume the parent can be read");
  return GetDialog()->CanGetAdministrator();
}
//---------------------------------------------------------------------------
