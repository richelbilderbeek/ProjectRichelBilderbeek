#ifndef RIBI_PHP_H
#define RIBI_PHP_H

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <typeinfo>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

namespace php {

//Drop-in replacements for PHP function

//You are free to use functions from this namespace,
//but I did not intend you using these :)
namespace php_private {

///Convert a type to the PHP description
template <class T> std::string TypeToStr() noexcept
  { return "T"; }
template <> std::string TypeToStr<int>() noexcept;
template <> std::string TypeToStr<double>() noexcept;

template <class Iter>
void var_dump(Iter begin, const Iter end,
  std::ostream& os = std::cout) noexcept
{
  const std::size_t sz = std::distance(begin,end);
  os << "array(" << sz << ") {\n";
  std::size_t i=0;
  for (; begin!=end; ++begin)
  {
    os
      << "  [" << i << "]=>\n"
      << "  " << TypeToStr<typename Iter::value_type>() << "(" << (*begin) << ")\n";
    ++i;
  }
  std::cout << "}\n";
}

template <class Iter>
void var_dump_ptrs(Iter begin, const Iter end,
  std::ostream& os = std::cout) noexcept
{
  const std::size_t sz = std::distance(begin,end);
  os << "array(" << sz << ") {\n";
  std::size_t i=0;
  for (; begin!=end; ++begin)
  {
    os
      << "  [" << i << "]=>\n"
      << "  " << TypeToStr<typename Iter::value_type::element_type>() << "(" << (*(*begin)) << ")\n";
    ++i;
  }
  os << "}\n";
}

} //~php_private


template <class T>
std::vector<T> array_intersect(
  const std::vector<T>& v,
  const std::vector<T>& w) noexcept
{
  assert(std::is_sorted(std::begin(v),std::end(v)));
  assert(std::is_sorted(w.begin(),w.end()));
  std::vector<T> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),std::back_inserter(x));
  return x;
}

template <class T>
std::set<T> array_intersect(
  const std::set<T>& v,
  const std::set<T>& w) noexcept
{
  std::set<T> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),std::inserter(x,x.begin()));
  return x;
}

template <class T, class U>
std::vector<T> array_keys(const std::map<T,U>& m) noexcept
{
  std::vector<T> v;
  for (const std::pair<T,U>& p: m) v.push_back(p.first);
  return v;
}

template <class T>
std::vector<int> array_keys(const std::vector<T>& m) noexcept
{
  std::vector<int> v;
  const std::size_t sz = m.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    v.push_back(static_cast<int>(i));
  }
  return v;
}

template <class T>
std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w) noexcept
{
  std::vector<T> x { v };
  std::copy(w.begin(),w.end(),std::back_inserter(x));
  return x;
}

template <class T>
std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w,
  const std::vector<T>& x) noexcept
{
  std::vector<T> result { v };
  const std::vector<T> temp { array_merge(w,x) };
  std::copy(temp.begin(),temp.end(),std::back_inserter(result));
  return result;
}

template <class T>
std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w,
  const std::vector<T>& x,
  const std::vector<T>& y) noexcept
{
  std::vector<T> result { v };
  const std::vector<T> temp { array_merge(w,x,y) };
  std::copy(temp.begin(),temp.end(),std::back_inserter(result));
  return result;
}

template <class KeyType, class ValueType>
std::vector<ValueType> array_values(
  const std::map<KeyType,ValueType>& m) noexcept
{
  std::vector<ValueType> v;
  for (const auto& p: m)
  {
    v.push_back(p.second);
  }
  return v;
}

template <class KeyType, class ValueType>
std::map<KeyType,ValueType> array_values(
  const std::map<KeyType,ValueType>& m) noexcept
{
  std::map<KeyType,ValueType> v;
  KeyType key = 0;
  for (const auto& p: m)
  {
    v[key] = p.second;
    ++key;
  }
  return v;
}

std::string implode(
  const std::string& seperator,
  const std::vector<std::string>& v) noexcept;

std::string implode(
  const std::string& seperator,
  const std::vector<int>& v) noexcept;

std::string implode(
  const std::string& seperator,
  const std::array<double,3>& v) noexcept;

template <class T>
void var_dump(const T& t,
  std::ostream& os = std::cout) noexcept
{
  os
    << php_private::TypeToStr<T>()
    << "(" << t << ")\n";
}

template <class T>
void var_dump(const std::set<T>& s,
  std::ostream& os = std::cout) noexcept
{
  php_private::var_dump(s.begin(),s.end(),os);
}

template <class T, class U>
void var_dump(const std::pair<T,U>& p,
  std::ostream& os = std::cout) noexcept
{
  os
    << php_private::TypeToStr<T>() << "(" << p.first << ")"
    << " = > "
    << php_private::TypeToStr<U>() << "(" << p.second << ")"
    << '\n';
}

template <class T>
void var_dump(const std::vector<T>& s,
  std::ostream& os = std::cout) noexcept
{
  php_private::var_dump(s.begin(),s.end(),os);
}

template <class T, class U>
void var_dump(const std::map<T,U>& m,
  std::ostream& os = std::cout) noexcept
{
  typedef std::pair<T,U> Pair;
  const std::size_t sz = m.size();
  os << "array(" << sz << ") {\n";
  for (const Pair& p: m)
  {
    os
      << "  [" << p.first << "]=>\n"
      << "  " << php_private::TypeToStr<typename Pair::second_type>() << "(" << p.second << ")\n";
  }
  std::cout << "}\n";
}

template <class T>
void var_dump(const std::vector<boost::shared_ptr<T>>& s,
  std::ostream& os = std::cout) noexcept
{
  php_private::var_dump_ptrs(s.begin(),s.end(),os);
}

} //~namespace php
} //~namespace ribi

#endif // RIBI_PHP_H
