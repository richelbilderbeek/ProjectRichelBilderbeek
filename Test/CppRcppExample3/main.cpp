#include <numeric>
#include <cassert>
#include <vector>

// [[Rcpp::export]]
int DoMagic(const std::vector<int>& v)
{
  return std::accumulate(
    std::begin(v),
    std::end(v),
    42
  );
}

int main()
{
  std::vector<int> v;
  v.push_back(-1);
  v.push_back(0);
  v.push_back(1);
  assert(DoMagic(v) == 42);
}
