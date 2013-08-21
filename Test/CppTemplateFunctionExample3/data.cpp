#include "data.h"

#include <cassert>

Data::Data(const int i, const double d, const std::string& s)
  : m_int(i), m_double(d), m_string(s)
{
  assert(Get<int>(*this) == m_int);
  assert(Get<double>(*this) == m_double);
  assert(Get<std::string>(*this) == m_string);
}

template <> const int& Get<int>(const Data& d) { return d.m_int; }
template <> const double& Get<double>(const Data& d) { return d.m_double; }
template <> const std::string& Get<std::string>(const Data& d) { return d.m_string; }
