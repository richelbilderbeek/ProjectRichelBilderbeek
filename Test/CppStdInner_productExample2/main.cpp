#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{

  const std::vector<int> v{1,2,3};
  const std::vector<int> w{2,3,4};

  //Calculate the sum of the products, where w must be square:
  // SUM(a * b^2)
  // = 1*(2)^2 + 2*(3)^2 + 3*(4)^2
  // = 1*4     + 2*9     + 3*16
  // = 4       + 18      + 48
  // = 70
  const int sip = std::inner_product(
    std::begin(v),
    std::end(v),
    std::begin(w),
    0,
    std::plus<int>(), //Sum the results
    [](const int a, const int b) { return a * b * b; } //b must be square
  );
  assert(sip == 70);
}
