struct MyClass {};

int main()
{
  const MyClass * const p = new MyClass;

  //Use p

  delete p; //Do not forget to delete p
}
