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
  //NewickToPhylogeny as SVG of extinct and extant species
  {
    const std::string temp_svg_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_svg_filename,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    assert(ribi::fileio::FileIo().IsRegularFile(temp_svg_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename);
  }
  //NewickToPhylogeny as PNG of extinct and extant species
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const bool plot_fossils{false};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      plot_fossils
    );
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());
  }
  //NewickToPhylogeny as PNG of extant species
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      plot_fossils
    );
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
  //NewickToLttPlot
  {
    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToLttPlot(newick,temp_png_filename,GraphicsFormat::png);
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());
  }
  {
    assert(
      PhylogenyR().DropExtict(
        "(L:1,(((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):1,(GD:1,ID:1):1,BD:1):3,(AC:1,EC:1):1,(((TC:1,FD:2):1,QC:1,RC:1):1,((((AE:1,BE:1):1,(WD:1,YD:1):1):1,HD:1):2,MC:1):1):1):3);"
      ) == "((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):4,((AE:1,BE:1):1,(WD:1,YD:1):1):5);"
    );
  }
}
#endif

