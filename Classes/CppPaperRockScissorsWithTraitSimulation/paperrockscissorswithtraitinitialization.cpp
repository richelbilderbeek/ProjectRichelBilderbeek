#include "paperrockscissorswithtraitinitialization.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "fileio.h"

#ifndef NDEBUG
void ribi::prswt::TestInitialization() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const auto all = {
    Initialization::random,
    Initialization::vertical_bands,
    Initialization::monomorph
  };

  //ToStr
  {
    for (const auto i: all)
    {
      const std::string s = ToStr(i);
      const auto j = ToInitialization(s);
      const std::string t = ToStr(j);
      assert(i == j);
      assert(s == t);
    }
  }
  //File I/O
  {
    for (const auto i: all)
    {
      const std::string filename = ribi::fileio::FileIo().GetTempFileName(".txt");
      //Write to file
      {
        std::ofstream f(filename);
        f << i;
      }
      //Read from file
      std::ifstream f(filename);
      Initialization j{Initialization::random};
      f >> j;
      assert(i == j);
      ribi::fileio::FileIo().DeleteFile(filename);
    }
  }
}
#endif

std::string ribi::prswt::ToStr(const Initialization initialization) noexcept
{
  switch (initialization)
  {
    case Initialization::random: return "random";
    case Initialization::vertical_bands: return "vertical_bands";
    case Initialization::monomorph: return "monomorph";
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::prswt::ToStr: unknown value of initialization");
}

ribi::prswt::Initialization ribi::prswt::ToInitialization(const std::string& s)
{
  if (s == "random") return Initialization::random;
  if (s == "vertical_bands") return Initialization::vertical_bands;
  if (s == "monomorph") return Initialization::monomorph;
  throw std::logic_error("ribi::prswt::ToInitialization: unknown s");
}


std::ostream& ribi::prswt::operator<<(std::ostream& os, const Initialization initialization)
{
  os << ToStr(initialization);
  return os;
}

std::istream& ribi::prswt::operator>>(std::istream& is, Initialization& initialization)
{
  std::string s;
  is >> s;
  initialization = ToInitialization(s);
  return is;
}
