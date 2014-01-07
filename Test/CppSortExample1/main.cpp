#include <algorithm>
#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#pragma GCC diagnostic pop

void AbsSortBoost(std::vector<int>& v) noexcept
{
  std::sort(
    v.begin(),
    v.end(),
      boost::bind(&std::labs,boost::lambda::_1)
    < boost::bind(&std::labs,boost::lambda::_2)
  );
}

void AbsSortLambda(std::vector<int>& v) noexcept
{
  std::sort(
    v.begin(),
    v.end(),
    [](const int a, const int b) { return std::abs(a) < std::abs(b); }
  );
}

int main()
{
  for (const auto f: { AbsSortBoost, AbsSortLambda } )
  {
    std::vector<int> v = { 4,-3,2,-1 };
    f(v);
    assert(v[0] == -1);
    assert(v[1] ==  2);
    assert(v[2] == -3);
    assert(v[3] ==  4);
  }
}
