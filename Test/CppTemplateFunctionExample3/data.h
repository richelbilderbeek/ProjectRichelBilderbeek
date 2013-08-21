#ifndef DATA_H
#define DATA_H

#include <string>

struct Data
{
  Data(const int i, const double d, const std::string& s);
  int m_int;
  double m_double;
  std::string m_string;
};

template <class T> const T& Get(const Data&);
template <> const int& Get<int>(const Data& d);
template <> const double& Get<double>(const Data& d);
template <> const std::string& Get<std::string>(const Data& d);

#endif // DATA_H
