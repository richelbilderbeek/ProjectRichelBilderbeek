//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012 Richel Bilderbeek

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
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/program_options.hpp>

#include "trace.h"
#include "richelbilderbeekgallerymenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char **argv)
{
  START_TRACE();

  // Declare the supported options.
  boost::program_options::options_description d("Allowed options for RichelBilderbeekGalleryConsole");

  d.add_options()
      ("about","displays the 'About' information")
      ("gallery","creates the Richel Bilderbeek's gallery web pages")
      ("help","produce this help message")
      ("status","creates the Richel Bilderbeek's program status web page")
      ("version","displays the version")
       ;

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("help"))
  {
    std::cout << d << "\n";
    return 0;
  }

  if (m.count("about"))
  {
    std::cout << ribi::RichelBilderbeek::GalleryMenuDialog::GetAbout() << "\n";
    return 0;
  }

  if (m.count("version"))
  {
    std::cout << ribi::RichelBilderbeek::GalleryMenuDialog::GetVersion() << "\n";
    return 0;
  }

  if (m.count("gallery"))
  {
    {
      const std::vector<std::string> v = ribi::RichelBilderbeek::GalleryMenuDialog::CreateHtmlClassGallery();
      std::ofstream f("CppClassGallery.htm");
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
    {
      const std::vector<std::string> v = ribi::RichelBilderbeek::GalleryMenuDialog::CreateHtmlGameGallery();
      std::ofstream f("GameGallery.htm");
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
    {
      const std::vector<std::string> v = ribi::RichelBilderbeek::GalleryMenuDialog::CreateHtmlProjectGallery();
      std::ofstream f("ProjectGallery.htm");
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
    {
      const std::vector<std::string> v = ribi::RichelBilderbeek::GalleryMenuDialog::CreateHtmlToolGallery();
      std::ofstream f("ToolGallery.htm");
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
    return 0;
  }

  if (m.count("status"))
  {
    {
      const std::vector<std::string> v = ribi::RichelBilderbeek::GalleryMenuDialog::CreateHtmlStatus();
      std::ofstream f("CppRichelBilderbeekStatus.htm");
      std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
    }
    return 0;
  }

  //Display the help
  std::cout << d << "\n";
}

