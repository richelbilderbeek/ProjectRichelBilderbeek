#ifndef RIBI_PHYLOGENY_R_H
#define RIBI_PHYLOGENY_R_H

#include <memory>
#include <vector>

struct PhylogenyR
{

  PhylogenyR();

  void NewickToPhylogenySvg(
    const std::string& newick,
    const std::string& svg_filename
  ) const noexcept;

  private:

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  bool IsRegularFileStl(
    const std::string& filename
  ) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_PHYLOGENY_R_H
