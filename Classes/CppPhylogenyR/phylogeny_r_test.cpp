#include "phylogeny_r.h"

#include <cassert>
#include <chrono>

#include "fileio.h"
#include "testtimer.h"
#include "trace.h"
#include "ribi_rinside.h"
#include "RInside.h"

#ifndef NDEBUG
void PhylogenyR::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    auto& r = ribi::Rinside().Get();
    r.parseEvalQ("library(ape)");
    r.parseEvalQ("library(geiger)");
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  ribi::fileio::FileIo f;

  PhylogenyR p;

  if (verbose) { TRACE("NewickToPhylogeny as SVG of extinct and extant species"); }
  {
    const std::string temp_svg_filename{
      f.GetTempFileName(".svg")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_svg_filename,
      PhylogenyR::GraphicsFormat::svg
    );
    assert(f.IsRegularFile(temp_svg_filename));
    //Clean up
    f.DeleteFile(temp_svg_filename);
  }
  if (verbose) { TRACE("NewickToPhylogeny as PNG of extant species"); }
  {
    const std::string temp_png_filename{
      f.GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png
    );
    assert(f.IsRegularFile(temp_png_filename));
    //Clean up
    f.DeleteFile(temp_png_filename.c_str());
  }
  #ifdef FIX_ISSUE_267
  if (verbose) { TRACE("NewickToPhylogenyPng on hard phylogeny"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      f.GetTempFileName(".png")
    };
    const std::string newick{"((ER:1,GR:1):1);"};
    p.NewickToPhylogenyPng(newick,temp_png_filename);
    assert(f.IsRegularFile(temp_png_filename));
    //Clean up
    f.DeleteFile(temp_png_filename.c_str());


    std::cout << "4: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  #endif
  if (verbose) { TRACE("NewickToLttPlot"); }
  {
    const std::string temp_png_filename{
      f.GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToLttPlot(newick,temp_png_filename,GraphicsFormat::png);
    assert(f.IsRegularFile(temp_png_filename));
    //Clean up
    f.DeleteFile(temp_png_filename.c_str());
  }
  if (verbose) { TRACE("DropExtinct"); }
  {
    assert(
      p.DropExtinct(
        "(L:1,(((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):1,(GD:1,ID:1):1,BD:1):3,(AC:1,EC:1):1,(((TC:1,FD:2):1,QC:1,RC:1):1,((((AE:1,BE:1):1,(WD:1,YD:1):1):1,HD:1):2,MC:1):1):1):3);"
      ) == "((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):4,((AE:1,BE:1):1,(WD:1,YD:1):1):5);"
    );
  }
  if (verbose) { TRACE("PhylogenyToNewick"); }
  {
    const std::string s{"((F:2,G:2):1,H:3);"};
    auto& r = ribi::Rinside().Get();
    r["newick"] = s;
    r.parseEval("phylogeny <- read.tree(text = newick)");
    const std::string t{p.PhylogenyToNewick("phylogeny")};
    assert(s == t);
  }
}
#endif

