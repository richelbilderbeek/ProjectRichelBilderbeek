#include <algorithm>
#include <vector>

///Sort a std::vector using insertion sort
///From http://www.richelbilderbeek.nl/CppInsertionSort.htm
template <typename T>
void InsertionSort(std::vector<T>& v)
{
  const int size = v.size();
  for(int i=1; i!=size; ++i)
  {
    for(int j=0; j<i; ++j)
    {
      if (v[j] > v[i])
      {
        const int temp = v[j];
        v[j] = v[i];
        for(int k=i; k>j; --k) { v[k] = v[k-1]; }
        v[j+1] = temp;
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
  InsertionSort(v1);
  //Assert they are equal
  assert(v1==v);
}
