#ifndef RIBI_PHYLOGENY_R_H
#define RIBI_PHYLOGENY_R_H

#include <memory>
#include <vector>

struct PhylogenyR
{
  enum class GraphicsFormat { png, svg };

  PhylogenyR();

  ///Remove the lineages that are extinct at the present time
  std::string DropExtict(
    const std::string& newick
  ) const;

  ///Plot Newick as a Lineages Through Time Plot in PNG format
  void NewickToLttPlot(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  ///Plot Newick as a phylogeny in a graphics format
  ///same interface is followed by NewickUtils
  void NewickToPhylogeny(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_PHYLOGENY_R_H
