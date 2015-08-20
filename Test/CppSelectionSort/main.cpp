#include <algorithm>
#include <vector>

//From http://www.richelbilderbeek.nl/CppSelectionSort.htm
template <typename T>
void SelectionSort(std::vector<T>& v)
{
  const int size{static_cast<int>(v.size())};
  for(int i=0; i!=size-1; ++i)
  {
    for(int j=i+1; j!=size; ++j)
    {
      if (v[i]> v[j])
      {
        std::swap(v[i],v[j]);
      }
    }
  }
}

#include <cassert>

int main()
{
  //Create a std::vector<int> with random values
  std::vector<int> v;
  for(int i=0; i!=100; ++i) v.push_back(std::rand() % 1000);
  //Create a copy of this std::vector
  std::vector<int> v1(v);
  //Sort v using std::sort
  std::sort(std::begin(v),std::end(v));
  //Sort v1 using BubbleSort
  SelectionSort(v1);
  //Assert they are equal
  assert(v1==v);
}
