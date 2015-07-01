//---------------------------------------------------------------------------
/*
ndsmake, tool to generate NDS makefile from Qt Creator project file
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
// From http://www.richelbilderbeek.nl/ToolNdsmake.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "createholymakefile.h"
#include "createmakefile.h"
#include "ndsmake.h"
#include "qtcreatorprofile.h"

int main(int argc, char* argv[])
{
  if ( argc!= 2
    || std::string(argv[1]) == "-help"
    || std::string(argv[1]) == "--help")
  {
    const std::vector<std::string>& v = ribi::Ndsmake::GetHelp();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  if (std::string(argv[1]) == "--history")
  {
    const std::vector<std::string>& v = ribi::Ndsmake::GetHistory();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  if (std::string(argv[1]) == "--licence")
  {
    const std::vector<std::string>& v = ribi::Ndsmake::GetLicence();
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  if (std::string(argv[1]) == "--version")
  {
    std::cout << ribi::Ndsmake::GetVersion() << '\n';
    return 0;
  }
  //Start ndsmake
  const boost::shared_ptr<ribi::Ndsmake> n(new ribi::Ndsmake(argv[0],argv[1]));
  //Copy source files
  std::clog << "Ndsmake cmd: " << n->GetCommand() << '\n';
  std::system(n->GetCommand().c_str());
  //Create makefile and make it
  {
    n->CreateMakefile();
    const std::string s =
      "export DEVKITARM=/opt/devkitpro/devkitARM; "
      "export DEVKITPRO=/opt/devkitpro; "
      "make;";
    std::system(s.c_str());
  }
  //Run the NDS file
  {
    std::system(
      (std::string("desmume ")
      + n->GetTarget()
      + std::string(".nds")).c_str());
  }
}
