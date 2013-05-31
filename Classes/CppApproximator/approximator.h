#ifndef APPROXIMATOR_H
#define APPROXIMATOR_H

#include <cassert>
#include <stdexcept>
#include <map>

template <class Key, class Value>
struct Approximator
{
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
    typedef typename std::map<Key,Value>::const_iterator Iterator;
    {
      const Iterator i = m_m.find(key);
      if (i!=m_m.end()) return (*i).second;
    }

    const Iterator low = --m_m.lower_bound(key);
    const Iterator high = m_m.lower_bound(key);

    if (high == m_m.begin() || high == m_m.end())
    {
      //const Value lowest  = (*m_m.begin()).first;
      //const Value highest = (*m_m.rbegin()).first;
      throw std::runtime_error("No extrapolation allowed with Approximator class");
    }
    assert(low != m_m.end());
    assert(high != m_m.end());
    const Value d_low = (*low).first;
    const Value d_high = (*high).first;
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
  static void Test()
  {
    {
      static bool is_tested = false;
      if (is_tested) return;
      is_tested = true;
    }
    {
      Approximator<double,double> m;
      m.Add(1.0,1.0);
      m.Add(2.0,2.0);
      assert(m.Approximate(1.5) == 1.5);
      m.Add(4.0,4.0);
      assert(m.Approximate(3.0) == 3.0);
      m.Add(3.0,3.5);
      assert(m.Approximate(3.0) == 3.5);
      assert(m.GetMin() == 1.0);
      assert(m.GetMax() == 4.0);
    }
  }

  std::map<Key,Value> m_m;
};

#endif // APPROXIMATOR_H
