//---------------------------------------------------------------------------
/*
MultiEncranger, encryption and de-encryption tool
Copyright (C) 2010-2011  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolMultiEncranger.htm
//---------------------------------------------------------------------------
//--e --k 1234 --s Makefile --t EncryptedMakefile
//--d --k 1234 --s EncryptedMakefile --t DeencryptedMakefile
//---------------------------------------------------------------------------
#include <fstream>
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
//---------------------------------------------------------------------------
#include "../../Classes/CppEncranger/encranger.h"
//---------------------------------------------------------------------------
///FileExists checks if a certain file exists
///From http://www.richelbilderbeek.nl/CppFileExists.htm
bool FileExists(const std::string& filename)
{
  return boost::filesystem::exists(filename) ;
}
//---------------------------------------------------------------------------
///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& filename)
{
  assert(FileExists(filename)==true);
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
//From http://www.richelbilderbeek.nl/CppSaveContainer.htm
template <class Container>
void SaveContainer(const Container& c, const std::string& filename)
{
  std::ofstream f(filename.c_str());
  std::copy(c.begin(),c.end(),std::ostream_iterator<typename Container::value_type>(f,"\n"));
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  boost::program_options::options_description desc("MultiEncranger options");
  int key = 0;
  std::string source_filename = "source.txt";
  std::string target_filename = "source.txt";
  desc.add_options()
    ("deencrypt,d",
      "de-encrypt source file to target file")
    ("encrypt,e",
      "encrypt source file to target file")
    ("help,h",
      "show this help message")
    ("key,k",
      boost::program_options::value<int>(&key)->default_value(0),
      "(de)encryption key")
    ("source,s",
      boost::program_options::value<std::string>(&source_filename)->default_value("source.txt"),
      "source file name")
    ("target,t",
      boost::program_options::value<std::string>(&target_filename)->default_value("target.txt"),
      "target file name")
    ("version,v",
      "display the version number")
    ;

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) //Note: also includes '--h'
  {
    std::cout << desc << '\n';
    return 0;
  }
  if (vm.count("version")) //Note: also includes '--v'
  {
    std::cout << Encranger::GetVersion() << '\n';
    return 0;
  }

  const Encranger e(key);
  if (vm.count("deencrypt")) //Note: also includes '--d'
  {
    std::vector<std::string> v = FileToVector(source_filename);
    BOOST_FOREACH(std::string& s,v)
    {
      s = e.Deencrypt(s);
    }
    SaveContainer(v,target_filename);
  }
  if (vm.count("encrypt")) //Note: also includes '--e'
  {
    std::vector<std::string> v = FileToVector(source_filename);
    BOOST_FOREACH(std::string& s,v)
    {
      s = e.Encrypt(s);
    }
    SaveContainer(v,target_filename);
  }
}
//---------------------------------------------------------------------------
