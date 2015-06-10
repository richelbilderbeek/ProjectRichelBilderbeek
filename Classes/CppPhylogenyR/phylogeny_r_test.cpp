#include "phylogeny_r.h"

#include <cassert>
#include <chrono>

#include "fileio.h"
#include "testtimer.h"
#include "trace.h"

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
  }
  using Clock = std::chrono::system_clock;
  using Duration = std::chrono::system_clock::duration;
  using TimePoint = std::chrono::system_clock::time_point;
  using Msec = std::chrono::milliseconds;

  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  ribi::fileio::FileIo f;
  #define FIX_ISSUE_278
  #ifdef FIX_ISSUE_278
  const bool test_throughly{true};
  #else  // FIX_ISSUE_277
  const bool test_throughly{false};
  #endif // FIX_ISSUE_277

  const TimePoint t_test{Clock::now()};

  PhylogenyR p;

  if (!test_throughly)
  {
    TRACE("PhylogenyR not thoroughly tested");
    return;
  }







  if (verbose) { TRACE("NewickToPhylogeny as SVG of extinct and extant species"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_svg_filename{
      f.GetTempFileName(".svg")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_svg_filename,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    assert(f.IsRegularFile(temp_svg_filename));
    //Clean up
    f.DeleteFile(temp_svg_filename);

    std::cout << "1: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  if (verbose) { TRACE("NewickToPhylogeny as PNG of extinct and extant species"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      f.GetTempFileName(".png")
    };
    const bool plot_fossils{false};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      plot_fossils
    );
    assert(f.IsRegularFile(temp_png_filename));
    //Clean up
    f.DeleteFile(temp_png_filename.c_str());

    std::cout << "2: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  if (verbose) { TRACE("NewickToPhylogeny as PNG of extant species"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      f.GetTempFileName(".png")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      plot_fossils
    );
    assert(f.IsRegularFile(temp_png_filename));
    //Clean up
    f.DeleteFile(temp_png_filename.c_str());

    std::cout << "3: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
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
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      f.GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToLttPlot(newick,temp_png_filename,GraphicsFormat::png);
    assert(f.IsRegularFile(temp_png_filename));
    //Clean up
    f.DeleteFile(temp_png_filename.c_str());

    std::cout << "5: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  if (verbose) { TRACE("DropExtinct"); }
  {
    const TimePoint t{Clock::now()};

    assert(
      p.DropExtinct(
        "(L:1,(((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):1,(GD:1,ID:1):1,BD:1):3,(AC:1,EC:1):1,(((TC:1,FD:2):1,QC:1,RC:1):1,((((AE:1,BE:1):1,(WD:1,YD:1):1):1,HD:1):2,MC:1):1):1):3);"
      ) == "((((XD:1,ZD:1):1,CE:2):1,(FE:2,EE:2):1):4,((AE:1,BE:1):1,(WD:1,YD:1):1):5);"
    );

    std::cout << "6: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }

  if ("Test NewickToPhylogenyRinside faster than NewickToPhylogenyRscript")
  {
    const TimePoint t{Clock::now()};

    const std::string temp_svg_filename1{
      f.GetTempFileName(".svg")
    };
    const std::string temp_svg_filename2{
      f.GetTempFileName(".svg")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};

    const TimePoint t1{Clock::now()};
    p.NewickToPhylogenyRscript(
      newick,
      temp_svg_filename1,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    const Duration d1{Clock::now() - t1};

    const TimePoint t2{Clock::now()};
    p.NewickToPhylogenyRinside(
      newick,
      temp_svg_filename2,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    const Duration d2{Clock::now() - t2};


    assert(f.IsRegularFile(temp_svg_filename1));
    assert(f.IsRegularFile(temp_svg_filename2));

    assert(d2 < d1 / 10);
    //Clean up
    f.DeleteFile(temp_svg_filename1);
    f.DeleteFile(temp_svg_filename2);
    // Before (using R script): 976
    // After (using RInside): 5
    std::cout << "Before (using R script): " << std::chrono::duration_cast<Msec>(d1).count() << '\n';
    std::cout << "After (using RInside): "  << std::chrono::duration_cast<Msec>(d2).count() << '\n';
  }

  if ("Speed compare NewickToLttPlotRscript versus NewickToLttPlotRinside")
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename1{f.GetTempFileName(".png") };
    const std::string temp_png_filename2{f.GetTempFileName(".png") };
    const std::string newick{"((F:2,G:2):1,H:3);"};

    const TimePoint t1{Clock::now()};
    p.NewickToLttPlotRscript(newick,temp_png_filename1,GraphicsFormat::png);
    const Duration d1{Clock::now() - t1};

    const TimePoint t2{Clock::now()};
    p.NewickToLttPlotRinside(newick,temp_png_filename2,GraphicsFormat::png);
    const Duration d2{Clock::now() - t2};

    assert(f.IsRegularFile(temp_png_filename1));
    assert(f.IsRegularFile(temp_png_filename2));
    assert(d2 < d1 / 10);

    //Clean up
    f.DeleteFile(temp_png_filename1.c_str());
    f.DeleteFile(temp_png_filename2.c_str());

    // Before (using R script): 941
    // After (using RInside): 24
    std::cout << "Before (using R script): " << std::chrono::duration_cast<Msec>(d1).count() << '\n';
    std::cout << "After (using RInside): "  << std::chrono::duration_cast<Msec>(d2).count() << '\n';
  }


  std::cout << std::chrono::duration_cast<Msec>(Clock::now() - t_test).count() << " milliseconds" << '\n';
}
#endif

