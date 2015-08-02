#include <chrono>

void WaitStl(const double n_secs) noexcept
{
  const std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
  while (1)
  {
    const std::chrono::system_clock::duration d = std::chrono::system_clock::now() - t;
    const long long int n_msecs_passed{std::chrono::duration_cast<std::chrono::milliseconds>(d).count()};
    const double secs_passed{static_cast<double>(n_msecs_passed) / 1000.0};
    if (secs_passed > n_secs) return;
  }
}


#include <boost/timer.hpp>

void WaitBoost(const double n_secs) noexcept
{
  boost::timer t;
  while (t.elapsed() < n_secs) {}
}

#include <iostream>

int main()
{
  for (int i=0; i!=10; ++i)
  {
    std::cout << "Waiting 100 msecs using STL" << std::endl;
    WaitStl(0.1);
  }
  for (int i=0; i!=10; ++i)
  {
    std::cout << "Waiting 100 msecs using Boost" << std::endl;
    WaitBoost(0.1);
  }
}
