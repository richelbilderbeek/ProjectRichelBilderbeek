#include <algorithm>
#include <cassert>
#include <vector>

///Modeled after the PHP function array_merge
template <class T>
const std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w)
{
  std::vector<T> x { v };
  std::copy(w.begin(),w.end(),std::back_inserter(x));
  return x;
}

int main()
{
  const std::vector<int> a { 0,1,2 };
  const std::vector<int> b { 0,2,4,6 };

  //Concatenate the arrays
  const std::vector<int> expected { 0,1,2,0,2,4,6 };

  //Find the merged set, raw
  const std::vector<int> result = array_merge(a,b);
  assert(result == expected);
}
