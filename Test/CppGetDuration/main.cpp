#include <chrono>
#include <iostream>

template <class Function>
long long int GetDuration(const Function& function)
{
  const auto t_begin = std::chrono::system_clock::now();

  function();

  const auto t_end = std::chrono::system_clock::now();
  const long long int n_msecs{
    std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count()
  };
  return n_msecs;
}

void ShowDots()
{
  for (int i=0; i!=100000; ++i) { std::cout << "." << std::flush; }
}

int main()
{
  std::cout << "Process lasted " << GetDuration(ShowDots) << " msecs" << std::endl;
}
