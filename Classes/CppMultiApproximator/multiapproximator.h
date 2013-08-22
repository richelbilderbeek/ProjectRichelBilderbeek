#ifndef MULTIAPPROXIMATOR_H
#define MULTIAPPROXIMATOR_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <map>
#include <boost/container/flat_map.hpp>

#include "exceptionnoextrapolation.h"
#include "trace.h"

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
template <class Key, class Value, class Container = std::multimap<Key,Value> >
struct MultiApproximator
{
  typedef typename Container::const_iterator Iterator;
  typedef typename std::pair<Iterator,Iterator> Range;

  MultiApproximator()
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
    //Must the average be calculated?
    {
      const Range r = m_m.equal_range(key);

      if (r.first != r.second )
      {
        Value sum(0.0);
        int cnt = 0;
        for (Iterator i = r.first; i!=r.second; ++i)
        {
          sum += (*i).second;
          ++cnt;
        }
        return Value( sum / static_cast<double>(cnt));
      }
    }

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
    const Value h_low  = (*m_m.find(d_low)).second;
    const Value h_high = (*m_m.find(d_high)).second;
    return ((1.0 - fraction)) * h_low + ((0.0 + fraction) * h_high);
  }
  const Value Get(const Key& key) const
  {
    //Must the average be calculated?
    const Range r = m_m.equal_range(key);

    if (r.first != r.second )
    {
      Value sum(0.0);
      int cnt = 0;
      for (Iterator i = r.first; i!=r.second; ++i)
      {
        sum += (*i).second;
        ++cnt;
      }
      return Value( sum / static_cast<double>(cnt));
    }
    else
    {
      return r.first;
    }
    /*
    const Iterator i = m_m.find(key);
    assert(i!=m_m.end());
    return (*i).second;
    */
  }


  ///Get the heighest key value
  const Key GetMax() const { return (*m_m.rbegin()).first; }

  ///Get the lowest key value
  const Key GetMin() const { return (*m_m.begin()).first; }

  private:
  ///The container to store the std::pair<Key,Value> in
  Container m_m;

  #ifndef NDEBUG
  ///Test this class
  static void Test()
  {
    {
      static bool is_tested = false;
      if (is_tested) return;
      is_tested = true;
    }
    TRACE("Starting MultiApproximator::Test");
    {
      MultiApproximator<double,int> m;
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
};

#endif // MULTIAPPROXIMATOR_H
