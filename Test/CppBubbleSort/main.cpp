#include <algorithm>
#include <vector>

//From http://www.richelbilderbeek.nl/CppBubbleSort.htm
template <class T>
void BubbleSort(std::vector<T>& v)
{
  const int size{static_cast<int>(v.size())};
  for(int i=0; i!=size-1; ++i)
  {
    for(int j=0; j!=size-i-1; ++j)
    {
      if(v[j] > v[j+1])
      {
        std::swap(v[j],v[j+1]);
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
  BubbleSort(v1);
  //Assert they are equal
  assert(v1==v);
}
