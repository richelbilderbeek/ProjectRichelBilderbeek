#include <memory>

struct MyClass {};

int main()
{
  const std::unique_ptr<const MyClass> p { new MyClass };

  //std::unique_ptr deletes p automatically
}
