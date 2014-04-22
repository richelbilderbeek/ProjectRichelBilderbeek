#include <algorithm>
#include <cassert>
#include <vector>

#include <set>
int main()
{
  //Compare two identical std::vectors: prefer operator==
  {
    const std::vector<int> v { 0,1,2 };
    const std::vector<int> w { 0,1,2 };

    //Preferred syntax
    assert(v == w);
    //Less preferred, no unexpected behaviour
    assert(std::equal(v.begin(),v.end(),w.begin()));
  }
  //Compare two different std::vectors: prefer operator==
  {
    const std::vector<int> v { 0,1,2   };
    const std::vector<int> w { 0,1,2,3 };

    //Preferred syntax
    assert(v != w);
    //Less preferred, unexpected behaviour:
    //Only tests 3 (the size of v) elements
    //v and w do match for these
    assert(std::equal(v.begin(),v.end(),w.begin()));
    //Might result in access violations (as it might read v[3])?
    //assert(!std::equal(w.begin(),w.end(),v.begin()));
  }
  //Compare two container types: use std::equal
  {
    const std::vector<int> v { 0,1,2 };
    //Sorted container, will result in {0,1,2}
    const std::set<int> w { 2,1,0 };
    //This syntax does not work here anymore
    //assert(v == w);
    //Preferred syntax in this situation
    assert(std::equal(v.begin(),v.end(),w.begin()));
  }
}
