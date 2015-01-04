//---------------------------------------------------------------------------
/*
The Rampal Etienne Project, calculates the probability of a phylogeny
(C) 2009-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef NEWICKSTORAGE_H
#define NEWICKSTORAGE_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <numeric>
#include <stdexcept>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "trace.h"

namespace ribi {

template <class NewickType>
struct NewickStorage
{
  typedef NewickType value_type;
  NewickStorage(const NewickType& n);
  double Find(const NewickType& n) const;
  void Store(const NewickType& n, const double p);
  const std::vector<std::map<NewickType,double> >& Peek() const { return m; }
  int CountNewicks() const;
  void CleanUp();
  int GetMemoryUse() const;

  private:
  std::vector<std::map<NewickType,double> > m;
};

template <class T, class U>
const std::vector<int> GetSizes(
  const std::vector<std::map<T,U> >& m)
{
  typedef typename std::vector<std::map<T,U> >::const_iterator Iter;

  std::vector<int> v;
  v.reserve(m.size());

  for (Iter i = m.begin(); i!=m.end(); ++i)
  {
    v.push_back( (*i).size() );
  }
  return v;
}

template <class T>
NewickStorage<T>::NewickStorage(const T& n)
  : m(n.Size()+1)
{

}

template <class T>
double NewickStorage<T>::Find(const T& n) const
{
  typedef typename std::map<T,double>::const_iterator Iter;
  const int n_sz = n.Size();
  //Disallow resizing
  assert(n_sz < static_cast<int>(m.size()));
  const Iter i = m[n_sz].find(n);
  if (i!=m[n_sz].end())
  {
    //n is already known, return probability
    assert((*i).second>0.0);
    return (*i).second;
  }
  return 0.0;
}

template <class T>
void NewickStorage<T>::Store(const T& n, const double p)
{
  //TRACE("Stored probability for "
  //  + n.ToStr()
  //  + " = "
  //  + boost::lexical_cast<std::string>(p));

  const int n_sz = n.Size();
  //Disallow resizing
  assert(n_sz < static_cast<int>(m.size()));

  assert(Find(n)==0.0 || Find(n)==p);

  while (1)
  {
    try
    {
      m[n_sz][n]=p;
      return;
    }
    catch (std::bad_alloc& e)
    {
      //TRACE("std::bad_alloc in NewickStorage<T>::Store");
      CleanUp();
    }
    catch (std::exception& e)
    {
      //TRACE("std::exception in NewickStorage<T>::Store");
      //TRACE(e.what());
      CleanUp();
    }
    catch (...)
    {
      //TRACE_FILE("Unknown exception in NewickStorage<T>::Store");
      CleanUp();
    }
  }
}

template <class T>
int NewickStorage<T>::CountNewicks() const
{
  int sum = 0;
  const int sz = m.size();
  for (int i=0; i!=sz; ++i)
  {
    sum+=m[i].size();
  }
  return sum;
}

template <class T>
void NewickStorage<T>::CleanUp()
{
  //Clear the simplest std::maps,
  //  save the std::maps with most complex ones
  //  (is this really wise?)
  //  (but what is the alternative?)
  //TRACE_FILE("Investigating std::map sizes - VERSION 2009-07-31-17:21");
  const int m_sz = m.size();
  std::vector<int> v(m_sz);
  for (int i=0; i!=m_sz; ++i)
  {
    v[i] = m[i].size();
    //TRACE_FILE(v[i]);
  }
  for (int i=0; i!=m_sz; ++i)
  {
    const int this_sz = m[i].size();
    const int sum_sz = CountNewicks();
    if (this_sz == sum_sz)
    {
      //All cleared except last
      break;
    }
    #ifndef NTRACE
    {
      const std::string trace = "Cleared index "
        + boost::lexical_cast<std::string>(i)
        + " with "
        + boost::lexical_cast<std::string>(m[i].size())
        + " entries.";
      //TRACE_FILE(trace);
    }
    #endif
    m[i] = std::map<T,double>(); //Clear
  }
}



//The memory used equals the sum of the memory used for each Newick size

//For each size the memory use equals
// the number of Newicks of that size
// * the size of those Newicks
// * the size of an integer
template <class T>
/* const */ int NewickStorage<T>::GetMemoryUse() const
{
  std::vector<int> v = GetSizes(m);
  const int sz = v.size();
  for (int i=0; i!=sz; ++i)
  {
    v[i]*=i; //The size of those Newikcs
    v[i]*=sizeof(int);
  }
  const int sum_of_newick_ints = std::accumulate(v.begin(),v.end(),0);
  const int sum
    = sum_of_newick_ints
    + (sz * sizeof(std::vector<int>))
    + sizeof(m);
  return sum;
}

} //~namespace ribi

#endif //NEWICKSTORAGE_H

