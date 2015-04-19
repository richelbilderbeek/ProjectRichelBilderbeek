#include "newickutils.h"

#include <cassert>
#include <fstream>
#include <iostream>
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
  const int error = std::system(cmd.c_str());
  if (error)
  {
    std::clog << __func__ << ": error " << error << '\n';
  }
}

std::string NewickUtils::DropExtinct(const std::string& newick) const
{
  return PhylogenyR().DropExtinct(newick);
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
  const int error = std::system(cmd.c_str());
  if (error)
  {
    std::clog << __func__ << ": error " << error << '\n';
  }

  //Result
  const std::vector<std::string> v{
    ribi::fileio::FileIo().FileToVector(tmp_filename)
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
  if (graphics_format != GraphicsFormat::svg)
  {
    throw std::logic_error("NewickUtils::NewickToPhylogeny: not yet implemented this GraphicsFormat");
  }
  if (plot_fossils == false)
  {
    newick = DropExtinct(newick);
  }
  const std::string executable{sm_newick_utils_path + "/nw_display"};
  assert(ribi::fileio::FileIo().IsRegularFile(executable) && "Checked in constructor");
  const std::string cmd{"echo \""+ newick + "\" | " + executable +" - -s > " + filename};
  const int error = std::system(cmd.c_str());
  if (error)
  {
    std::clog << __func__ << ": error " << error << '\n';
  }
  assert(ribi::fileio::FileIo().IsRegularFile(filename));
}

