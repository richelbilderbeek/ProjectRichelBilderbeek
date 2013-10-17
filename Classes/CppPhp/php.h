#ifndef PHP_H
#define PHP_H

#include <algorithm>
#include <map>
#include <set>
#include <vector>

namespace ribi {

namespace php {

//Drop-in replacements for PHP function

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

} //~namespace php

} //~namespace ribi

#endif // PHP_H
