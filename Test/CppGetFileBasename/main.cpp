#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/filesystem.hpp>
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

const std::string GetFileBasenameBoostFilesystem(const std::string& filename)
{
  return boost::filesystem::basename(filename);
}

const std::string GetFileBasenameBoostXpressive(const std::string& filename)
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "((.*)(/|\\\\))?([A-Za-z]*)((\\.)([A-Za-z]*))?" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[4];
  }

  return "";
}

int main()
{
  //Tests for easy copy-paste
  assert(GetFileBasenameBoostXpressive("") == std::string(""));
  assert(GetFileBasenameBoostXpressive("tmp.txt") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("tmp") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("MyFolder/tmp") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("MyFolder/tmp.txt") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("MyFolder\\tmp.txt") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("MyFolder/MyFolder/tmp") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
  assert(GetFileBasenameBoostXpressive("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));

  //Same tests again...
  for (auto f: {GetFileBasenameBoostFilesystem, GetFileBasenameBoostXpressive } )
  {
    assert(f("") == std::string(""));
    assert(f("tmp.txt") == std::string("tmp"));
    assert(f("tmp") == std::string("tmp"));
    assert(f("MyFolder/tmp") == std::string("tmp"));
    assert(f("MyFolder/tmp.txt") == std::string("tmp"));
    assert(f("MyFolder\\tmp.txt") == std::string("tmp"));
    assert(f("MyFolder/MyFolder/tmp") == std::string("tmp"));
    assert(f("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
    assert(f("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));
  }
}
