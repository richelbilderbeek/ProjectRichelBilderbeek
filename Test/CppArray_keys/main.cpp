#include <cassert>
#include <map>
#include <vector>

//Modeled after the PHP function with the same name
template <class T,class U>
const std::vector<T> array_keys(const std::map<T,U>& m)
{
  std::vector<T> v;
  for (const std::pair<T,U>& p: m) { v.push_back(p.first); }
  return v;
}

//Modeled after the PHP function with the same name
#ifdef I_CAN_GET_THIS_TO_WORK_20131004
template <
  class T,
  class U,
  template <typename> class Array = std::vector,
  template <typename,typename> class Map = std::map
>
const Array<T> array_keys(const Map<T,U>& m)
{
  Array<T> v;
  for (const std::pair<T,U>& p: m) { v.push_back(p.first); }
  return v;
}
#endif

int main()
{
  const std::map<int,std::string> m
  {
    { 0, "Zero" },
    { 1, "One"  },
    { 2, "Two"  }
  };

  const std::vector<int> keys { array_keys(m) };
  const std::vector<int> expected { 0,1,2 };
  assert(keys == expected );
}

