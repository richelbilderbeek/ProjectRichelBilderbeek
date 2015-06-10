#include <cassert>
#include <iostream>
#include <random>

int main()
{
  const double mean{0.0};
  const double stddev{1.0};
  std::normal_distribution<double> d(mean,stddev);
  assert(d.mean() == mean);
  assert(d.stddev() == stddev);

  const int rng_seed{42};
  std::mt19937 rng(rng_seed);

  for (int i=0; i!=20; ++i)
  {
    std::cout << d(rng) << '\n';
  }
}

/*

-0.550234
0.515433
0.473861
1.36845
-0.916827
-0.124147
-2.01096
-0.492803
0.39258
-0.929185
0.0798318
-0.159516
0.0222218
-0.427793
-0.531817
-0.117476
0.222079
-0.767976
0.142465
-0.0346522
Press <RETURN> to close this window...

*/
