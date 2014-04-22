#include <cassert>
#include <functional>
#include <numeric>
#include <vector>

int main()
{
  std::vector<int> v;
  v.push_back(1);
  v.push_back(4);
  v.push_back(9);

  std::vector<int> w;

  std::adjacent_difference(v.begin(),v.end(),
    std::back_inserter(w));

  assert(w[0] == 1); //v[0]
  assert(w[1] == 3); //v[1]-v[0]
  assert(w[2] == 5); //v[2]-v[1]

  std::vector<int> x;

  std::adjacent_difference(v.begin(),v.end(),
    std::back_inserter(x),std::multiplies<int>());

  assert(x[0] ==  1); //v[0]
  assert(x[1] ==  4); //v[1]*v[0]
  assert(x[2] == 36); //v[2]*v[1]
}
