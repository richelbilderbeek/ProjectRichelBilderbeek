#include <chrono>
#include <cmath>
#include <iostream>

int main()
{
  const std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
  const std::chrono::high_resolution_clock::time_point u = std::chrono::high_resolution_clock::now();

  //Burn some time
  for (int i=0; i!=100000000; ++i)
  {
    for (int j=0; j!=10; ++j)
    {
      std::sqrt(static_cast<double>(i + j));
    }
  }

  const std::chrono::system_clock::duration d = std::chrono::system_clock::now() - t;
  const std::chrono::system_clock::duration e = std::chrono::high_resolution_clock::now() - u;

  std::cout
    << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << " milliseconds" << '\n'
    << std::chrono::duration_cast<std::chrono::milliseconds>(e).count() << " milliseconds" << '\n'
    << std::endl;
}

/* Screen output:

7651 milliseconds
7651 milliseconds

Press <RETURN> to close this window...

*/
