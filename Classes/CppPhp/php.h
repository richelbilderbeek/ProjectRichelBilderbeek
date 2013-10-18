#ifndef PHP_H
#define PHP_H

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <typeinfo>


namespace ribi {

namespace php {

//Drop-in replacements for PHP function

//You are free to use functions from this namespace,
//but I did not intend you using these :)
namespace php_private {

///Convert a type to the PHP description
template <class T> const std::string TypeToStr();
template <> const std::string TypeToStr<int>();

template <class Iter>
void var_dump(Iter begin, const Iter end)
{
  const std::size_t sz = std::distance(begin,end);
  std::cout << "array(" << sz << ") {\n";
  std::size_t i=0;
  for (; begin!=end; ++begin)
  {
    std::cout
      << "  [" << i << "]=>\n"
      << "  " << TypeToStr<typename Iter::value_type>() << "(" << (*begin) << ")\n";
    ++i;
  }
  std::cout << "}\n";
}

} //~php_private


template <class T>
const std::vector<T> array_intersect(
  const std::vector<T>& v,
  const std::vector<T>& w)
{
  assert(std::is_sorted(v.begin(),v.end()));
  assert(std::is_sorted(w.begin(),w.end()));
  std::vector<T> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),std::back_inserter(x));
  return x;
}

template <class T>
const std::set<T> array_intersect(
  const std::set<T>& v,
  const std::set<T>& w)
{
  std::set<T> x;
  std::set_intersection(v.begin(),v.end(),w.begin(),w.end(),std::inserter(x,x.begin()));
  return x;
}

template <class T, class U>
const std::vector<T> array_keys(const std::map<T,U>& m)
{
  std::vector<T> v;
  for (const std::pair<T,U>& p: m) v.push_back(p.first);
  return v;
}

template <class T>
const std::vector<int> array_keys(const std::vector<T>& m)
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
const std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w)
{
  std::vector<T> x { v };
  std::copy(w.begin(),w.end(),std::back_inserter(x));
  return x;
}

template <class T>
const std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w,
  const std::vector<T>& x)
{
  std::vector<T> result { v };
  const std::vector<T> temp { array_merge(w,x) };
  std::copy(temp.begin(),temp.end(),std::back_inserter(result));
  return result;
}

template <class T>
const std::vector<T> array_merge(
  const std::vector<T>& v,
  const std::vector<T>& w,
  const std::vector<T>& x,
  const std::vector<T>& y)
{
  std::vector<T> result { v };
  const std::vector<T> temp { array_merge(w,x,y) };
  std::copy(temp.begin(),temp.end(),std::back_inserter(result));
  return result;
}

template <class KeyType, class ValueType>
const std::vector<ValueType> array_values(
  const std::map<KeyType,ValueType>& m)
{
  std::vector<ValueType> v;
  for (auto p: m)
  {
    v.push_back(p.second);
  }
  return v;
}

template <class KeyType, class ValueType>
const std::map<KeyType,ValueType> array_values(
  const std::map<KeyType,ValueType>& m)
{
  std::map<KeyType,ValueType> v;
  KeyType key = 0;
  for (auto p: m)
  {
    v[key] = p.second;
    ++key;
  }
  return v;
}

const std::string implode(
  const std::string& seperator,
  const std::vector<std::string>& v);

const std::string implode(
  const std::string& seperator,
  const std::vector<int>& v);

const std::string implode(
  const std::string& seperator,
  const std::array<double,3>& v);

template <class T>
void var_dump(const std::set<T>& s)
{
  php_private::var_dump(s.begin(),s.end());
}

} //~namespace php

} //~namespace ribi

#endif // PHP_H
