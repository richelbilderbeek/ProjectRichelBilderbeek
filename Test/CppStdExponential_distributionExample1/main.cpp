#include <cassert>
#include <iostream>
#include <random>

int main()
{
  const double lambda{1.0};
  std::exponential_distribution<double> d(lambda);
  assert(lambda == d.lambda());

  const int rng_seed{42};
  std::mt19937 rng(rng_seed);

  for (int i=0; i!=20; ++i)
  {
    std::cout << d(rng) << '\n';
  }
}

/*

1.5923
0.202649
1.51272
0.908447
0.590289
0.105333
0.614796
0.406028
0.154162
1.05236
0.0580652
1.28013
2.78958
0.000779068
4.85512
0.960978
0.945856
0.00709139
0.0233325
0.743966
Press <RETURN> to close this window...

*/
