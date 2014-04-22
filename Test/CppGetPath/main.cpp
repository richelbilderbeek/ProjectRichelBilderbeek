#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

///Returns the path of a filename
///From http://www.richelbilderbeek.nl/CppGetPath.htm
const std::string GetPathStl(const std::string& filename)
{
  const int a = filename.rfind("\\",filename.size());
  const int b = filename.rfind("/",filename.size());
  const int i = std::max(a,b);
  assert(i < static_cast<int>(filename.size()));
  return filename.substr(0,i);
}

///Returns the path of a filename
//From http://www.richelbilderbeek.nl/CppGetPath.htm
const std::string GetPathBoostFilesystem(const std::string& filename)
{
  return boost::filesystem::path(filename).parent_path().string();
}

///Returns the path of a filename
///From http://www.richelbilderbeek.nl/CppGetPath.htm
const std::string GetPathBoostXpressive(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)(\\\\|/)([A-Za-z\\._]*)" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[1];
  }

  return "";
}

#include <iostream>

int main()
{
  #ifdef _WIN32
  assert(GetPathBoostFilesystem("C:\\any_path\\any_file.cpp")=="C:\\any_path");
  #else
  assert(GetPathBoostFilesystem("/any_path/any_file.cpp")=="/any_path");
  #endif

  assert(GetPathBoostXpressive("C:\\any_path\\any_file.cpp")=="C:\\any_path");
  assert(GetPathStl("C:\\any_path\\any_file.cpp")=="C:\\any_path");

  assert(GetPathBoostXpressive("/any_path/any_file.cpp")=="/any_path");
  assert(GetPathStl("/any_path/any_file.cpp")=="/any_path");

  for (const auto f: { GetPathStl, GetPathBoostFilesystem, GetPathBoostXpressive} )
  {
    #ifdef _WIN32
    assert(f("C:\\any_path\\any_file.cpp")=="C:\\any_path");
    assert(f("any_path\\any_file.cpp")=="any_path");
    #else
    assert(f("/any_path/any_file.cpp")=="/any_path");
    #endif
  }
}
