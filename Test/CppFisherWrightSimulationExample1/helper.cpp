#include "helper.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/xpressive/xpressive.hpp>

template <class Container>
std::string ContainerToStrImpl(const Container& c, const std::string& seperator)
{
  std::stringstream s;
  std::copy(c.begin(),c.end(),
    std::ostream_iterator<typename Container::value_type>(s,seperator.c_str()));
  return s.str();
}

Helper::Helper() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string Helper::ContainerToStr(
  const std::vector<std::string>& s,
  const std::string& seperator
) const noexcept
{
  return ContainerToStrImpl(s,seperator);
}


std::map<std::string,int> Helper::CreateSortedTally(
  const std::vector<std::string>& v
) const noexcept
{
  std::map<std::string,int> m;
  for (const std::string& s: v)
  {
    if (m.find(s) == m.end())
    {
      m[s] = 1;
    }
    else
    {
      ++m[s];
    }
  }
  return m;
}

std::vector<std::pair<std::string,int>> Helper::CreateTally(
  const std::vector<std::string>& v
) const noexcept
{
  std::vector<std::pair<std::string,int>> w;
  for (const std::string& s: v)
  {
    const auto iter = std::find_if(std::begin(w),std::end(w),
      [s](const auto& p) { return p.first == s; }
    );

    if (iter == std::end(w))
    {
      w.push_back(std::make_pair(s,1));
    }
    else
    {
      ++((*iter).second);
    }
  }
  return w;
}

///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
std::vector<std::string> Helper::FileToVector(
  const std::string& filename
) const noexcept
{
  assert(IsRegularFileStl(filename));
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


std::string Helper::GetFileBasenameBoostFilesystem(const std::string& filename) const noexcept
{
  return boost::filesystem::basename(filename);
}

std::string Helper::GetFileBasenameBoostXpressive(const std::string& filename) const noexcept
{
  const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "((.*)(/|\\\\))?([0-9A-Za-z_]*)((\\.)([A-Za-z]*))?" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what, rex ) )
  {
    return what[4];
  }

  return "";
}


///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool Helper::IsRegularFileStl(
  const std::string& filename
) const noexcept
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

#ifndef NDEBUG
void Helper::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  //CreateTally
  {
    const std::vector<std::string> v = { "A"};
    const std::vector<std::pair<std::string,int>> m{Helper().CreateTally(v)};
    assert(m.size() == 1);
    assert(m[0].first == "A");
    assert(m[0].second == 1);
  }
  {
    const std::vector<std::string> v = { "A", "A" };
    const std::vector<std::pair<std::string,int>> m{Helper().CreateTally(v)};
    assert(m.size() == 1);
    assert(m[0].first == "A");
    assert(m[0].second == 2);
  }
  {
    const std::vector<std::string> v = { "A", "B" };
    const std::vector<std::pair<std::string,int>> m{Helper().CreateTally(v)};
    assert(m.size() == 2);
    assert(m[0].first == "A");
    assert(m[0].second == 1);
    assert(m[1].first == "B");
    assert(m[1].second == 1);
  }
  {
    const std::vector<std::string> v = { "B", "A", "B" };
    const std::vector<std::pair<std::string,int>> m{Helper().CreateTally(v)};
    assert(m.size() == 2);
    assert(m[0].first == "B");
    assert(m[0].second == 2);
    assert(m[1].first == "A");
    assert(m[1].second == 1);
  }
  {
    assert(Helper().GetFileBasenameBoostFilesystem("") == std::string(""));
    assert(Helper().GetFileBasenameBoostFilesystem("tmp.txt") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostFilesystem("test_output.fas") == std::string("test_output"));
    assert(Helper().GetFileBasenameBoostFilesystem("test_output_0.fas") == std::string("test_output_0"));
    assert(Helper().GetFileBasenameBoostFilesystem("tmp") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostFilesystem("MyFolder/tmp") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostFilesystem("MyFolder/tmp.txt") == std::string("tmp"));
    //assert(Helper().GetFileBasenameBoostFilesystem("MyFolder\\tmp.txt") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostFilesystem("MyFolder/MyFolder/tmp") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostFilesystem("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
    //assert(Helper().GetFileBasenameBoostFilesystem("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));

    assert(Helper().GetFileBasenameBoostXpressive("") == std::string(""));
    assert(Helper().GetFileBasenameBoostXpressive("tmp.txt") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("test_output.fas") == std::string("test_output"));
    assert(Helper().GetFileBasenameBoostXpressive("test_output_0.fas") == std::string("test_output_0"));
    assert(Helper().GetFileBasenameBoostXpressive("tmp") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("MyFolder/tmp") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("MyFolder/tmp.txt") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("MyFolder\\tmp.txt") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("MyFolder/MyFolder/tmp") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("MyFolder/MyFolder/tmp.txt") == std::string("tmp"));
    assert(Helper().GetFileBasenameBoostXpressive("MyFolder/MyFolder\\tmp.txt") == std::string("tmp"));
  }
}
#endif
