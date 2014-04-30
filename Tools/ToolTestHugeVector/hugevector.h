#ifndef HUGEVECTOR_H
#define HUGEVECTOR_H

#include <cassert>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <cln/cln.h>

///IntToStrWithSep converts an integer to std::string
///and adds thousands seperators.
///From http://www.richelbilderbeek.nl/CppIntToStrWithSep.htm
const std::string IntToStrWithSep(cln::cl_I i);

///SafeIntToCli converts an int to cln::cl_I safely.
///From http://www.richelbilderbeek.nl/CppSafeIntToCli.htm
const cln::cl_I SafeIntToCli(const int i);

///HugeVector is a class for storing
template <class T>
struct HugeVector
{
  HugeVector(const cln::cl_I& sz)
    : m_max_index(cln::isqrt(sz)+1),
      m_cur_index(0)
  {
    std::clog << "HugeVector(" << sz << ")"
      << ": m_max_index(" << m_max_index << ")\n";
    assert(this->max_size() >= sz);
    //Only add an empty std::vector,
    //for HugeVector::push_back to work
    //(because it needs an existing m_v.back())
    m_v.push_back(std::vector<T>());

    assert(m_max_index < SafeIntToCli(m_v.max_size()));
    //std::clog << "m_v.max_size: " << m_v.max_size() << '\n';
  }
  const T& operator[](const cln::cl_I& i) const
  {
    assert(i >= 0);
    assert(i < m_max_index * m_max_index);

    //cln::cl_I_to_int will throw if cln::cl_I is bigger then the maximum
    //integer value. This method should not throw, however.
    //x = i / m_max_index
    const int x = cln::cl_I_to_int(cln::floor1(i,m_max_index));
    //y = i % m_max_index
    const int y = cln::cl_I_to_int(cln::mod(i,m_max_index));
    //std::clog << "const T& operator[" << i << "], "
    //  << "retrieves at (x,y) = (" << x << ',' << y << ")\n";
    assert(x < boost::numeric_cast<int>(m_v.size()));
    assert(y < boost::numeric_cast<int>(m_v[x].size()));
    return m_v[x][y];
  }

  T& operator[](const cln::cl_I& i)
  {
    //Calls the const version of operator[]
    //To avoid duplication in const and non-const member functions [1]
    return const_cast<T&>(const_cast<const HugeVector<T>& >(*this)[i]);
  }
  void push_back(const T& t)
  {
    //std::clog << "HugeVector::push_back\n";
    const int cur_sz = boost::numeric_cast<int>(m_v[m_cur_index].size());
    //std::clog << "Current size: " << cur_sz << '\n';
    assert(cur_sz < boost::numeric_cast<int>(m_v[m_cur_index].max_size()));
    if (cln::cl_I(cur_sz) == m_max_index)
    {
      //std::clog << "Add a std::vector\n";
      m_v.push_back(std::vector<T>());
      ++m_cur_index;
    }
    //const int index = boost::numeric_cast<int>(m_v.size()) - 1;
    assert(m_cur_index >= 0);
    //std::clog << "Push_back data at m_v["<< m_cur_index << "]\n";
    m_v[m_cur_index].push_back(t);

  }
  ///HugeVector<T>::reserve reserves at least i elements of space
  void reserve_all()
  {
    this->reserve(max_size());
  }
  void reserve(const cln::cl_I& i)
  {
    assert(i >= 0);
    std::clog << "HugeVector<T>::reserve(" << i << ")\n";
    //how many 1D std::vectors to reserve in?
    //j = 1 + (i / m_max_index)
    const int j = 1 + cln::cl_I_to_int(cln::floor1(i,m_max_index));
    std::clog << "Number of 1D std::vectors: " << j << '\n';
    //create space for those 1D std::vectors
    m_v.resize(j);
    //reserve in all those 1D std::vectors
    const int reserve_sz = cln::cl_I_to_int(m_max_index);
    //std::clog << "Reserved size in 1D std::vectors: " << reserve_sz << '\n';
    for (int i=0; i!=j; ++i)
    {
      //std::clog << "Reserving " << reserve_sz << " spaces in std::vector[" << i << "]\n";
      assert(i < boost::numeric_cast<int>(m_v.size()));
      assert(reserve_sz < boost::numeric_cast<int>(m_v[i].max_size()));
      //reserve maximum space
      m_v[i].reserve(reserve_sz);
    }
  }
  const cln::cl_I max_size() const
  {
    const cln::cl_I x = (m_max_index * m_max_index);
    const cln::cl_I y = x - cln::cl_I(1);
    std::clog << "HugeVector<T>::max_size() = " << y << '\n';
    return y;
  }

  private:
  //The maximum index a std::vector will/can be called from
  const cln::cl_I m_max_index;
  //m_cur_index is the index in m_v currently working on
  //(m_v.size() does not work, because in HugeVector::reserve
  // the 1D std::vectors must exist, to be able to reserve
  // memory for them).
  int m_cur_index;
  //The 2D std::vector containing all data
  std::vector<std::vector<T> > m_v;
};

///m_max_index = 2 ^ 27 = 134217728
///m_max_index = 2 ^ 28 = 268435456
///m_max_index must be less than std::vector<T>::max_size
///Measured was 357913941, which equals 2 ^ 28.415
///template <class T>
///const cln::cl_I HugeVector<T>::m_max_index("134217728");

///IntToStrWithSep converts an integer to std::string
///and adds thousands seperators.
///From http://www.richelbilderbeek.nl/CppIntToStrWithSep.htm
const std::string IntToStrWithSep(cln::cl_I i)
{
  std::string s
    = boost::lexical_cast<std::string>(cln::mod(i,10));
  i = cln::floor1(i,10);
  int d = 1;
  while (!cln::zerop(i))
  {
    s = boost::lexical_cast<std::string>(cln::mod(i,10))
      + (d % 3 == 0 ? "," : "")
      + s;
    i = cln::floor1(i,10);
    ++d;
  }
  return s;
}

///SafeIntToCli converts an int to cln::cl_I safely.
///From http://www.richelbilderbeek.nl/CppSafeIntToCli.htm
const cln::cl_I SafeIntToCli(const int i)
{
  //A cln::cl_I can handle integer values to 2^29 in its constructor
  if (i < 536870912)
  {
    return cln::cl_I(i);
  }
  const std::string s = boost::lexical_cast<std::string>(i);
  return cln::cl_I(s.c_str());
}

#endif // HUGEVECTOR_H
