#include <array>
#include <cassert>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

struct Base { int m_base; };
struct Derived : public Base { int m_derived; };

void f()
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

void g()
{
  {
    const int sz = 5;
    int v[sz];
    assert(sizeof(v) / sizeof(int) == sz);
  }
  {
    const int sz = (std::rand() % 2) - 100;
    assert(sz < 0 && "sz will always be negative, yet I can create an array of this size");
    int v[sz]; //Will be accepted
    assert(static_cast<int>(sizeof(v) / sizeof(int)) == sz); //Will not protect you
    //v[0] = 0; //Crashes the program
  }
  {
    const int sz = (std::rand() % 2) - 100;
    assert(sz < 0 && "sz will always be negative, yet I can create an array of this size");
    std::vector<int> v(sz); //Throws std::bad_alloc
  }
}

int main()
{
  f();
  g();
}

