#include "phylogeny_r.h"

#include <cassert>
#include <fstream>
#include <sstream>

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

void PhylogenyR::NewickToPhylogenySvg(
  const std::string& newick,
  const std::string& svg_filename
) const noexcept
{
  assert(!newick.empty());
  assert(!svg_filename.empty());

  //TODO: Test if the user has all required packages

  const std::string r_filename{"temp.R"};

  //Create the R script
  {
    /*
    library(ape)
    library(geiger)
    svg(filename="CreateTreeFromNewick.svg")
    newick <- "((F:2,G:2):1,H:3);" # OK
    phylogeny <- read.tree(text = newick)
    plot(phylogeny)
    dev.off()
    */

    std::ofstream f(r_filename.c_str());
    f
      << "library(ape)" << '\n'
      << "library(geiger)" << '\n'
      << "svg(filename=\"" << svg_filename << "\")" << '\n'
      << "newick <- \"" << newick << "\"" << '\n'
      << "phylogeny <- read.tree(text = newick)" << '\n'
      << "plot(phylogeny)" << '\n'
      << "dev.off()" << '\n';
    ;
  }
  //Execute the R script
  {
    std::stringstream cmd;
    cmd << "Rscript " << r_filename;
    std::system(cmd.str().c_str());
  }
}

