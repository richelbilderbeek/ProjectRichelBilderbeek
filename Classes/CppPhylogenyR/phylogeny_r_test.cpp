#include "phylogeny_r.h"

#include <cassert>

#include "fileio.h"

#ifndef NDEBUG
void PhylogenyR::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //NewickToPhylogenySvg
  {
    const std::string temp_svg_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToPhylogenySvg(newick,temp_svg_filename);
    assert(ribi::fileio::FileIo().IsRegularFile(temp_svg_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename);
  }
  //NewickToPhylogenyPng
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToPhylogenyPng(newick,temp_png_filename);
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());
  }
  //NewickToPhylogenyPng on hard phylogeny
  #ifdef FIX_ISSUE_267
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((ER:1,GR:1):1);"};
    PhylogenyR().NewickToPhylogenyPng(newick,temp_png_filename);
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());
  }
  #endif
}
#endif

