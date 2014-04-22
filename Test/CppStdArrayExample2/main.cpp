#include <array>
#include <cassert>

struct Data
{
  //Data() : m_v{    } {} //Not allowed
  Data() : m_v{ {} } {} //Allowed, implicit initialization with zeroes
  //Data() : m_v{ {0,0,0,0,0,0,0} } {} //Allowed, explicit initialization with zeroes
  //Data() : m_v{0,0,0,0,0,0,0} {} //Not allowed
  const std::array<int,7> m_v;
};

int main()
{
  Data d;
  for (int i=0; i!=7; ++i) { assert(d.m_v[i] == 0); }
}
