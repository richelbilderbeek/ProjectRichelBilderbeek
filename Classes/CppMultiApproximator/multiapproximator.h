#ifndef MULTIAPPROXIMATOR_H
#define MULTIAPPROXIMATOR_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/container/flat_map.hpp>

#include "exceptionnoextrapolation.h"
#include "trace.h"
#pragma GCC diagnostic pop

///MultiApproximator can estimate a value between (non-unique) keys.
///For example, supply Approximator<X,Y> with (1.0,10) and (2.0,20)
///and it will estimate an X if 1.5 to have a Y of 15.
///If the data used has unique keys only, use Approximator
///for an increase in run-time speed.
///If all keys are added to MultiApproximator, it is possible to spawn
///an Approximator from it.
///
///Key: a type that has operator<
///Value: a type that has operator/(double)
///Container: how to store the std::pair<Key,Value>
///  - boost::container::flat_multimap<Key,Value>
///    : faster for lookup, data adding is slower
///  - std::multimap<Key,Value>
///    : faster adding of data, lookup is slower
template <class Key = double, class Value = double, class Container = std::multimap<Key,Value> >
struct MultiApproximator
{
  typedef Key key_type;
  typedef Value value_type;
  typedef typename Container::const_iterator Iterator;
  typedef typename std::pair<Iterator,Iterator> Range;

  MultiApproximator();

  void Add(const Key& key, const Value& value);

  const Value Approximate(const Key& key) const;

  ///Obtain the container
  const Container& GetContainer() const { return m_m; }

  ///Get the heighest key value
  const Key GetMax() const { return (*m_m.rbegin()).first; }

  ///Get the lowest key value
  const Key GetMin() const { return (*m_m.begin()).first; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  ///The container to store the std::pair<Key,Value> in
  Container m_m;

  ///Obtain the true or averaged value at the key when the key is present
  const Value GetValue(const Key& key) const;

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

template <class Key, class Value, class Container>
MultiApproximator<Key,Value,Container>::MultiApproximator()
{
  static_assert(!std::is_integral<Key>(),
    "MultiApproximator will not work on integer keys");
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Key, class Value, class Container>
void MultiApproximator<Key,Value,Container>::Add(const Key& key, const Value& value)
{
  m_m.insert(std::make_pair(key,value));
}

template <class Key, class Value, class Container>
const Value MultiApproximator<Key,Value,Container>::Approximate(const Key& key) const
{
  //Must the average be calculated?
  if (m_m.find(key) != m_m.end()) return GetValue(key);

  const Iterator high = m_m.lower_bound(key);

  if (high == m_m.begin() || high == m_m.end())
  {
    assert(!m_m.empty());
    const Key lowest  = (*m_m.begin()).first;
    const Key highest = (*m_m.rbegin()).first;
    throw ExceptionNoExtrapolation<Key>(key, lowest, highest);
  }
  const Iterator low = --Iterator(high);
  assert(low != m_m.end());
  assert(high != m_m.end());
  const Key d_low = (*low).first;
  const Key d_high = (*high).first;
  assert(d_low < key);
  assert(d_high > key);
  const double fraction
    = (key - d_low)
    / (d_high - d_low);
  assert(fraction >= 0.0);
  assert(fraction <= 1.0);
  assert(m_m.find(d_low)  != m_m.end());
  assert(m_m.find(d_high) != m_m.end());
  const Value h_low  = GetValue(d_low);
  const Value h_high = GetValue(d_high);
  return ((1.0 - fraction)) * h_low + ((0.0 + fraction) * h_high);
}

template <class Key, class Value, class Container>
const Value MultiApproximator<Key,Value,Container>::GetValue(const Key& key) const
{
  assert(m_m.find(key) != m_m.end());

  //Must the average be calculated?
  const Range r = m_m.equal_range(key);
  assert(r.first != m_m.end());

  if (r.first != r.second )
  {
    //const Value result = std::accumulate(r.first,r.second,Value(0.0), [] )
    //  / static_cast<double>( std::distance(r.first,r.second) );

    Value sum(0.0);
    int cnt = 0;
    for (Iterator i = r.first; i!=r.second; ++i)
    {
      sum += (*i).second;
      ++cnt;
    }
    const Value result( sum / static_cast<double>(cnt));
    return result;
  }
  else
  {
    const Value result((*r.first).second);
    return result;
  }
}

template <class Key, class Value, class Container>
const std::string MultiApproximator<Key,Value,Container>::GetVersion()
{
  return "1.0";
}

///Obtain the version history of this class
template <class Key, class Value, class Container>
const std::vector<std::string> MultiApproximator<Key,Value,Container>::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-08-23: version 1.0: initial version");
  return v;
}

#ifndef NDEBUG
template <class Key, class Value, class Container>
void MultiApproximator<Key,Value,Container>::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting MultiApproximator::Test");
  //Test approximation
  {
    MultiApproximator<double,double,std::multimap<double,double> > m;
    m.Add(1.0,10);
    m.Add(2.0,20);
    assert(m.Approximate(1.5) == 15);
    m.Add(4.0,40);
    m.Add(4.0,40);
    assert(m.Approximate(3.0) == 30);
    m.Add(3.0,35);
    assert(m.Approximate(3.0) == 35);
    m.Add(3.0,45);
    assert(m.Approximate(3.0) == 40);
    assert(m.GetMin() == 1.0);
    assert(m.GetMax() == 4.0);
  }
  TRACE("Completed MultiApproximator::Test successfully");
}
#endif


#endif // MULTIAPPROXIMATOR_H
