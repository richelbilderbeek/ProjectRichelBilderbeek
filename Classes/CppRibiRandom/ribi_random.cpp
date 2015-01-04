//---------------------------------------------------------------------------
/*
RibiRandom, class for working with random numbers
Copyright (C) 2014-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRibiRandom.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "ribi_random.h"

#include <cassert>

#include <boost/random.hpp>

#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

struct ribi::Random::RandomImpl
{
  ///Use a random seed
  RandomImpl() : RandomImpl(std::random_device()()) {}
  ///Use a given seed
  RandomImpl(const int seed) : m_mt{seed} {}
  RandomImpl(const RandomImpl&) = delete;
  RandomImpl& operator=(const RandomImpl&) = delete;

  ///Obtain a random boolean
  bool GetBool() noexcept;

  ///Obtain a random lowercase character
  char GetChar() noexcept;

  ///Obtain a random number from zero to (and not including) one
  double GetFraction() noexcept;

  ///Obtain a random integer in range 'min' to and including 'max'
  int GetInt(const int min, const int max) noexcept;

  ///Obtain a random number from a normal distribution
  ///From http://www.richelbilderbeek.nl/CppGetRandomNormal.htm
  double GetNormal(const double mean = 0.0, const double sigma = 1.0) noexcept;

  ///Return a random string
  std::string GetString(const int length) noexcept;

  private:
  ///Random number generator
  std::mt19937 m_mt;
};

bool ribi::Random::RandomImpl::GetBool() noexcept
{
  const int i{GetInt(0,1)};
  const bool b{i % 2 == 0};
  return b;
}

char ribi::Random::RandomImpl::GetChar() noexcept
{
  const char c = 'a' + GetInt(0,25);
  assert(c >= 'a');
  assert(c <= 'z');
  return c;
}

int ribi::Random::RandomImpl::GetInt(const int min, const int max) noexcept
{
  std::uniform_int_distribution<int> d(min,max);
  //The random value x gets drawn here
  const int x{d(m_mt)};
  return x;
}

double ribi::Random::RandomImpl::GetFraction() noexcept
{
  static std::uniform_real_distribution<double> d(0.0,1.0);
  //The random value x gets drawn here
  const double x{d(m_mt)};
  return x;
}

double ribi::Random::RandomImpl::GetNormal(const double mean, const double sigma) noexcept
{
  std::normal_distribution<double> d(mean,sigma);
  //The random value x gets drawn here
  const double x{d(m_mt)};
  return x;
}

std::string ribi::Random::RandomImpl::GetString(const int length) noexcept
{
  std::string s;
  s.resize(length);
  std::generate(std::begin(s),std::end(s),
   [this](){ return this->GetChar(); }
  );
  return s;
}

ribi::Random::Random() : m_impl{new RandomImpl}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::Random::Random(const int seed) : m_impl{new RandomImpl(seed)}
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::Random::~Random()
{
  //Otherwise trouble with forward declarations
}

bool ribi::Random::GetBool() noexcept
{
  return m_impl->GetBool();
}

char ribi::Random::GetChar() noexcept
{
  return m_impl->GetChar();
}

double ribi::Random::GetFraction() noexcept
{
  return m_impl->GetFraction();
}

int ribi::Random::GetInt(const int min, const int max) noexcept
{
  return m_impl->GetInt(min,max);
}

double ribi::Random::GetNormal(const double mean, const double sigma) noexcept
{
  return m_impl->GetNormal(mean,sigma);
}

std::string ribi::Random::GetString(const int length) noexcept
{
  return m_impl->GetString(length);
}

std::string ribi::Random::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Random::GetVersionHistory() noexcept
{
  return {
    "2014-07-29: Version 1.0: initial version"
    "2014-12-27: Version 1.1: removed deprecated functions"
  };
}

#ifndef NDEBUG
void ribi::Random::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  Random r(42);
  {
    assert(r.GetFraction() >= 0.0);
    assert(r.GetFraction()  < 1.0);
  }
  {
    const auto s = r.GetString(99);
    assert(std::count(std::begin(s),std::end(s),s[0]) < 10);
  }
}
#endif
