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





  if (verbose) { TRACE("Speed comparison of NewickToPhylogeny versus NewickToPhylogeny"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_svg_filename1{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    const std::string temp_svg_filename2{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};

    const TimePoint t2{Clock::now()};
    p.NewickToPhylogenyNew(
      newick,
      temp_svg_filename2,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    const Duration d2{Clock::now() - t2};

    const TimePoint t1{Clock::now()};
    p.NewickToPhylogeny(
      newick,
      temp_svg_filename1,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    const Duration d1{Clock::now() - t1};

    assert(ribi::fileio::FileIo().IsRegularFile(temp_svg_filename1));
    assert(ribi::fileio::FileIo().IsRegularFile(temp_svg_filename2));

    if(
      !ribi::fileio::FileIo().FilesAreIdentical(
        temp_svg_filename1,
        temp_svg_filename2
      )
    )
    {
      std::cout << temp_svg_filename1 << '\n';
    }
    #ifdef FIX_ISSUE_277
    assert(
      ribi::fileio::FileIo().FilesAreIdentical(
        temp_svg_filename1,
        temp_svg_filename2
      )
    );
    assert(!"Fixed issue 277");

    std::cout
      << "d1: " << std::chrono::duration_cast<Msec>(d1).count() << '\n'
      << "d2: " << std::chrono::duration_cast<Msec>(d1).count() << '\n'
    ;


    assert(d2 < d1 / 2);
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename1);
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename2);

    std::cout << "1: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
    assert(!"Fixed speed");
    #endif // FIX_ISSUE_277
  }








  if (verbose) { TRACE("NewickToPhylogeny as SVG of extinct and extant species"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_svg_filename{
      ribi::fileio::FileIo().GetTempFileName(".svg")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_svg_filename,
      PhylogenyR::GraphicsFormat::svg,
      plot_fossils
    );
    assert(ribi::fileio::FileIo().IsRegularFile(temp_svg_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_svg_filename);

    std::cout << "1: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  if (verbose) { TRACE("NewickToPhylogeny as PNG of extinct and extant species"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const bool plot_fossils{false};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      plot_fossils
    );
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());

    std::cout << "2: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  if (verbose) { TRACE("NewickToPhylogeny as PNG of extant species"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const bool plot_fossils{true};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToPhylogeny(
      newick,
      temp_png_filename,
      PhylogenyR::GraphicsFormat::png,
      plot_fossils
    );
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());

    std::cout << "3: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  #ifdef FIX_ISSUE_267
  if (verbose) { TRACE("NewickToPhylogenyPng on hard phylogeny"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((ER:1,GR:1):1);"};
    p.NewickToPhylogenyPng(newick,temp_png_filename);
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());


    std::cout << "4: " << std::chrono::duration_cast<Msec>(Clock::now() - t).count() << " milliseconds" << '\n';
  }
  #endif
  if (verbose) { TRACE("NewickToLttPlot"); }
  {
    const TimePoint t{Clock::now()};

    const std::string temp_png_filename{
      ribi::fileio::FileIo().GetTempFileName(".png")
    };
    const std::string newick{"((F:2,G:2):1,H:3);"};
    p.NewickToLttPlot(newick,temp_png_filename,GraphicsFormat::png);
    assert(ribi::fileio::FileIo().IsRegularFile(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());

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


  std::cout << std::chrono::duration_cast<Msec>(Clock::now() - t_test).count() << " milliseconds" << '\n';
}
#endif

