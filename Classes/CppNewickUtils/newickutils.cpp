#include "newickutils.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "fileio.h"
#include "trace.h"
#include "phylogeny_r.h"

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

std::string NewickUtils::DropExtinct(const std::string& newick) const
{
  return PhylogenyR().DropExtict(newick);
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

void NewickUtils::NewickToPhylogeny(
  std::string newick,
  const std::string& filename,
  const GraphicsFormat graphics_format,
  const bool plot_fossils
) const
{
  assert(graphics_format == GraphicsFormat::svg);
  if (plot_fossils == false)
  {
    newick = DropExtinct(newick);
  }
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  assert(ribi::fileio::FileIo().IsRegularFile(executable) && "Checked in constructor");
  const std::string cmd{"echo \""+ newick + "\" | " + executable +" - -s > " + filename};
  std::system(cmd.c_str());
  assert(ribi::fileio::FileIo().IsRegularFile(filename));
}

