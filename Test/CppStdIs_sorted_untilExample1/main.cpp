#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

int main()
{
  const std::vector<int> v { 1,2,3,5,4 };
  const std::vector<int>::const_iterator last_sorted
    = std::is_sorted_until(std::begin(v),std::begin(v) + 2);
  assert(*last_sorted == 3);
}
