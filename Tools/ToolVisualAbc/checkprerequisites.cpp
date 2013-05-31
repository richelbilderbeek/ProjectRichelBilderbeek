//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <fstream>
//---------------------------------------------------------------------------
#include "checkprerequisites.h"
//---------------------------------------------------------------------------
CheckPrerequisites::CheckPrerequisites()
{
  CheckAbc2midi();
  CheckAbcm2ps();
  CheckConvert();
  CheckPlaysound();
}
//---------------------------------------------------------------------------
void CheckPrerequisites::CheckAbc2midi()
{
  std::remove("tmp.txt");
  assert(!FileExists("tmp.txt"));

  const int result
    = std::system("abc2midi > tmp.txt");
  if (result != 0)
  {
    throw std::runtime_error(
      "\'abc2midi\' not not present. "
      "Type \'sudo apt-get install abcmidi\' to install");
  }
  std::remove("tmp.txt");
  assert(!FileExists("tmp.txt"));
}
//---------------------------------------------------------------------------
void CheckPrerequisites::CheckAbcm2ps()
{
  const int result
    = std::system("abcm2ps > tmp.txt");
  if (result != 0)
  {
    throw std::runtime_error(
      "\'abcm2ps\' not not present. "
      "Type \'sudo apt-get install abcm2ps\' to install");
  }

  std::remove("tmp.txt");
  assert(!FileExists("tmp.txt"));
}
//---------------------------------------------------------------------------
void CheckPrerequisites::CheckConvert()
{
  const int result
    = std::system("convert --help > tmp.txt");
  if (result != 0)
  {
    //FileExists("tmp.txt"))
    throw std::runtime_error(
      "\'convert\' not not present. "
      "Type \'sudo apt-get install imagemagick\' to install");
  }
  std::remove("tmp.txt");
  assert(!FileExists("tmp.txt"));
}
//---------------------------------------------------------------------------
void CheckPrerequisites::CheckPlaysound()
{
  const int error
    = std::system("playsound --version > tmp.txt");
  if (!FileExists("tmp.txt"))
  {
    assert(error);
    throw std::runtime_error(
      "\'playsound\' not not present. "
      "Type \'sudo apt-get install libsdl-sound1.2\' to install");
  }
  std::remove("tmp.txt");
  assert(!FileExists("tmp.txt"));
}
//---------------------------------------------------------------------------
///FileExists checks if a certain file exists
///From http://www.richelbilderbeek.nl/CppFileExists.htm
bool CheckPrerequisites::FileExists(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}
//---------------------------------------------------------------------------
