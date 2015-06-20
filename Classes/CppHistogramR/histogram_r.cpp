#include "histogram_r.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ribi_rinside.h"
#include "fileio.h"

ribi::HistogramR::HistogramR()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::HistogramR::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::HistogramR::GetVersionHistory() const noexcept
{
  return {
    "2015-06-20: Version 1.0: initial version"
  };
}

void ribi::HistogramR::ToHistogram(
  const std::vector<double>& v,
  const std::string& filename,
  const ribi::HistogramR::GraphicsFormat graphics_format
) const
{
  assert(!v.empty());
  assert(!filename.empty());

  //TODO: Test if the user has all required packages
  auto& r = ribi::Rinside().Get();

  //r.parseEvalQ("library(ape)");
  //r.parseEvalQ("library(geiger)");
  r["v"] = v;
  r["temp_filename"] = filename;

  switch (graphics_format)
  {
    case GraphicsFormat::png:
      r.parseEvalQ("png(filename=temp_filename)");
    break;
    case GraphicsFormat::svg:
      r.parseEvalQ("svg(filename=temp_filename)");
    break;
  }
  r.parseEvalQ("hist(v)");
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
