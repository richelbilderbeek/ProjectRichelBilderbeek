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
  //Compare two identical std::vectors: prefer operator!=
  {
    const std::vector<boost::shared_ptr<int>> v { Create(2) };
    const std::vector<boost::shared_ptr<int>> w { Create(2) };

    //Mismatch: compares the memory addresses of the integers
    assert(v != w);
    //Less preferred, no unexpected behaviour
    assert(!std::equal(v.begin(),v.end(),w.begin()));
  }
  //Compare two identical std::vectors: prefer operator!=
  {
    const std::vector<boost::shared_ptr<int>> v { Create(2) };
    std::vector<boost::shared_ptr<int>> w(v);

    //Match: compares the memory addresses of the integers
    assert(v == w);
    //Less preferred, no unexpected behaviour
    assert(std::equal(v.begin(),v.end(),w.begin()));

    std::swap(*w.begin(),*(w.end()-1));

    assert(v != w);
    //Less preferred, no unexpected behaviour
    assert(!std::equal(v.begin(),v.end(),w.begin()));
  }
  //Compare two different containers
  {
    const std::vector<boost::shared_ptr<int>> v { Create(2) };
    std::set<boost::shared_ptr<int>> w(v.begin(),v.end());

    //Less preferred, no unexpected behaviour
    assert( (     std::equal(v.begin(),v.end(),w.begin())
              || !std::equal(v.begin(),v.end(),w.begin()) )
      && "Unknown if the shared_ptrs are allocated in memory at incremental adresses"
    );
  }
}
