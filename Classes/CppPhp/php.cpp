#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "php.h"

#include <cassert>
#include <iomanip>

#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

std::string ribi::php::implode(
  const std::string& seperator,
  const std::vector<std::string>& v) noexcept
{
  std::string s;
  if (v.empty()) return s;
  s += v[0];
  const std::size_t sz = v.size();
  for (std::size_t i=1; i!=sz; ++i)
  {
    s += seperator + v[i];
  }
  return s;
}

std::string ribi::php::implode(
  const std::string& seperator,
  const std::vector<int>& v) noexcept
{
  std::stringstream s;
  s << std::setprecision(17);

  if (v.empty()) return s.str();
  s << v[0];
  const std::size_t sz = v.size();
  for (std::size_t i=1; i!=sz; ++i)
  {
    s << seperator << v[i];
  }
  return s.str();
}

std::string ribi::php::implode(
  const std::string& seperator,
  const std::array<double,3>& v) noexcept
{
  std::string s;
  if (v.empty()) return s;
  s += boost::lexical_cast<std::string>(v[0]);
  const std::size_t sz = v.size();
  for (std::size_t i=1; i!=sz; ++i)
  {
    s += seperator + boost::lexical_cast<std::string>(v[i]);
  }
  return s;
}

template <> std::string
  ribi::php::php_private::TypeToStr<int>() noexcept { return "int"; }
template <> std::string
  ribi::php::php_private::TypeToStr<double>() noexcept { return "float"; }
