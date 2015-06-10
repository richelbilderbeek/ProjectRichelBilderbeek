#include <cassert>
#include <cstring>
#include <vector>

int main()
{
  const std::vector<int> from = {1,4,9,16,25,36,49};
  std::vector<int> to(from.size());
  std::memcpy(&to[0],&from[0],from.size() * sizeof(int));
  assert(from==to);
}
