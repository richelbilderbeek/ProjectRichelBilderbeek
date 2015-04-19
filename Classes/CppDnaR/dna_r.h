#ifndef RIBI_DNA_R_H
#define RIBI_DNA_R_H

#include <memory>
#include <vector>

struct DnaR
{
  enum class GraphicsFormat { png, svg };

  DnaR();

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

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_DNA_R_H
