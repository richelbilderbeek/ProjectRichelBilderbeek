#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <vector>

///Obtain all permutations of a std::vector
///Examples:
/// {1    } -> { {1} }
/// {1,2  } -> { {1,2} , {2,1} }
/// {1,2,3} -> { {1,2,3} , {1,3,2} , {2,1,3} , {2,3,1} , {3,1,2} , {3,2,1} }
//From http://www.richelbilderbeek.nl/CppGetPermutations.htm
template <class T>
const std::vector<std::vector<T> > GetPermutations(std::vector<T> v)
{
  std::vector<std::vector<T> > w;
  w.push_back(v);
  while(std::next_permutation(v.begin(),v.end()))
  {
    w.push_back(v);
  }
  return w;
}


int main()
{
  assert(GetPermutations(std::vector<int>( {1        } ) ).size() ==   1);
  assert(GetPermutations(std::vector<int>( {1,2      } ) ).size() ==   2);
  assert(GetPermutations(std::vector<int>( {1,2,3    } ) ).size() ==   6);
  assert(GetPermutations(std::vector<int>( {1,2,3,4  } ) ).size() ==  24);
  assert(GetPermutations(std::vector<int>( {1,2,3,4,5} ) ).size() == 120);
}
