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

std::string PhylogenyR::DropExtinct(const std::string& newick) const
{
  assert(!newick.empty());

  //TODO: Test if the user has all required packages

  const std::string temp_r_filename{
    ribi::fileio::FileIo().GetTempFileName(".R")
  };
  const std::string temp_newick_filename{
    ribi::fileio::FileIo().GetTempFileName(".new")
  };

  //Create the R script
  {
    std::ofstream f(temp_r_filename.c_str());
    f
      << "library(ape)" << '\n'
      << "library(geiger)" << '\n'
      << "newick <- \"" << newick << "\"" << '\n'
      << "phylogeny <- read.tree(text = newick)" << '\n'
      << "phylogeny <- drop.extinct(phylogeny)" << '\n'
      << "write.tree(phylogeny,file=\"" << temp_newick_filename << "\")" << '\n'
    ;
  }

  if (!ribi::fileio::FileIo().IsRegularFile(temp_r_filename))
  {
    std::stringstream s;
    s << "PhylogenyR::DropExtict: "
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

  if (!ribi::fileio::FileIo().IsRegularFile(temp_newick_filename))
  {
    std::stringstream s;
    s << "PhylogenyR::DropExtict: "
      << "Could not create temporary Newick file "
      << "with filename '" << temp_newick_filename << "'. "
      << "Perhaps not all packages (ape, geiger) needed are installed? "
      << "You can try to run the temporary R script file '"
      << temp_r_filename
      << "' yourself to see which error it gives"
    ;
    throw std::runtime_error(s.str().c_str());
  }
  //After detection. so user can check script
  ribi::fileio::FileIo().DeleteFile(temp_r_filename);

  const std::string newick_extant{
    ribi::fileio::FileIo().FileToStr(temp_newick_filename)
  };

  ribi::fileio::FileIo().DeleteFile(temp_newick_filename);

  return newick_extant;
}


void PhylogenyR::NewickToLttPlot(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format,
  const bool plot_fossils
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
    ;
    if (!plot_fossils)
    {
      f << "phylogeny <- drop.extinct(phylogeny)" << '\n';
    }
    f
      << "ltt.plot(phylogeny)" << '\n'
      << "dev.off()" << '\n';
    ;
  }

  if (!ribi::fileio::FileIo().IsRegularFile(temp_r_filename))
  {
    std::stringstream s;
    s << "PhylogenyR::NewickToLttPlot: "
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

  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << "PhylogenyR::NewickToLttPlot: "
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

void PhylogenyR::NewickToPhylogeny(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format,
  const bool plot_fossils
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
    ;
    if (!plot_fossils)
    {
      f << "phylogeny <- drop.extinct(phylogeny)" << '\n';
    }
    f
      << "plot(phylogeny)" << '\n'
      << "dev.off()" << '\n';
    ;
  }

  if (!ribi::fileio::FileIo().IsRegularFile(temp_r_filename))
  {
    std::stringstream s;
    s << "PhylogenyR::NewickToPhylogeny: "
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

  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << "PhylogenyR::NewickToPhylogeny: "
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
