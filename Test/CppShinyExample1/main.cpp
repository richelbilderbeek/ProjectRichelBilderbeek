#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>

#include "Shiny.h"
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppBubbleSort.htm
template <class T>
void BubbleSort(std::vector<T>& v)
{
  PROFILE_FUNC();
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
  PROFILE_FUNC();
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
  PROFILE_FUNC();
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
  PROFILE_FUNC();
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

  for (int i=0; i!=100; ++i)
  {
    std::clog << "%"; //Show progress
    std::vector<int> v1(v);
    std::vector<int> v2(v);
    std::vector<int> v3(v);
    std::vector<int> v4(v);
    PROFILER_UPDATE();
    BubbleSort(v1);
    InsertionSort(v2);
    SelectionSort(v3);
    SortVector(v4);
    assert(v1==v2);
    assert(v2==v3);
    assert(v3==v4);
  }
  std::clog << std::endl;

  #ifndef NDEBUG
  std::cout << "Finished debug mode" << std::endl;
  #else
  std::cout << "Finished release mode" << std::endl;
  #endif
  PROFILER_OUTPUT("shiny_output.txt");
}

/* shiny_output.txt content:

flat profile                               hits       self time      total time
<root>                                      0.0    598 ms   25%      3 s   125%
BubbleSort                                  1.0    938 ms   40%    938 ms   40%
InsertionSort                               1.0    524 ms   22%    524 ms   22%
SelectionSort                               1.0    900 ms   38%    900 ms   38%
SortVector                                  1.0      3 ms    0%      3 ms    0%

call tree                                  hits       self time      total time
<root>                                      0.0    598 ms   25%      3 s   125%
  BubbleSort                                1.0    938 ms   40%    938 ms   40%
  InsertionSort                             1.0    524 ms   22%    524 ms   22%
  SelectionSort                             1.0    900 ms   38%    900 ms   38%
  SortVector                                1.0      3 ms    0%      3 ms    0%

*/
