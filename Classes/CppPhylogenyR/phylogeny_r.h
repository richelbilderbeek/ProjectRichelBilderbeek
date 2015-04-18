#ifndef RIBI_PHYLOGENY_R_H
#define RIBI_PHYLOGENY_R_H

#include <memory>
#include <vector>

struct PhylogenyR
{

  PhylogenyR();

  void NewickToPhylogenyPng(
    const std::string& newick,
    const std::string& png_filename
  ) const;

  void NewickToPhylogenySvg(
    const std::string& newick,
    const std::string& svg_filename
  ) const;

  private:

  enum class GraphicsFormat { png, svg };

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  bool IsRegularFileStl(
    const std::string& filename
  ) const noexcept;

  ///Handles both NewickToPhylogenyPng and NewickToPhylogenySvg
  void NewickToPhylogenyImpl(
    const std::string& newick,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};


#endif // RIBI_PHYLOGENY_R_H
