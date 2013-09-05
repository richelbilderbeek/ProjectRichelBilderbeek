#ifndef APPROXIMATOR_H
#define APPROXIMATOR_H

#include <cassert>
#include <stdexcept>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/container/flat_map.hpp>

#include "exceptionnoextrapolation.h"
#include "trace.h"
#pragma GCC diagnostic pop

namespace ribi {

///Approximator can estimate a value between unique keys.
///For example, supply Approximator<X,Y> with (1.0,10.0) and (2.0,20.0)
///and it will estimate an X if 1.5 to have a Y of 15.0.
///If the data used has duplicate keys, e.g. (1.0,9.0) and (1.0,11.0), use
///MultiApproximator instead.
///
///Key: a type that has operator<
///Value: a type that has operator/(double)
///Container: how to store the std::pair<Key,Value>
///  - boost::container::flat_imap<Key,Value>
///    : faster for lookup, data adding is slower
///  - std::map<Key,Value>
///    : faster adding of data, lookup is slower
template <class Key = double, class Value = double, class Container = boost::container::flat_map<Key,Value> >
struct Approximator
{
  typedef Key key_type;
  typedef Value value_type;

  explicit Approximator(const Container& m = Container() );

  ///Add a key-value pair, where the key must be unique
  void Add(const Key& key, const Value& value);

  ///Approximate a key its value
  const Value Approximate(const Key& key) const;

  ///Can only add a value if its key is not present
  bool CanAdd(const Key& key, const Value& ) const;

  ///Obtain the container
  const Container& Get() const { return m_m; }

  ///Obtain the lowest key value
  const Key GetMax() const { assert(!m_m.empty()); return (*m_m.rbegin()).first; }

  ///Obtain the heighest key value
  const Key GetMin() const { assert(!m_m.empty()); return (*m_m.begin()).first; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  ///The container used
  Container m_m;

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif

};


template <class Key, class Value, class Container>
Approximator<Key,Value,Container>::Approximator(const Container& m)
  : m_m { m }
{
  static_assert(!std::is_integral<Key>(),
    "Approximator will not work on integer keys");
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Key, class Value, class Container>
void Approximator<Key,Value,Container>::Add(const Key& key, const Value& value)
{
  assert( CanAdd(key,value)
    && "Every key must be unique,"
       "use MultiApproximator if you need non-unique keys");
  m_m.insert(std::make_pair(key,value));
  assert( !CanAdd(key,value) );
}

template <class Key, class Value, class Container>
const Value Approximator<Key,Value,Container>::Approximate(const Key& key) const
{
  typedef typename Container::const_iterator Iterator;

  assert(!m_m.empty() && "Cannot approximate without data");

  {
    const Iterator i { m_m.find(key) };
    if (i!=m_m.end()) return (*i).second;
  }

  const Iterator high { m_m.lower_bound(key) };
  if (high == m_m.begin() || high == m_m.end())
  {
    assert(!m_m.empty());
    const Key lowest  { (*m_m.begin()).first  };
    const Key highest { (*m_m.rbegin()).first };
    throw ExceptionNoExtrapolation<Key>(key,lowest,highest);
  }
  const Iterator low { --Iterator(high) };
  assert(low != m_m.end());
  assert(high != m_m.end());
  const Key d_low  { (*low).first };
  const Key d_high { (*high).first };
  assert(d_low < key);
  assert(d_high > key);
  const double fraction { (key - d_low) / (d_high - d_low) };
  assert(fraction >= 0.0);
  assert(fraction <= 1.0);
  assert(m_m.find(d_low)  != m_m.end());
  assert(m_m.find(d_high) != m_m.end());
  const Value h_low  { (*m_m.find(d_low)).second  };
  const Value h_high { (*m_m.find(d_high)).second };
  return ((1.0 - fraction)) * h_low + ((0.0 + fraction) * h_high);
}

template <class Key, class Value, class Container>
bool Approximator<Key,Value,Container>::CanAdd(const Key& key, const Value& ) const
{
  return m_m.find(key) == m_m.end();
}

template <class Key, class Value, class Container>
const std::string Approximator<Key,Value,Container>::GetVersion()
{
  return "1.0";
}

///Obtain the version history of this class
template <class Key, class Value, class Container>
const std::vector<std::string> Approximator<Key,Value,Container>::GetVersionHistory()
{
  const std::vector<std::string> v {
    "2013-08-22: version 1.0: initial version"
  };
  return v;
}


#ifndef NDEBUG
template <class Key, class Value, class Container>
void Approximator<Key,Value,Container>::Test()
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  {
    TRACE("Starting Approximator::Test");
    Approximator<double,int> m;
    m.Add(1.0,10);
    m.Add(2.0,20);
    assert(m.Approximate(1.5) == 15);
    m.Add(4.0,40);
    assert(m.Approximate(3.0) == 30);
    m.Add(3.0,35);
    assert(m.Approximate(3.0) == 35);
    assert(m.GetMin() == 1.0);
    assert(m.GetMax() == 4.0);
    TRACE("Completed Approximator::Test successfully");
  }
}
#endif

} //~namespace ribi

#endif // APPROXIMATOR_H
