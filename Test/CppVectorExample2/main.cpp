#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
  const std::vector<int> v_expected { 1,2,3,4,5,6,7 };
  std::vector<int> v { 0,1,0,2,0,0,3,4,0,5,0,0,6,7,0 };

  //The erase-remove idiom
  v.erase(std::remove(v.begin(),v.end(),0),v.end());

  assert(v == v_expected);
}
