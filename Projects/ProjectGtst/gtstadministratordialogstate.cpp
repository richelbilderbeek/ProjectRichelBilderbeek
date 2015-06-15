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
#include <cassert>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/regex.hpp>

#include "fileio.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstadministrator.h"
#include "gtstserverstatechooseaction.h"
#include "gtstserverstatefinished.h"
#include "gtstserverstateviewresultsgroup.h"
#include "gtstserverstatewaiting.h"
#include "stopwatch.h" //In the precompiled header
#include "gtstadministratordialog.h"
#include "gtstadministratordialogstate.h"
#pragma GCC diagnostic pop

ribi::gtst::AdministratorDialogState::AdministratorDialogState(
  Server * const server,
  AdministratorDialog * const dialog)
  : m_dialog(dialog),
    m_server(server)
{
  assert(m_dialog);
  assert(m_server);
}

//From http://www.richelbilderbeek.nl/CppGetTextFilesInFolder.htm
std::vector<std::string> ribi::gtst::AdministratorDialogState::GetTextFilesInFolder(const std::string& folder) noexcept
{
  //Get all filenames
  const std::vector<std::string> v
    = fileio::FileIo().GetFilesInFolder(folder);

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

bool ribi::gtst::AdministratorDialogState::IsLoggedIn() const
{
  assert(GetDialog() && "Assume the parent can be read");
  return GetDialog()->CanGetAdministrator();
}

