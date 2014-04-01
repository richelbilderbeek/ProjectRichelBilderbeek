
#include <algorithm>
#include <functional>
#include <vector>

///IsSorted checks if a container is sorted.
///From http://www.richelbilderbeek.nl/CppIsSorted.htm
template <class T>
bool IsSortedStl98(const T& v)
{
  return std::adjacent_find(
    v.begin(),
    v.end(),
    std::greater<typename T::value_type>()) == v.end();
}

///IsSorted checks if a std::vector is sorted.
///From http://www.richelbilderbeek.nl/CppIsSorted.htm
template <class T>
bool IsSortedStl98VectorOnly(const std::vector<T>& v)
{
  return std::adjacent_find(
    v.begin(),
    v.end(),
    std::greater<T>()) == v.end();
}

///IsSorted checks if a container is sorted.
///From http://www.richelbilderbeek.nl/CppIsSorted.htm
template <class T>
bool IsSortedStl11(const T& v)
{
  return is_sorted(v.begin(),v.end());
}

#include <cassert>

int main()
{
  std::vector<int> v;
  v.push_back(3);
  v.push_back(2);
  v.push_back(5);
  v.push_back(1);
  v.push_back(0);

  assert(!IsSortedStl98(v));
  assert(!IsSortedStl11(v));

  std::sort(v.begin(),v.end());

  assert(IsSortedStl98(v));
  assert(IsSortedStl11(v));
}
