#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{

  const std::vector<int> v{1,2,3};
  const std::vector<int> w{2,3,4};
  //Calculate the sum of the products:
  //
  // 1*2 + 2*3 + 3*4 = 2 + 6 + 12 = 20
  //
  const int sip = std::inner_product(
    std::begin(v),
    std::end(v),
    std::begin(w),
    0.0,
    std::plus<int>(), //Sum the results
    std::multiplies<int>() //Multiply the elements from the two vectors
  );
  assert(sip == 20);

  // Because summing the product is so common,
  // it is supplied as a default
  const int sip_too = std::inner_product(
    std::begin(v),
    std::end(v),
    std::begin(w),
    0.0
  );
  assert(sip_too == sip);
}
