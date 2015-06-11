#ifndef RIBI_PHYLOGENY_R_H
#define RIBI_PHYLOGENY_R_H

#include <memory>
#include <vector>

#include "RInside.h"

struct RInside;

struct PhylogenyR
{
  enum class GraphicsFormat { png, svg };

  PhylogenyR();

  ///Remove the lineages that are extinct at the present time
  ///Throws std::runtime_error if R script fails
  std::string DropExtinct(
    const std::string& newick
  ) const;

  ///Make a histogram of the branching times
  void NewickToBranchingTimes(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Make a histogram of the branch length
  void NewickToBranchLengths(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
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

  ///Converts a phylogeny, with the
  ///name 'phylogeny_name' known
  ///inside RInside to std::string
  std::string PhylogenyToNewick(
    const std::string& phylogeny_name
  );


  private:

  std::string DropExtinctRinside(
    const std::string& newick
  ) const;

  std::string DropExtinctRscript(
    const std::string& newick
  ) const;

  void NewickToLttPlotRscript(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  void NewickToLttPlotRinside(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  void NewickToPhylogenyRscript(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  void NewickToPhylogenyRinside(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_PHYLOGENY_R_H
