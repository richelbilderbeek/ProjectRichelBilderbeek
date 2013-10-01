#include <cassert>
#include <vector>

int main()
{
  std::vector<int> v { 1,4,9,16,25 };

  const std::size_t index = 2;
  assert(v[index] == 9 && "Erase the 9");
  v.erase( v.begin() + index);

  const std::vector<int> expected { 1,4,16,25 };
  assert(v == expected );
}
