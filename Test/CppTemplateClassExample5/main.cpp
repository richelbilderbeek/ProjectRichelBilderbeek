enum class IntCopyPolicy { allow, forbid };

template <IntCopyPolicy copy_policy> struct Int;

template <>
struct Int<IntCopyPolicy::forbid>
{
  Int(const int x) : m_x(x) {}
  Int<IntCopyPolicy::forbid>(const Int<IntCopyPolicy::forbid>&) = delete;
  Int<IntCopyPolicy::forbid>& operator=(const Int<IntCopyPolicy::forbid>&) = delete;
  private:
  int m_x;
};

template <>
struct Int<IntCopyPolicy::allow>
{
  Int(const int x) : m_x(x) {}
  private:
  int m_x;
};

int main()
{
  const Int<IntCopyPolicy::allow> a(123);
  const Int<IntCopyPolicy::forbid> b(123);

  const Int<IntCopyPolicy::allow> c(a);
  //const Int<IntCopyPolicy::forbid> d(b); //Won't compile
}
