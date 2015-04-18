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
    assert(PhylogenyR().IsRegularFileStl(temp_svg_filename));
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
    assert(PhylogenyR().IsRegularFileStl(temp_png_filename));
    //Clean up
    ribi::fileio::FileIo().DeleteFile(temp_png_filename.c_str());
  }
  //NewickToPhylogenyPng on hard phylogeny
  {

  }
  // The tree has apparently singleton node(s): cannot read tree file.
  //((ER:1,GR:1):1);
  /*
  library(ape)
  library(geiger)
  png(filename="tmpfilename589986201190433744146092484089548429.png")
  newick <- "((KG:1,(SH:2,UH:2,LH:1):2,((AI:2,(HJ:2,LJ:2,(NJ:2,(MJ:1,PJ:1,SJ:1,VJ:1):1):1):3):2,BH:1):1):1);"
  phylogeny <- read.tree(text = newick)
  plot(phylogeny)
  dev.off()
  */
}
#endif

