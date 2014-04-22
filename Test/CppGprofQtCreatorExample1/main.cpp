#include <algorithm>
#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppBubbleSort.htm
template <class T>
void BubbleSort(std::vector<T>& v)
{
  const int size = v.size();
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

//From http://www.richelbilderbeek.nl/CppInsertionSort.htm
template <typename T>
void InsertionSort(std::vector<T>& v)
{
  const int size = v.size();
  for(int i=1; i!=size; ++i)
  {
    for(int j=0; j!=i; ++j)
    {
      if (v[j]>v[i])
      {
        const int temp=v[j];
        v[j]=v[i];
        for(int k=i;k>j;--k) { v[k]=v[k-1]; }
        v[j+1]=temp;
      }
    }
  }
}

//From http://www.richelbilderbeek.nl/CppSelectionSort.htm
template <typename T>
void SelectionSort(std::vector<T>& v)
{
  const int size = v.size();
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

//From http://www.richelbilderbeek.nl/CppSortVector.htm
template <class T>
void SortVector(std::vector<T>& v)
{
  std::sort(v.begin(), v.end());
}

const std::vector<int> CreateShuffledVector(const std::size_t sz)
{
  std::vector<int> v(sz);

  int value = 0;
  BOOST_FOREACH(int& i,v)
  {
    i = value;
    ++value;
  }
  std::random_shuffle(v.begin(),v.end());
  return v;
}


int main()
{
  const std::vector<int> v = CreateShuffledVector(10000);

  std::vector<int> v1(v);
  std::vector<int> v2(v);
  std::vector<int> v3(v);
  std::vector<int> v4(v);

  BubbleSort(v1);
  InsertionSort(v2);
  SelectionSort(v3);
  SortVector(v4);

  assert(v1==v2);
  assert(v2==v3);
  assert(v3==v4);
}
