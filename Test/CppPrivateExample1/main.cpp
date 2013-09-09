class MyClass
{
  public:
  void YouCanCallMe() const {}
  private:
  void YouCannotCallMe() const {}
};

int main()
{
  const MyClass t;
  t.YouCanCallMe();
  //t.YouCannotCallMe(); //YouCannotCallMe is private
}
