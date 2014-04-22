#include <cassert>
#include <utility>

struct MyClass
{
  MyClass(const int x = 0) noexcept : m_x(x) {}
  MyClass(MyClass&& other) noexcept : m_x(other.m_x)
  {
    const_cast<int&>(other.m_x) = 0;
  }
  MyClass(const MyClass&) = delete;
  MyClass& operator=(const MyClass&) = delete;

  int GetX() const noexcept { return m_x; }

  private:
  ///'const int' is trivial, imaging this being a 'const Database' instead
  const int m_x;
};

int main()
{
  MyClass a(42);
  assert(a.GetX() == 42);

  //Initialize b with the internals of a,
  //leave a without its internals
  const MyClass b { std::move(a) };

  assert(a.GetX() == 0);
  assert(b.GetX() == 42);
}
