#ifndef APPROXIMATOR_H
#define APPROXIMATOR_H

#include <cassert>
#include <stdexcept>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/container/flat_map.hpp>

#include "exceptionnoextrapolation.h"

#pragma GCC diagnostic pop

///Approximator can estimate a value for a key
///For example, supply Approximator<X,Y> with (1.0,10.0) and (2.0,20.0)
///and it will estimate an X if 1.5 to have a Y of 15.0
template <class Key, class Value>
struct Approximator
{
  //typedef std::map<Key,Value> Container;
  typedef boost::container::flat_map<Key,Value> Container;

  Approximator()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  void Add(const Key& key, const Value& value)
  {
    m_m.insert(std::make_pair(key,value));
  }
  const Value Approximate(const Key& key) const
  {
    typedef typename Container::const_iterator Iterator;
    {
      const Iterator i = m_m.find(key);
      if (i!=m_m.end()) return (*i).second;
    }

    const Iterator high = m_m.lower_bound(key);
    if (high == m_m.begin() || high == m_m.end())
    {
      assert(!m_m.empty());
      const Key lowest  = (*m_m.begin()).first;
      const Key highest = (*m_m.rbegin()).first;
      throw ExceptionNoExtrapolation<Key>(key,lowest,highest);
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
    const Value h_low  = (*m_m.find(d_low)).second;
    const Value h_high = (*m_m.find(d_high)).second;
    return ((1.0 - fraction)) * h_low + ((0.0 + fraction) * h_high);
  }
  const Key GetMax() const { return (*m_m.rbegin()).first; }
  const Key GetMin() const { return (*m_m.begin()).first; }

  private:
  Container m_m;

  #ifndef NDEBUG
  static void Test()
  {
    {
      static bool is_tested = false;
      if (is_tested) return;
      is_tested = true;
    }
    {
      Approximator<double,double> m;
      m.Add(1.0,10.0);
      m.Add(2.0,20.0);
      assert(m.Approximate(1.5) == 15.0);
      m.Add(4.0,40.0);
      assert(m.Approximate(3.0) == 30.0);
      m.Add(3.0,35.0);
      assert(m.Approximate(3.0) == 35.0);
      assert(m.GetMin() == 1.0);
      assert(m.GetMax() == 4.0);
    }
  }
  #endif
};

#endif // APPROXIMATOR_H
