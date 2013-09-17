#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

void ReplaceNegativeByZero(std::vector<int>& v)
{
  std::replace_if(v.begin(),v.end(),
    std::bind2nd(std::less<int>(),0),0);
}

int main()
{
  const std::vector<int> input    { -1, 1,-1, 1 };
  const std::vector<int> expected {  0, 1, 0, 1 };

  std::vector<int> result { input };
  ReplaceNegativeByZero(result);

  assert(result == expected);
}
