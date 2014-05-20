#include <array>
#include <cassert>
#include <iostream>

int main()
{
  //Create a Y-X ordered 2D std::array
  static const int n_rows = 2;
  static const int n_cols = 3;
  std::array<std::array<int,n_cols>,n_rows> v;

  //Must be initialized
  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      //Use std::array<T,U>::at to check for range
      v[y][x] = x + (y * n_cols);
      assert(v.at(y).at(x) >= 0);
    }
  }

  for (const auto row: v)
  {
    for (const auto cell: row)
    {
      std::cout << cell << " ";
    }
    std::cout << '\n';
  }
}

/*

0 1 2
3 4 5
Press <RETURN> to close this window...

*/
