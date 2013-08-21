#include <cassert>
#include <cmath>
#include <string>

struct Data
{
  Data(const int i, const double d, const std::string& s)
    : m_int(i), m_double(d), m_string(s) {}
  int m_int;
  double m_double;
  std::string m_string;
};

template <class T> const T& Get(const Data&);
template <> const int& Get<int>(const Data& d) { return d.m_int; }
template <> const double& Get<double>(const Data& d) { return d.m_double; }
template <> const std::string& Get<std::string>(const Data& d) { return d.m_string; }

int main()
{
  const Data d(42,M_PI,"Hello world");
  assert( Get<int>(d) == 42);
  assert( Get<double>(d) == M_PI);
  assert( Get<std::string>(d) == "Hello world");
}
