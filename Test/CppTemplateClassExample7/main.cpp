//Does not compile
//
//Unknown how to compile this

enum class CopyPolicy { allow, forbid };

template <class T, CopyPolicy copy_policy>
struct MyClass
{
  //All MyClass template classes must have a same constructor
  MyClass<T,copy_policy>(const T& x) : m_x(x) {}
  private:
  T m_x;
};

template <class T>
struct MyClass<T,CopyPolicy::forbid>
{
  MyClass<T,CopyPolicy::forbid>(const MyClass<T,CopyPolicy::forbid>&) = delete;
  MyClass<T,CopyPolicy::forbid>& operator=(const MyClass<T,CopyPolicy::forbid>&) = delete;
};

template <class T>
struct MyClass<T,CopyPolicy::allow>
{

};

int main()
{

  const MyClass<int,CopyPolicy::allow > a(123); //Use general constructor: Does not compile
  const MyClass<int,CopyPolicy::forbid> b(123); //Use general constructor: Does not compile

  const decltype(a) c(a); //Should compile
  const decltype(b) d(b); //Should not compile
}
