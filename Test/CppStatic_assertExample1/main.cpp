#include <functional>

template <class T>
struct MyClass
{
  typedef T This_t;
  MyClass()
  {
    static_assert(!std::is_same<This_t,int>(),"MyClass cannot have int type");
  }
};


int main()
{
  static_assert(1+1==2,"One plus one equals two");
  //static_assert(1==2,"One is not equal to two"); //Won't compile

  const MyClass<double> a;
  //MyClass<int> b; //Won't compile
}
