//---------------------------------------------------------------------------
/*
Lazy_init. Class to postpone constructor call upon first use.
Copyright (C) 2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLazy_init.htm
//---------------------------------------------------------------------------
#ifndef LAZY_INIT_H
#define LAZY_INIT_H

#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>

namespace ribi {

/*
//How to do this with variadic function templates???
template <class T, typename ... Args> struct LazyInit
{
  LazyInit(const Args ... args)
    : m_args(args)
  {

  }
  const T& Get() const
  {
    if(!m_data)
    {
      m_data.reset(new T(m_args));
    }
    return *m_data;
  }

  private:
  Args ... m_args;
  mutable boost::scoped_ptr<T> m_data;
};
*/

template <class T> struct LazyInit0
{
  LazyInit0() : m_data{} {}
  const T& Get() const
  {
    if(!m_data)
    {
      m_data.reset(new T);
    }
    return *m_data;
  }

  private:
  mutable boost::scoped_ptr<T> m_data;
};

template <class T, typename Arg0> struct LazyInit1
{
  LazyInit1(const Arg0 args)
    : m_args{args},
      m_data{}
  {

  }
  const T& Get() const
  {
    if(!m_data)
    {
      m_data.reset(new T(m_args));
    }
    return *m_data;
  }

  private:
  mutable Arg0 m_args;
  mutable boost::scoped_ptr<T> m_data;
};

template <class T, typename Arg0, typename Arg1> struct LazyInit2
{
  LazyInit2(const Arg0 arg0, const Arg1 arg1)
    : m_arg0{arg0},
      m_arg1{arg1},
      m_data{}
  {

  }
  const T& Get() const
  {
    if(!m_data)
    {
      m_data.reset(new T(m_arg0,m_arg1));
    }
    return *m_data;
  }

  private:
  mutable Arg0 m_arg0;
  mutable Arg1 m_arg1;
  mutable boost::scoped_ptr<T> m_data;
};

struct Lazy_initVersion
{
  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // LAZY_INIT_H
