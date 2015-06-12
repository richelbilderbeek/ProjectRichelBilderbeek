#include "dna_r.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <future>

#include "dnasequence.h"
#include "fileio.h"

DnaR::DnaR()
{

  #ifndef NDEBUG
  Test();
  #endif
}

void DnaR::PlotSequences(
  const std::vector<ribi::DnaSequence>& sequences,
  const std::string& filename
) const
{
  PlotSequencesRinside(sequences,filename);
}

void DnaR::PlotSequencesRinside(
  const std::vector<ribi::DnaSequence>& sequences,
  const std::string& filename
) const
{
  PlotSequencesRscript(sequences,filename);
}

void DnaR::PlotSequencesRscript(
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
