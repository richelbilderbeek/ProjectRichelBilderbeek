#include <cassert>
#include <memory>

int main()
{
  const int value{42};
  std::shared_ptr<const int> p(new int(value));
  assert(*p == value);

  //Remove constness
  std::shared_ptr<int> q{std::const_pointer_cast<int>(p)};
  assert(*q == value);
}
