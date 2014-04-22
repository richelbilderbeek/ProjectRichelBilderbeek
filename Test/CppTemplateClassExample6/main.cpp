enum class CopyPolicy { allow, forbid };

template <class T, CopyPolicy copy_policy = CopyPolicy::allow> struct MyClass;

template <class T>
struct MyClass<T,CopyPolicy::forbid>
{
  MyClass(const T& x) : m_x(x) {}
  MyClass<T,CopyPolicy::forbid>(const MyClass<T,CopyPolicy::forbid>&) = delete;
  MyClass<T,CopyPolicy::forbid>& operator=(const MyClass<T,CopyPolicy::forbid>&) = delete;
  private:
  T m_x;
};

template <class T>
struct MyClass<T,CopyPolicy::allow>
{
  MyClass(const T& x) : m_x(x) {}
  private:
  T m_x;
};

int main()
{
  const MyClass<int,CopyPolicy::allow> a(123);
  const MyClass<int,CopyPolicy::forbid> b(123);

  const MyClass<int> c(a);
  //const MyClass<int,IntCopyPolicy::forbid> d(b); //Won't compile
}
