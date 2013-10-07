#include <algorithm>
#include <cassert>
#include <vector>

///Modeled after the PHP function array_intersect
template <class T>
const std::vector<T> array_intersect(
  const std::vector<T>& v,
  const std::vector<T>& w)
{
  assert(std::is_sorted(v.begin(),v.end()));
  assert(std::is_sorted(w.begin(),w.end()));
  std::vector<T> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),std::back_inserter(x));
  return x;
}

int main()
{

  //Integers
  const std::vector<int> a { 0,1,2, 3, 4, 5 };

  //Squares
  const std::vector<int> b { 0,1,4,16,25,36 };

  //Zero, one and four are common in both arrays
  const std::vector<int> expected { 0,1,4 };

  //array_intersect will return the following form
  const std::vector<int> result { array_intersect(a,b) };

  assert(expected == result);

}
