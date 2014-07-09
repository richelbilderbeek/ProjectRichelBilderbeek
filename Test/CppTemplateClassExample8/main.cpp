//FAILS TO COMPILE

/*

Problem: the two get member functions are overloads

struct MyClass
{
  double Get() const noexcept;
  int Get() const noexcept;

  private:
  double m_x;
};

For template functions, this works:

template <class T> T Get() noexcept;
template <> double Get() noexcept { return 12.34; }
template <> int Get() noexcept { return 42; }
*/

#include <cassert>


struct MyClass
{
  template <class T> T Get() const noexcept;
  template <> double Get() const noexcept { return 12.34; } //Does not compile
  template <> int Get() const noexcept { return 42; } //Does not compile


  private:
  double m_x;
};


int main()
{
  MyClass c;
  const auto x = c.Get<int>();
  const auto y = c.Get<double>();
  assert(x == 42);
  assert(y == 12.34);
}
