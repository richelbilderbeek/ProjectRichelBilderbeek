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

#pragma GCC diagnostic pop

#include "approximator.h"
#include "exceptionnoextrapolation.h"
#include "testtimer.h"
#include "trace.h"

namespace ribi {

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

  explicit MultiApproximator(const Container& container = Container()) noexcept;

  ///Add a (key,value) pair. Because keys do not need to be unique,
  ///this will always succeed
  void Add(const Key& key, const Value& value) noexcept;

  ///Approximates a value from a key
  ///Will throw a std::logic_error if there is no data in the MultiApproximator
  ///Will throw ExceptionNoExtrapolation if the key is beyond the range
  ///of the keys stored in MultiApproxitor
  Value Approximate(const Key& key) const;

  ///Obtain the container
  const Container& GetContainer() const noexcept{ return m_m; }

  ///Get the heighest key value
  Key GetMax() const;

  ///Get the lowest key value
  Key GetMin() const;

  ///Obtain the true or averaged value at the key when the key is present
  Value GetValue(const Key& key) const;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///The container to store the std::pair<Key,Value> in
  Container m_m;

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  //template <class AnyKey, class AnyValue, class AnyContainer>
  //friend void MultiApproximator<AnyKey,AnyValue,AnyContainer>::Test();
  //friend void MultiApproximator<Key,Value,Container>::Test();


};


///Convert a std::multimap to a std::map
template <class Key, class Value>
const std::map<Key,Value> MultimapToMap(
  const std::multimap<Key,Value> m) noexcept;

///Convert to a (non-multi)Approximator
///This probably gain runtime speed, when will no data added anymore
template <
  class Key,
  class Value,
  class MultiContainer,
  class Container
  >
Approximator<Key,Value,Container> ToApproximator(
  const MultiApproximator<Key,Value,MultiContainer>& m) noexcept;


template <class Key, class Value, class Container>
MultiApproximator<Key,Value,Container>::MultiApproximator(const Container& container) noexcept
  : m_m { container }
{
  static_assert(!std::is_integral<Key>(),
    "MultiApproximator will not work on integer keys");
  static_assert(!std::is_integral<Value>(),
    "MultiApproximator will not work on integer values");
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Key, class Value, class Container>
void MultiApproximator<Key,Value,Container>::Add(const Key& key, const Value& value) noexcept
{
  m_m.insert(std::make_pair(key,value));
}

template <class Key, class Value, class Container>
Value MultiApproximator<Key,Value,Container>::Approximate(const Key& key) const
{
  if (m_m.empty())
  {
    throw std::logic_error(
      "MultiApproximator<Key,Value,Container>::Approximate: "
      "cannot approximate without data");
  }
  //Must the average be calculated?
  if (m_m.find(key) != m_m.end()) return GetValue(key);

  const Iterator high { m_m.lower_bound(key) };

  if (high == m_m.begin() || high == m_m.end())
  {
    assert(!m_m.empty());
    const Key lowest  { (*m_m.begin()).first  };
    const Key highest { (*m_m.rbegin()).first };
    throw ExceptionNoExtrapolation<Key>(key, lowest, highest);
  }
  const Iterator low { --Iterator(high) };
  assert(low != m_m.end());
  assert(high != m_m.end());
  const Key d_low  { (*low).first  };
  const Key d_high { (*high).first };
  assert(d_low < key);
  assert(d_high > key);
  const double fraction { (key - d_low) / (d_high - d_low) };
  assert(fraction >= 0.0);
  assert(fraction <= 1.0);
  assert(m_m.find(d_low)  != m_m.end());
  assert(m_m.find(d_high) != m_m.end());
  const Value h_low  { GetValue(d_low)  };
  const Value h_high { GetValue(d_high) };
  return ((1.0 - fraction)) * h_low + ((0.0 + fraction) * h_high);
}

template <class Key, class Value, class Container>
Key MultiApproximator<Key,Value,Container>::GetMax() const
{
  assert(!m_m.empty());
  return (*m_m.rbegin()).first;
}

template <class Key, class Value, class Container>
Key MultiApproximator<Key,Value,Container>::GetMin() const
{
  assert(!m_m.empty());
  return (*m_m.begin()).first;
}

template <class Key, class Value, class Container>
Value MultiApproximator<Key,Value,Container>::GetValue(const Key& key) const
{
  assert(m_m.find(key) != m_m.end());

  //Must the average be calculated?
  const Range r { m_m.equal_range(key) };
  assert(r.first != m_m.end());

  if (r.first != r.second )
  {
    //const Value result = std::accumulate(r.first,r.second,Value(0.0), [] )
    //  / static_cast<double>( std::distance(r.first,r.second) );

    Value sum { 0.0 };
    int cnt { 0 };
    for (Iterator i { r.first }; i!=r.second; ++i)
    {
      sum += (*i).second;
      ++cnt;
    }
    const Value result { sum / static_cast<double>(cnt) };
    return result;
  }
  else
  {
    const Value result { (*r.first).second };
    return result;
  }
}

template <class Key, class Value, class Container>
std::string MultiApproximator<Key,Value,Container>::GetVersion() noexcept
{
  return "1.1";
}

///Obtain the version history of this class
template <class Key, class Value, class Container>
std::vector<std::string> MultiApproximator<Key,Value,Container>::GetVersionHistory() noexcept
{
  return {
    "2013-08-23: version 1.0: initial version",
    "2013-08-23: version 1.1: add conversion to an Approximator"
  };
}

template <class Key, class Value>
const std::map<Key,Value> MultimapToMap(
  const std::multimap<Key,Value> m) noexcept
{
  std::map<Key,Value> n;
  if (m.empty()) return n;
  const auto end = m.end();
  for (auto begin = m.begin(); begin != end; )
  {
    assert(begin != m.end());
    const auto key = (*begin).first;
    assert(m.find(key) != m.end());

    //Must the average be calculated?
    const auto r = m.equal_range(key);
    assert(r.first != m.end());

    if (r.first != r.second )
    {
      Value sum(0.0);
      int cnt = 0;
      for (auto i = r.first; i!=r.second; ++i)
      {
        sum += (*i).second;
        ++cnt;
      }
      const Value result( sum / static_cast<double>(cnt));
      n[ key ] = result;
    }
    else
    {
      const Value result((*r.first).second);
      n[ key ] = result;
    }
    begin = r.second;
  }
  return n;
}

#ifndef NDEBUG
template <class Key, class Value, class Container>
void MultiApproximator<Key,Value,Container>::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //GetMin and GetMax
  {
    MultiApproximator<double,double,std::multimap<double,double> > m;
    m.Add(1.0,0.0);
    assert(m.GetMin() == 1.0);
    assert(m.GetMax() == 1.0);
    m.Add(2.0,0.0);
    assert(m.GetMin() == 1.0);
    assert(m.GetMax() == 2.0);
    m.Add(0.0,0.0);
    assert(m.GetMin() == 0.0);
    assert(m.GetMax() == 2.0);
    m.Add(0.5,0.0);
    assert(m.GetMin() == 0.0);
    assert(m.GetMax() == 2.0);
  }
  //GetValue
  {
    MultiApproximator<double,double,std::multimap<double,double> > m;
    const double key = 1.0;
    const double value1 = 1.0;
    m.Add(key,value1);
    assert(m.GetValue(key) == value1);
    const double value2 = 2.0;
    m.Add(key,value2);
    assert(m.GetValue(key) == (value1 + value2) / 2.0);
    const double value3 = 4.0;
    m.Add(key,value3);
    assert(m.GetValue(key) == (value1 + value2 + value3) / 3.0);
  }
  //MultimapToMap
  {
    {
      const std::multimap<int,double> m ( { { 1, 1.0} } );
      const std::map<int,double> n(MultimapToMap(m));
      assert(n.size() == 1);
    }
    {
      const std::multimap<int,double> m ( { { 1, 1.0}, { 1, 1.0} } );
      const std::map<int,double> n(MultimapToMap(m));
      const std::map<int,double> e( { { 1, 1.0 } } );
      assert(n.size() == 1);
      assert(n == e);
    }
    {
      const std::multimap<int,double> m ( { { 1, 1.0}, { 1, 2.0} } );
      const std::map<int,double> n(MultimapToMap(m));
      const std::map<int,double> e( { { 1, 1.5 } } );
      assert(n.size() == 1);
      assert(n == e);
    }
    {
      const std::multimap<int,double> m ( { {0, 0.0}, { 1, 1.0}, { 1, 1.0}, {2, 2.0} } );
      const std::map<int,double> n(MultimapToMap(m));
      const std::map<int,double> e( { {0, 0.0}, { 1, 1.0 }, {2, 2.0} } );
      assert(n.size() == 3);
      assert(n == e);
    }
    {
      const std::multimap<int,double> m ( { {0, 0.0}, { 1, 1.0}, { 1, 2.0}, {2, 2.0} } );
      const std::map<int,double> n(MultimapToMap(m));
      const std::map<int,double> e( { {0, 0.0}, { 1, 1.5 }, {2, 2.0} } );
      assert(n.size() == 3);
      assert(n == e);
    }
  }
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
  }
  TRACE("Completed MultiApproximator::Test successfully");
}
#endif

template <
  class Key,
  class Value,
  class MultiContainer,
  class Container
  >
Approximator<Key,Value,Container> ToApproximator(
  const MultiApproximator<Key,Value,MultiContainer>& multi_approximator) noexcept
{
  const MultiContainer m = multi_approximator.GetContainer();
  const Container n = MultimapToMap(m);
  Approximator<Key,Value,Container> a(n);
  return a;
}

} //~namespace ribi

#endif // MULTIAPPROXIMATOR_H
