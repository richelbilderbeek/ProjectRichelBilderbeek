#include <cassert>
#include <string>
#include <typeinfo>

int main()
{
  assert(std::string(typeid(int).name())=="i");
  assert(std::string(typeid(double).name())=="d");
  assert(std::string(typeid(std::string).name())=="Ss");
}
