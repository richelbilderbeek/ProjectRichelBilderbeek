#include <cassert>
#include <cstdlib>
#include <set>
#include <vector>

int main()
{
  //Basic std::set operations
  {
    //An empty set
    std::set<int> s;
    assert(s.empty() && "A std::set is empty when created");

    //x is a random value
    const int x = std::rand();

    //x cannot be in the std::set yet
    assert(s.count(x)==0);

    //Add x to the std::set
    s.insert(x);
    assert(s.count(x)==1);

    //A std::set does not allow duplicates,
    //so again adding x has no effect
    s.insert(x);
    assert(s.count(x)==1);

    //Remove x from the set
    s.erase(x);
    assert(s.count(x)==0);
  }
  //Creating a std::set that orders its elements the other way around
  {
    std::set<int                   > s; //Default-ordered std::set
    std::set<int,std::greater<int> > t; //Other way around
    const int a = 3;
    const int b = 1;
    const int c = 2;
    s.insert(a); t.insert(a);
    s.insert(b); t.insert(b);
    s.insert(c); t.insert(c);
    std::vector<int> v; //For default-ordered std::set
    std::vector<int> w; //For other std::set

    std::copy(s.begin(),s.end(),std::back_inserter(v));
    std::copy(t.begin(),t.end(),std::back_inserter(w));

    assert(v.size() == 3);
    assert(w.size() == 3);
    assert(v[0] < v[1] && v[1] < v[2]);
    assert(w[0] > w[1] && w[1] > w[2]);
  }
}
