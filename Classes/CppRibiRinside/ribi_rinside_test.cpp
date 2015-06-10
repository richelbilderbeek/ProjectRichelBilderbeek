#ifndef NDEBUG

#include "ribi_rinside.h"

#include <cassert>

#include "RInside.h"

#include "fileio.h"

bool operator==(const Rcpp::NumericVector& lhs, const Rcpp::NumericVector& rhs)
{
  return std::equal(
    std::begin(lhs),
    std::end(lhs),
    std::begin(rhs)
  );
}


void ribi::Rinside::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  auto& r = Rinside().Get();
  const auto f = ribi::fileio::FileIo();
  //Read/write of integer
  {
    r["x"] = 42;
    const Rcpp::NumericVector v = r.parseEval("x");
    assert(v.size() == 1);
    assert(v[0] == 42);
  }
  //Read/write of integer vector
  {
    const Rcpp::NumericVector v = {1,2,3};
    r["v"] = v;
    const Rcpp::NumericVector w = r.parseEval("v");
    assert(v == w);
  }
  //Read/write of plot with known name
  {
    if(f.IsRegularFile("tmp.png")) { f.DeleteFile("tmp.png"); }
    assert(!f.IsRegularFile("tmp.png"));
    r.parseEval("png(filename=\"tmp.png\")");
    r.parseEval("plot(sin)");
    r.parseEval("dev.off()");
    assert(f.IsRegularFile("tmp.png"));
    f.DeleteFile("tmp.png");
  }
  {
    const std::string newick{"((F:2,G:2):1,H:3);"};
    if(f.IsRegularFile("tmp.png")) { f.DeleteFile("tmp.png"); }
    assert(!f.IsRegularFile("tmp.png"));
    r.parseEvalQ("library(ape)");
    r.parseEvalQ("library(geiger)");
    r["newick"] = newick;
    r.parseEvalQ("phylogeny <- read.tree(text = newick)");
    r.parseEvalQ("png(filename=\"tmp.png\")");
    r.parseEvalQ("plot(phylogeny)");
    r.parseEvalQ("dev.off()");

    assert(f.IsRegularFile("tmp.png"));
    f.DeleteFile("tmp.png");
  }
  //Use any filename
  {
    const std::string filename = f.GetTempFileName(".png");
    assert(!f.IsRegularFile(filename));
    r.parseEval("png(filename=\""+filename+"\")");
    r.parseEval("plot(sin)");
    r.parseEval("dev.off()");
    assert(f.IsRegularFile(filename));
    f.DeleteFile(filename);
  }
  //Use any filename with a name in the R script
  {
    const std::string filename = f.GetTempFileName(".png");
    assert(!f.IsRegularFile(filename));
    r["png_filename"] = filename;
    r.parseEval("png(filename=png_filename)");
    r.parseEval("plot(sin)");
    r.parseEval("dev.off()");
    assert(f.IsRegularFile(filename));
    f.DeleteFile(filename);
  }

  //assert(1==2);
}

#endif // NDEBUG
