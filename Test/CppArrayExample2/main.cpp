#include <array>
#include <cassert>
#include <iostream>

struct Base { int m_base; };
struct Derived : public Base { int m_derived; };

int main()
{
  //Example adapted from Stoustrup, 'A Tour of C++, 2014, page 123
  //Using a plain array
  {
    const int sz = 3;
    Derived v[sz];

    //Initialize
    for (int i=0; i!=sz; ++i) { v[i].m_base = i+1; v[i].m_derived = i+4; }

    //Displays
    // 1 4
    // 2 5
    // 3 6
    for (int i=0; i!=sz; ++i) { std::cout << v[i].m_base << " " << v[i].m_derived << '\n'; }

    const Base * const w = v; //Disaster waiting to happen

    //Displays
    // 1
    // 4
    // 2
    //because a Base has a different offset than Derived
    for (int i=0; i!=sz; ++i) { std::cout << w[i].m_base << '\n'; }
  }
  //Using a std::array instead
  {
    const int sz = 3;
    std::array<Derived,sz> v;

    //Initialize
    for (int i=0; i!=sz; ++i) { v[i].m_base = i+1; v[i].m_derived = i+4; }

    //Displays
    // 1 4
    // 2 5
    // 3 6
    for (int i=0; i!=sz; ++i) { std::cout << v[i].m_base << " " << v[i].m_derived << '\n'; }

    //Cannot compile. Thanks compiler!
    //Base * const w = v; //Disaster waiting to happen
  }
}
