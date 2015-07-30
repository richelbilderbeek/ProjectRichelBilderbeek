#include <cassert>

void CopyArray(
  const int * const source,
  int * const target,
  const int size
)
{
  for (int i=0; i!=size; ++i)
  {
    target[i] = source[i];
  }
}

int main()
{
  const int sz = 5;
  const int v[sz] = {1,4,9,16,25};
  int w[sz] = {0,0,0, 0, 0};
  CopyArray(v,w,sz);

  for (int i=0; i!=sz; ++i)
  {
    assert(v[i] == w[i]);
  }
}
