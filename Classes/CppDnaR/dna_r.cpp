#include "dna_r.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <future>

#include "RInside.h"

#include "dnasequence.h"
#include "fileio.h"
#include "ribi_rinside.h"

ribi::DnaR::DnaR()
{

  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::DnaR::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::DnaR::GetVersionHistory() const noexcept
{
  return {
    "2015-06-13: Version 1.0: started versioning"
  };
}

void ribi::DnaR::PlotSequences(
  const std::vector<ribi::DnaSequence>& sequences,
  const std::string& filename
) const
{
  PlotSequencesRinside(sequences,filename);
}

void ribi::DnaR::PlotSequencesRinside(
  const std::vector<ribi::DnaSequence>& sequences,
  const std::string& png_filename
) const
{
  assert(!sequences.empty());

  auto& r = ribi::Rinside().Get();
  r.parseEval("library(ape)");

  //TODO: Test if the user has all required packages

  //Create the R script
  {
    std::stringstream s;
    s
      << "x <- structure(c("
    ;
    std::stringstream container;
    for (const auto sequence: sequences)
    {
      container << "\"" << sequence.GetDescription() << "\",";
    }
    for (const auto sequence: sequences)
    {
      container << "\"" << sequence.GetSequence() << "\",";
    }
    std::string container_str{container.str()};
    assert(!container_str.empty());
    container_str.pop_back();
    s
      << container_str
      << "), .Dim = c(" << sequences.size() << "L, 2L))"
    ;
    r.parseEval(s.str());
  }
  r.parseEval("y <- t(sapply(strsplit(x[,2],\"\"), tolower))");
  r.parseEval("rownames(y) <- x[,1]");
  r.parseEval("alignments <- as.DNAbin(y)");
  r["png_filename"] = png_filename;
  r.parseEval("png(filename=png_filename)");
  r.parseEval("image(alignments)");
  r.parseEval("dev.off()");

  if (!ribi::fileio::FileIo().IsRegularFile(png_filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
      << "Could not create temporary PNG file "
      << "with filename '" << png_filename << "'. "
      << "Perhaps not all packages (ape) needed are installed? "
    ;
    throw std::runtime_error(s.str().c_str());
  }
}

void ribi::DnaR::PlotSequencesRscript(
  const std::vector<ribi::DnaSequence>& sequences,
  const std::string& png_filename
) const
{
  assert(!sequences.empty());

  //TODO: Test if the user has all required packages

  const std::string temp_r_filename{
    ribi::fileio::FileIo().GetTempFileName(".R")
  };

  //Create the R script
  {
    std::ofstream f(temp_r_filename.c_str());
    f
      << "library(ape)" << '\n'
      << "x <- structure(c("
    ;
    {
      std::stringstream container;
      for (const auto sequence: sequences)
      {
        container << "\"" << sequence.GetDescription() << "\",";
      }
      for (const auto sequence: sequences)
      {
        container << "\"" << sequence.GetSequence() << "\",";
      }
      std::string container_str{container.str()};
      assert(!container_str.empty());
      container_str.pop_back();
      f << container_str;
    }
    f
      << "), .Dim = c(" << sequences.size() << "L, 2L))" << '\n'
      << "y <- t(sapply(strsplit(x[,2],\"\"), tolower))" << '\n'
      << "rownames(y) <- x[,1]" << '\n'
      << "alignments <- as.DNAbin(y)" << '\n'
      << "png(filename=\"" << png_filename << "\")" << '\n'
      << "image(alignments)" << '\n'
      << "dev.off()" << '\n'
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

  if (!ribi::fileio::FileIo().IsRegularFile(png_filename))
  {
    std::stringstream s;
    s << __FILE__ << "(" << __LINE__ << "): "
      << "Could not create temporary PNG file "
      << "with filename '" << png_filename << "'. "
      << "Perhaps not all packages (ape) needed are installed? "
      << "You can try to run the temporary R script file '"
      << temp_r_filename
      << "' yourself to see which error it gives"
    ;
    throw std::runtime_error(s.str().c_str());
  }
  //After detection. so user can check script
  ribi::fileio::FileIo().DeleteFile(temp_r_filename);
}
