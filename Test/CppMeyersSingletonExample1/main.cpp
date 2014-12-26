struct Widget {};

//Meyers' Singleton
Widget& instance()
{
  static Widget w;
  return w;
}

int main()
{
  const auto w = instance();
}
