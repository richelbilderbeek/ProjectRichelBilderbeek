#include "newickutils.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "fileio.h"

const std::string NewickUtils::sm_newick_utils_path{"../../Libraries/newick_utils/src"};

NewickUtils::NewickUtils()
{
  #ifndef NDEBUG
  Test();
  #endif
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  if (!ribi::fileio::FileIo().IsRegularFile(executable))
  {
    std::stringstream s;
    s
      << "Error: nw_display executable '" << executable << "' not found\n"
      << "Please change the path\n"
    ;
    throw std::logic_error(s.str().c_str());
  }

}

void NewickUtils::Display(const std::string& newick)
{
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  assert(ribi::fileio::FileIo().IsRegularFile(executable) && "Checked in constructor");
  const std::string cmd{"echo \""+ newick + "\" | " + executable +" -"};
  std::system(cmd.c_str());
}

///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
std::vector<std::string> NewickUtils::FileToVector(
  const std::string& filename
) const noexcept
{
  assert(ribi::fileio::FileIo().IsRegularFile(filename));
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

std::vector<std::string> NewickUtils::GetPhylogeny(const std::string& newick)
{
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  assert(ribi::fileio::FileIo().IsRegularFile(executable) && "Checked in constructor");
  const std::string tmp_filename{
    ribi::fileio::FileIo().GetTempFileName(".txt")
  };
  assert(!ribi::fileio::FileIo().IsRegularFile(tmp_filename));
  const std::string cmd{"echo \""+ newick + "\" | " + executable +" - > " + tmp_filename};
  std::system(cmd.c_str());

  //Result
  const std::vector<std::string> v{
    FileToVector(tmp_filename)
  };

  //Clean up
  ribi::fileio::FileIo().DeleteFile(tmp_filename);

  return v;
}

#ifndef NDEBUG
void NewickUtils::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //GetPhylogeny
  {
    const std::string newick{"(1,2);"};
    std::vector<std::string> v{NewickUtils().GetPhylogeny(newick)};
    assert(!v.empty());
  }
}
#endif
