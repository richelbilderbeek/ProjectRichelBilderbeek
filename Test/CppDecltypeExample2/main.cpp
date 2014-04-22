#include <algorithm>
#include <cassert>

std::vector<int> TimesTwo1(const std::vector<int>& v)
{
  //Create an empty return vector
  std::remove_const<std::remove_reference<decltype(v)>::type>::type w;

  //Define the type of an element
  typedef decltype(w)::value_type Value;

  //Insert elements in return vector
  std::transform(
    v.begin(),v.end(),std::back_inserter(w),
    [](const Value a) { return a * 2; }
  );
  return w;
}

std::vector<int> TimesTwo2(const std::vector<int>& v)
{
  //Create a return type vector from the input vector
  auto w(v);

  //Define the type of an element
  typedef decltype(w)::value_type Value;

  //Modify elements in return vector
  std::for_each(w.begin(),w.end(),[](Value& a) { a *= 2; } );
  return w;
}

auto TimesTwo3(const std::vector<int>& v) -> decltype(std::remove_reference<decltype(v)>::type{})
{
  auto w(v);
  typedef decltype(w)::value_type Value;
  std::for_each(w.begin(),w.end(),[](Value& a) { a *= 2; } );
  return w;
}

template <class T>
auto TimesTwo4(const std::vector<T>& v) -> decltype(std::vector<T>{})
{
  auto w(v);
  std::for_each(w.begin(),w.end(),[](T& a) { a *= 2; } );
  return w;
}

template <class T>
std::vector<T> TimesTwo5(const std::vector<T>& v)
{
  auto w(v);
  std::for_each(w.begin(),w.end(),[](T& a) { a *= 2; } );
  return w;
}

int main()
{
  const std::vector<int> v { 1,2,3 };
  const std::vector<int> e { 2,4,6 };
  assert(TimesTwo1(v) == e);
  assert(TimesTwo2(v) == e);
  assert(TimesTwo3(v) == e);
  assert(TimesTwo4(v) == e);
  assert(TimesTwo5(v) == e);
}
