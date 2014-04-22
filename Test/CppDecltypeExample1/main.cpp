#include <cassert>
#include <initializer_list>
#include <stdexcept>

struct MyFirst
{
  MyFirst(const int x) : m_x{x} {}
  MyFirst(const std::initializer_list<int> x) : m_x{SetX(x)} {}
  const int m_x;
  private:
  static int SetX(const std::initializer_list<int> x)
  {
    if (x.size() != 1) throw std::logic_error("Need exactly one argument");
    return *x.begin();
  }
};

struct MySecond
{
  MySecond(const std::initializer_list<int> x) : m_x{SetX(x)} {}
  MySecond(const int x) : m_x{x} {}
  const int m_x;
  private:
  static int SetX(const std::initializer_list<int> x)
  {
    if (x.size() != 1) throw std::logic_error("Need exactly one argument");
    return *x.begin();
  }
};

struct MyThird
{
  MyThird(const std::initializer_list<int> x) : m_x{SetX(x)} {}
  MyThird(const int x) : m_x{x} {}
  const int m_x;
  private:
  static int SetX(const std::initializer_list<int> x)
  {
    if (x.size() != 1) throw std::logic_error("Need exactly one argument");
    return *x.begin();
  }
};

MyThird operator+(const MyFirst& a, const MySecond& b)
{
  return MyThird( a.m_x + b.m_x );
}

//Similar to
// * Stroustrup, B., The C++ programming language, 4th Edition,
//   section 6.3.6.3, 'The decltype() specifier', page 165
template<class T, class U>
auto Product(const T& a, const U& b) -> decltype(T{} + U{})
{
  return decltype(T{} + U{})(a.m_x * b.m_x);
}

int main()
{
  const MyFirst  x(2);
  const MySecond y(3);
  const MyThird sum(x + y); //operator+ works fine
  assert(sum.m_x == 5);
  const auto product(Product(x,y));
  assert(product.m_x == 6);
}
