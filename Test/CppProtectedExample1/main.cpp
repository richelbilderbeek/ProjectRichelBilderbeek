struct Base
{
  Base(const int x = 0) : m_x(x) {}
  virtual ~Base() {}

  protected:
  int m_x;
};

struct Derived : public Base
{
  void SetX(const int x) { m_x = x; } //For a derived class, m_x is public
};

int main()
{
  Base b;
  //b.m_x = 0; //Not allowed! Only derived classes have access to Base::m_x

  Derived d;
  d.SetX(42);
}
