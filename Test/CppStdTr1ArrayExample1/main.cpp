#include <tr1/array>
#include <cassert>

int main()
{
  const int sz = 3;
  std::tr1::array<int,sz> v;
  v[0] = 0;
  v[1] = 1;
  v[2] = 2;
  assert(v.size() == sz);
  assert(v[0] == 0);
  assert(v[1] == 1);
  assert(v[2] == 2);
}
