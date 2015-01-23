#include <cassert>

// [[Rcpp::export]]
int DoMagic(const int a, const int b)
{
  return 42 + a + b;
}

int main()
{
  assert(DoMagic(0,0) == 42);
}
