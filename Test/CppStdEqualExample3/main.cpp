#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

const std::vector<boost::shared_ptr<int>> Create(const int n)
{
  assert(n >= 0);
  std::vector<boost::shared_ptr<int>> v;
  for (int i=0; i!=n; ++i)
  {
    const boost::shared_ptr<int> p(new int(i));
    v.push_back(p);
  }
  return v;
}

int main()
{
  //Compare two sets with different constness
  {
    std::vector<boost::shared_ptr<int>> v { Create(2) };
    const std::set<boost::shared_ptr<      int>> w(v.begin(),v.end());
    const std::set<boost::shared_ptr<const int>> x(v.begin(),v.end());
    assert(std::equal(w.begin(),w.end(),x.begin()));
  }
}
