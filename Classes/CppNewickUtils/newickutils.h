#ifndef RIBI_NEWICKUTILS_H
#define RIBI_NEWICKUTILS_H

#include <string>
#include <vector>

///Wrapper to call newick_utils
struct NewickUtils
{
  NewickUtils();

  ///Display Newick to console, use GetPhylogeny to obtain the text
  void Display(const std::string& newick);

  ///GetPhylogeny returns the Newick as a phylogeny
  std::vector<std::string> GetPhylogeny(const std::string& newick);

  private:
  std::vector<std::string> FileToVector(
    const std::string& filename
  ) const noexcept;

  bool IsRegularFileStl(const std::string& filename) const noexcept;

  static const std::string sm_newick_utils_path;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif //RIBI_NEWICKUTILS_H
