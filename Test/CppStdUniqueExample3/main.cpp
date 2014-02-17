#include <algorithm>
#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

const std::vector<boost::shared_ptr<int>> Create()
{
  const boost::shared_ptr<int> a { new int(1) };
  const boost::shared_ptr<int> b { new int(2) };
  std::vector<boost::shared_ptr<int>> v {
    a,b,a,a,b,b,a,a,a,a,b,b,b,b
  };
  return v;
}


int main()
{
  {
    std::vector<boost::shared_ptr<int>> v { Create() };
    assert(std::count(v.begin(),v.end(),nullptr) == 0);
    std::sort(v.begin(),v.end());
    assert(std::count(v.begin(),v.end(),nullptr) == 0);
    v.erase(std::unique(v.begin(),v.end()),v.end());
    assert(std::count(v.begin(),v.end(),nullptr) == 0);
    assert(v.size() == 2);
  }
  {
    std::vector<boost::shared_ptr<int>> v { Create() };
    assert(std::count(std::begin(v),std::end(v),nullptr) == 0);
    std::sort(std::begin(v),std::end(v));
    assert(std::count(std::begin(v),std::end(v),nullptr) == 0);
    v.erase(std::unique(std::begin(v),std::end(v)),std::end(v));
    assert(std::count(std::begin(v),std::end(v),nullptr) == 0);
    assert(v.size() == 2);
  }
  {
    std::vector<boost::shared_ptr<int>> v { Create() };
    assert(std::count(std::begin(v),std::end(v),nullptr) == 0);
    std::sort(std::begin(v),std::end(v));
    assert(std::count(std::begin(v),std::end(v),nullptr) == 0);

    std::vector<boost::shared_ptr<int>> w;
    std::unique_copy(std::begin(v),std::end(v),std::back_inserter(w));
    assert(std::count(std::begin(w),std::end(w),nullptr) == 0);
    assert(w.size() == 2);
  }
}
