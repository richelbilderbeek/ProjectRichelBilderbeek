#ifndef RIBI_PHYLOGENY_R_H
#define RIBI_PHYLOGENY_R_H

#include <memory>
#include <vector>

struct PhylogenyR
{
  enum class GraphicsFormat { png, svg };

  PhylogenyR();

  ///Plot Newick as a Lineages Through Time Plot in PNG format
  void NewickToLttPlot(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Plot Newick as a phylogeny in a graphics format
  void NewickToPhylogeny(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Plot Newick as a phylogeny in PNG format
  void NewickToPhylogenyPng(
    const std::string& newick,
    const std::string& png_filename
  ) const;

  ///Plot Newick as a phylogeny in SVG format
  void NewickToPhylogenySvg(
    const std::string& newick,
    const std::string& svg_filename
  ) const;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_PHYLOGENY_R_H
