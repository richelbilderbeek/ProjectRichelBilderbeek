#ifndef RIBI_NEWICKUTILS_H
#define RIBI_NEWICKUTILS_H

#include <string>

///Wrapper to call newick_utils
struct NewickUtils
{
  NewickUtils();

  void Display(const std::string& newick);

  private:
  bool IsRegularFileStl(const std::string& filename) const noexcept;

  static const std::string sm_newick_utils_path;
};

#endif //RIBI_NEWICKUTILS_H
