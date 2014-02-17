#include <cassert>
#include <algorithm>
#include <vector>

int main()
{
  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  v.push_back(1);
  v.push_back(2);
  v.push_back(2);
  v.push_back(2);
  v.push_back(3);
  v.push_back(3);
  v.push_back(3);
  v.push_back(3);
  std::vector<int> w;
  std::unique_copy(v.begin(),v.end(),std::back_inserter(w));
  assert(w[0]==0);
  assert(w[1]==1);
  assert(w[2]==2);
  assert(w[3]==3);
}
