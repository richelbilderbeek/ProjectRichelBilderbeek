#include <algorithm>
#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

template <class T>
bool IsSubset(const std::vector<T>& v, const std::vector<T>& w) noexcept
{
  assert(std::is_sorted(v.begin(),v.end()));
  assert(std::is_sorted(w.begin(),w.end()));
  std::vector<T> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),
    std::back_inserter(x));
  return x.size() == v.size() || x.size() == w.size();
}

int main()
{
  {
    const std::vector<int> super { 0,1,4,9,16,25,36 };
    const std::vector<int> sub_y { 0,  4,  16,   36 };
    const std::vector<int> sub_n { 0,1,2            };
    assert(IsSubset(super,super));
    assert(IsSubset(sub_y,sub_y));
    assert(IsSubset(sub_n,sub_n));

    assert(IsSubset(super,sub_y));
    assert(IsSubset(sub_y,super));

    assert(!IsSubset(super,sub_n));
    assert(!IsSubset(sub_n,super));

    assert(!IsSubset(sub_y,sub_n));
    assert(!IsSubset(sub_n,sub_y));
  }
  {
    std::vector<boost::shared_ptr<int>> super;
    for (int i=0; i!=10; ++i)
    {
      boost::shared_ptr<int> p(new int(i));
      super.push_back(p);
    }
    std::vector<boost::shared_ptr<int>> sub_y
    {
      super[1],
      super[3],
      super[5],
      super[8]
    };
    std::vector<boost::shared_ptr<int>> sub_n;
    for (int i=0; i!=3; ++i)
    {
      boost::shared_ptr<int> p(new int(i));
      sub_n.push_back(p);
    }

    std::sort(super.begin(),super.end());
    std::sort(sub_y.begin(),sub_y.end());
    std::sort(sub_n.begin(),sub_n.end());
    assert(IsSubset(super,super));
    assert(IsSubset(sub_y,sub_y));
    assert(IsSubset(sub_n,sub_n));

    assert(IsSubset(super,sub_y));
    assert(IsSubset(sub_y,super));

    assert(!IsSubset(super,sub_n));
    assert(!IsSubset(sub_n,super));

    assert(!IsSubset(sub_y,sub_n));
    assert(!IsSubset(sub_n,sub_y));
  }
  assert(1==2);
}
