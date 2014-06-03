#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
  {
    int a[] { 2,1,0 };
    assert(!std::is_sorted(std::begin(a),std::end(a)));
    std::sort(std::begin(a),std::end(a));
    assert(std::is_sorted(std::begin(a),std::end(a)));
  }
  {
    std::vector<int> v { 2,1,0 };
    assert(!std::is_sorted(std::begin(v),std::end(v)));
    std::sort(std::begin(v),std::end(v));
    assert(std::is_sorted(std::begin(v),std::end(v)));
  }
}
