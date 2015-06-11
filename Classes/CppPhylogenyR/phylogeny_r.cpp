#include "phylogeny_r.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <future>

#include "ribi_rinside.h"
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

  auto& r = ribi::Rinside().Get();
  r.parseEval("library(ape)");
  r.parseEval("library(geiger)");
  r["newick"] = newick;
  r.parseEval("phylogeny <- read.tree(text = newick)");
  r.parseEval("phylogeny <- drop.extinct(phylogeny)");
  const Rcpp::String s = r.parseEval("write.tree(phylogeny)");
  return std::string(s);
}

void PhylogenyR::NewickToBranchingTimes(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format
) const
{
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
      << "branching_times <- branching.times(phylogeny)" << '\n'
      << "hist(branching_times)" << '\n'
      << "dev.off()" << '\n';
    ;
  }

  if (!ribi::fileio::FileIo().IsRegularFile(temp_r_filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
      << "Could not create temporary R script file "
      << "with filename '" << temp_r_filename << "'";
    throw std::runtime_error(s.str().c_str());
  }

  //Execute the R script
  {
    std::stringstream cmd;
    cmd << "Rscript " << temp_r_filename;
    const int error{std::system(cmd.str().c_str())};
    if (error)
    {
      std::clog << __FILE__ << ": error " << error << '\n';
    }
  }

  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
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

void PhylogenyR::NewickToBranchLengths(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format
) const
{
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
      << "branch_lengths <- phylogeny$edge.length" << '\n'
      << "hist(branch_lengths)" << '\n'
      << "dev.off()" << '\n';
    ;
  }

  if (!ribi::fileio::FileIo().IsRegularFile(temp_r_filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
      << "Could not create temporary R script file "
      << "with filename '" << temp_r_filename << "'";
    throw std::runtime_error(s.str().c_str());
  }

  //Execute the R script
  {
    std::stringstream cmd;
    cmd << "Rscript " << temp_r_filename;
    const int error{std::system(cmd.str().c_str())};
    if (error)
    {
      std::clog << __FILE__ << ": error " << error << '\n';
    }
  }

  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
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

void PhylogenyR::NewickToLttPlot(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format
) const
{
  assert(!newick.empty());
  assert(!filename.empty());

  //TODO: Test if the user has all required packages
  auto& r = ribi::Rinside().Get();

  r.parseEvalQ("library(ape)");
  r.parseEvalQ("library(geiger)");
  r["temp_filename"] = filename;
  r["newick"] = newick;
  r.parseEvalQ("phylogeny <- read.tree(text = newick)");

  switch (graphics_format)
  {
    case GraphicsFormat::png:
      r.parseEvalQ("png(filename=temp_filename)");
    break;
    case GraphicsFormat::svg:
      r.parseEvalQ("svg(filename=temp_filename)");
    break;
  }
  r.parseEvalQ("ltt.plot(phylogeny)");
  r.parseEvalQ("dev.off()");

  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
      << "Could not create SVG "
      << "with filename '" << filename << "'. "
      << "Perhaps not all packages (ape, geiger) needed are installed?"
    ;
    throw std::runtime_error(s.str().c_str());
  }
}

void PhylogenyR::NewickToPhylogeny(
  const std::string& newick,
  const std::string& filename,
  const PhylogenyR::GraphicsFormat graphics_format
) const
{
  assert(!newick.empty());
  assert(!filename.empty());

  //TODO: Test if the user has all required packages
  auto& r = ribi::Rinside().Get();

  r.parseEvalQ("library(ape)");
  r.parseEvalQ("library(geiger)");
  r["temp_filename"] = filename;
  r["newick"] = newick;
  r.parseEvalQ("phylogeny <- read.tree(text = newick)");

  switch (graphics_format)
  {
    case GraphicsFormat::png:
      r.parseEvalQ("png(filename=temp_filename)");
    break;
    case GraphicsFormat::svg:
      r.parseEvalQ("svg(filename=temp_filename)");
    break;
  }
  r.parseEvalQ("plot(phylogeny)");
  r.parseEvalQ("dev.off()");


  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
      << "Could not create image "
      << "with filename '" << filename << "'. "
      << "Perhaps not all packages (ape, geiger) needed are installed?"
    ;
    throw std::runtime_error(s.str().c_str());
  }
}

std::string PhylogenyR::PhylogenyToNewick(
  const std::string& phylogeny_name
)
{
  auto& r = ribi::Rinside().Get();
  const Rcpp::String s = r.parseEval("write.tree("+ phylogeny_name + ")");
  const std::string t = s;
  return t;
}
