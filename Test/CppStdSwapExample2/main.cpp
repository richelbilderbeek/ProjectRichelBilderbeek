#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
  std::vector<int> v { 0,1,2 };
  // {0,1,2} -> {2,1,0}
  //  ^                  x
  //      ^              v.back()
  //
  // {2,1,0} -> {2,0,1}
  //    ^                x
  //      ^              v.back()
  //
  // {2,0,1} -> {2,0,1}
  //      ^              x
  //      ^              v.back()
  //
  for (int& x: v)
  {
    std::swap(x,v.back());
  }

  const std::vector<int> expected { 2,0,1 };
  assert(v == expected);
}
