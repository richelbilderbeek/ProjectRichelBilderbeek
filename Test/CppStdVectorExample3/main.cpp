#include <cassert>
#include <vector>

int main()
{
  std::vector<int> v { 2,3 };
  v.emplace(v.begin(),1);
  v.emplace(v.begin(),0);
  const std::vector<int> expected { 0,1,2,3 };
  assert(v == expected );
}
