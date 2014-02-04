#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

//Returns the extension of a filename
//Assumes that the filename has an extension
//From http://www.richelbilderbeek.nl/CppGetExtension.htm
const std::string GetExtensionStl(const std::string& filename)
{
  const std::size_t i = filename.rfind('.');
  assert(i != std::string::npos && "Filename must contain a dot");
  assert(i != filename.size() - 1 && "Filename must not end with a dot");
  assert(filename[i+1] != '\\' && "Filename must have an extension");
  assert(filename[i+1] != '/' && "Filename must have an extension");
  return filename.substr(i,filename.size());
}


//Returns the extension of a filename
//From http://www.richelbilderbeek.nl/CppGetExtension.htm
const std::string GetExtensionBoostFilesystem(const std::string& filename)
{
  return boost::filesystem::extension(filename);
}

//Returns the extension of a filename
//From http://www.richelbilderbeek.nl/CppGetExtension.htm
const std::string GetExtensionBoostXpressive(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)?(\\.[A-Za-z]*)" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[2];
  }

  return "";
}

#include <iostream>

int main()
{
  assert(GetExtensionStl("test.abc") == ".abc");
  assert(GetExtensionStl("myfolder/test.abc") == ".abc");
  assert(GetExtensionStl("myfolder\\test.abc") == ".abc");
  assert(GetExtensionStl("myfolder/myfolder/test.abc") == ".abc");
  assert(GetExtensionStl("myfolder\\myfolder\\test.abc") == ".abc");

  assert(GetExtensionBoostFilesystem("test.abc") == ".abc");
  assert(GetExtensionBoostFilesystem("myfolder/test.abc") == ".abc");
  assert(GetExtensionBoostFilesystem("myfolder\\test.abc") == ".abc");
  assert(GetExtensionBoostFilesystem("myfolder/myfolder/test.abc") == ".abc");
  assert(GetExtensionBoostFilesystem("myfolder\\myfolder\\test.abc") == ".abc");

  assert(GetExtensionBoostXpressive("test.abc") == ".abc");
  assert(GetExtensionBoostXpressive("myfolder/test.abc") == ".abc");
  assert(GetExtensionBoostXpressive("myfolder\\test.abc") == ".abc");
  assert(GetExtensionBoostXpressive("myfolder/myfolder/test.abc") == ".abc");
  assert(GetExtensionBoostXpressive("myfolder\\myfolder\\test.abc") == ".abc");

  for (auto f: { GetExtensionStl, GetExtensionBoostFilesystem, GetExtensionBoostXpressive} )
  {
    assert(f("test.abc") == ".abc");
    assert(f("myfolder/test.abc") == ".abc");
    assert(f("myfolder\\test.abc") == ".abc");
    assert(f("myfolder/myfolder/test.abc") == ".abc");
    assert(f("myfolder\\myfolder\\test.abc") == ".abc");
  }
}
