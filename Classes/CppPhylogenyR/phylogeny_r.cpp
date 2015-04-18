#include "phylogeny_r.h"

#include <cassert>
#include <fstream>
#include <sstream>

#include "fileio.h"

PhylogenyR::PhylogenyR()
{

  #ifndef NDEBUG
  Test();
  #endif
}

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool PhylogenyR::IsRegularFileStl(
  const std::string& filename
) const noexcept
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

void PhylogenyR::NewickToPhylogenyImpl(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format
) const
{
  assert(!newick.empty());
  assert(!filename.empty());

  //TODO: Test if the user has all required packages

  const std::string temp_r_filename{
    ribi::fileio::FileIo().GetTempFileName(".R")
  };

  //Create the R script
  {
    std::ofstream f(temp_r_filename.c_str());
    f
      << "library(ape)" << '\n'
      << "library(geiger)" << '\n'
    ;
    switch (graphics_format)
    {
      case GraphicsFormat::png:
        f << "png(filename=\"" << filename << "\")" << '\n';
      break;
      case GraphicsFormat::svg:
        f << "svg(filename=\"" << filename << "\")" << '\n';
      break;
    }

    f
      << "newick <- \"" << newick << "\"" << '\n'
      << "phylogeny <- read.tree(text = newick)" << '\n'
      << "plot(phylogeny)" << '\n'
      << "dev.off()" << '\n';
    ;
  }
  if (!PhylogenyR().IsRegularFileStl(temp_r_filename))
  {
    std::stringstream s;
    s << "PhylogenyR::NewickToPhylogenySvg: "
      << "Could not create temporary R script file "
      << "with filename '" << temp_r_filename << "'";
    throw std::runtime_error(s.str().c_str());
  }

  //Execute the R script
  {
    std::stringstream cmd;
    cmd << "Rscript " << temp_r_filename;
    std::system(cmd.str().c_str());
  }

  if (!PhylogenyR().IsRegularFileStl(filename))
  {
    std::stringstream s;
    s << "PhylogenyR::NewickToPhylogenySvg: "
      << "Could not create SVG "
      << "with filename '" << filename << "'. "
      << "Perhaps not all packages (ape, geiger) needed are installed? "
      << "You can try to run the temporary R script file '"
      << temp_r_filename
      << "' yourself to see which error it gives"
    ;
    throw std::runtime_error(s.str().c_str());
  }

  //Delete the temporary R file
  ribi::fileio::FileIo().DeleteFile(temp_r_filename);
}

void PhylogenyR::NewickToPhylogenyPng(
  const std::string& newick,
  const std::string& png_filename
) const
{
  NewickToPhylogenyImpl(newick,png_filename,GraphicsFormat::png);
}

void PhylogenyR::NewickToPhylogenySvg(
  const std::string& newick,
  const std::string& svg_filename
) const
{
  NewickToPhylogenyImpl(newick,svg_filename,GraphicsFormat::svg);
}

