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
    const GraphicsFormat graphics_format
  ) const;

  ///Plot Newick as a phylogeny in a graphics format
  ///same interface is followed by NewickUtils
  void NewickToPhylogeny(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Converts a phylogeny, with the
  ///name 'phylogeny_name' known
  ///inside RInside to std::string
  std::string PhylogenyToNewick(
    const std::string& phylogeny_name
  );


  private:

  ///Make a histogram of the branching times
  void NewickToBranchingTimesRinside(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Make a histogram of the branching times
  void NewickToBranchingTimesRscript(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Make a histogram of the branch length
  void NewickToBranchLengthsRinside(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  ///Make a histogram of the branch length
  void NewickToBranchLengthsRscript(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_PHYLOGENY_R_H
