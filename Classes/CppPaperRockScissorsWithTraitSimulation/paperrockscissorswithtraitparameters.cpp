#include "paperrockscissorswithtraitparameters.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "fileio.h"

ribi::prswt::Parameters::Parameters(
  const int width,
  const int height,
  const Initialization initialization,
  const int rng_seed
) : m_width{width},
    m_height{height},
    m_initialization{initialization},
    m_rng_seed{rng_seed}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::prswt::Parameters::SetHeight(const int height)
{
  if (height < 1) throw std::logic_error("ribi::prswt::Parameters::SetHeight: invalid height");
  assert(height > 0);
  m_height = height;
}

void ribi::prswt::Parameters::SetInitialization(const Initialization initialization) noexcept
{
  m_initialization = initialization;
}

void ribi::prswt::Parameters::SetRngSeed(const int rng_seed) noexcept
{
  m_rng_seed = rng_seed;
}

void ribi::prswt::Parameters::SetWidth(const int width)
{
  if (width < 1) throw std::logic_error("ribi::prswt::Parameters::SetWidth: invalid width");
  assert(width > 0);
  m_width = width;
}



#ifndef NDEBUG
void ribi::prswt::Parameters::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    TestInitialization();
  }
  //operator==
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    const Parameters q(2,3,Initialization::monomorph,42);
    assert(p == q);
  }
  //operator==
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    const Parameters q(p);
    assert(p == q);
  }
  //operator!=, varied width
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    Parameters q(p);
    q.SetWidth(q.GetWidth() + 1);
    assert(p != q);
  }
  //operator!=, varied height
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    Parameters q(p);
    q.SetHeight(q.GetHeight() + 1);
    assert(p != q);
  }
  //operator!=, varied initialization
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    Parameters q(p);
    q.SetInitialization(Initialization::vertical_bands);
    assert(p != q);
  }
  //operator!=, varied RNG seed
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    Parameters q(p);
    q.SetRngSeed(q.GetRngSeed() + 1);
    assert(p != q);
  }
  //File Io
  {
    const Parameters p(2,3,Initialization::monomorph,42);
    const std::string filename = ribi::fileio::FileIo().GetTempFileName(".txt");
    //Write to file
    {
      std::ofstream f(filename);
      f << p;
    }
    //Read from file
    std::ifstream f(filename);
    Parameters q(p);
    f >> q;
    assert(p == q);
    ribi::fileio::FileIo().DeleteFile(filename);
  }

}
#endif

std::ostream& ribi::prswt::operator<<(std::ostream& os, const Parameters& parameters)
{
  os
    << "width: " << parameters.GetWidth()
    << " height: " << parameters.GetHeight()
    << " initialization: " << parameters.GetInitialization()
    << " rng_seed: " << parameters.GetRngSeed()
  ;
  return os;
}

std::istream& ribi::prswt::operator>>(std::istream& is, Parameters& parameters)
{
  std::string s;
  is >> s;
  assert(s == "width:");
  int width = -1;
  is >> width;

  is >> s;
  assert(s == "height:");
  int height = -1;
  is >> height;

  is >> s;
  assert(s == "initialization:");
  Initialization initialization = Initialization::random;
  is >> initialization;

  is >> s;
  assert(s == "rng_seed:");
  int rng_seed = 0;
  is >> rng_seed;

  parameters = Parameters(width,height,initialization,rng_seed);

  return is;
}

bool ribi::prswt::operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.GetHeight() == rhs.GetHeight()
    && lhs.GetInitialization() == rhs.GetInitialization()
    && lhs.GetRngSeed() == rhs.GetRngSeed()
    && lhs.GetWidth() == rhs.GetWidth()
  ;
}

bool ribi::prswt::operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
