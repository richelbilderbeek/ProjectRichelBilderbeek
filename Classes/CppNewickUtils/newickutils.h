#ifndef RIBI_NEWICKUTILS_H
#define RIBI_NEWICKUTILS_H

#include <string>
#include <vector>

///Wrapper to call newick_utils
struct NewickUtils
{
  enum class GraphicsFormat { svg };

  NewickUtils();


  ///Display Newick to console, use GetPhylogeny to obtain the text
  void Display(const std::string& newick);

  ///Drops the extinct lineages, throws if R script fails
  std::string DropExtinct(const std::string& newick) const;

  ///GetPhylogeny returns the Newick as a phylogeny in text
  std::vector<std::string> GetPhylogeny(const std::string& newick);

  ///Plot Newick as a phylogeny in a graphics format,
  ///folloing the same interface as PhylogenyR
  void NewickToPhylogeny(
    std::string newick,
    const std::string& filename,
    const GraphicsFormat graphics_format,
    const bool plot_fossils = true
  ) const;

  private:
  static const std::string sm_newick_utils_path;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif //RIBI_NEWICKUTILS_H
