#include "phylogeny_r.h"

#include <cassert>

#ifndef NDEBUG
void PhylogenyR::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    const std::string temp_svg_filename{"tmp.svg"};
    const std::string newick{"((F:2,G:2):1,H:3);"};
    PhylogenyR().NewickToPhylogenySvg(newick,temp_svg_filename);
    assert(PhylogenyR().IsRegularFileStl(temp_svg_filename));
  }
}
#endif

