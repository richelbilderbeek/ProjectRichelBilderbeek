/*
    SymbolicC++ : An object oriented computer algebra system written in C++

    Copyright (C) 2008 Yorick Hardy and Willi-Hans Steeb

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


// array.h
// The Array Class

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cassert>
#include <cstdarg>
#include <vector>


template <int d> std::vector<int> dimensions(int d1, ...)
{
   std::vector<int> dim;
   va_list ap;

   dim.push_back(d1);
   // collect the remaining sizes in dim
   va_start(ap,d1);
    for(int i=1;i<d;++i) dim.push_back(va_arg(ap,int));
   va_end(ap);
   return dim;
}

template <class T,int d>
class Array : public std::vector<Array<T,d-1> >
{
   public:
      // Constructors
      Array();
      Array(int,...);
      Array(std::vector<int>);
      Array(std::vector<int>,const T&);
      Array(const Array<T,d>&);
      ~Array();

      // Member Functions
      void resize(int,...);
      void resize(std::vector<int>);
      void resize(std::vector<int>,const T&);

      // Arithmetic Operators
      const Array<T,d> & operator = (const T&);
      Array<T,d> operator *= (const T&);
      Array<T,d> operator += (const Array<T,d>&);
      Array<T,d> operator -= (const Array<T,d>&);
      Array<T,d> operator +  (const Array<T,d>&);
      Array<T,d> operator -  (const Array<T,d>&);
};    // end declaration class Array<T,d>

// Constructor, destructor and copy constructor.

template <class T,int d> 
Array<T,d>::Array() : std::vector<Array<T,d-1> >() {}

template <class T,int d> 
Array<T,d>::Array(int r, ...) : std::vector<Array<T,d-1> >(r)
{
   std::vector<int> dim;
   va_list ap;

   dim.push_back(r);
   // collect the remaining sizes in dim
   va_start(ap,r);
    for(int i=0;i<d-1;++i) dim.push_back(va_arg(ap,int));
   va_end(ap);
   // resize the arrays with sizes in dim
   resize(dim);
}

template <class T,int d> 
Array<T,d>::Array(std::vector<int> r)
{
   if(!r.empty())
   {
    std::vector<Array<T,d-1> >::resize(r.front());
    std::vector<int> n(r.begin()+1, r.end());
    // resize the arrays with sizes in r
    for(int i=0;i<r.front();++i)
     std::vector<Array<T,d-1> >::at(i).resize(n);
   }
}

template <class T,int d> 
Array<T,d>::Array(std::vector<int> r,const T &num)
{
   if(!r.empty())
   {
    std::vector<Array<T,d-1> >::resize(r.front());
    std::vector<int> n(r.begin()+1,r.end());
    // resize the arrays with sizes in r
    for(int i=0;i<r.front();++i)
     std::vector<Array<T,d-1> >::at(i).resize(n,num);
   }
}

template <class T,int d> 
Array<T,d>::Array(const Array<T,d> &m) : std::vector<Array<T,d-1> >(m) { }

template <class T,int d> Array<T,d>::~Array() { }

// Member functions

template <class T,int d> 
void Array<T,d>::resize(int r, ...)
{
   std::vector<int> dim;
   va_list ap;
   dim.push_back(r);
   // collect the remaining sizes in dim
   va_start(ap,r);
    for(int i=0;i<d-1;++i) dim.push_back(va_arg(ap,int));
   va_end(ap);
   resize(dim);
}

template <class T,int d> 
void Array<T,d>::resize(std::vector<int> r)
{
   if(!r.empty())
   {
    std::vector<Array<T,d-1> >::resize(r.front());
    std::vector<int> n(r.begin()+1, r.end());
    // resize the arrays with sizes in r
    for(int i=0;i<r.front();++i)
     std::vector<Array<T,d-1> >::at(i).resize(n);
   }
}

template <class T,int d> 
void Array<T,d>::resize(std::vector<int> r,const T &value)
{
   if(!r.empty())
   {
    std::vector<Array<T,d-1> >::resize(r.front());
    std::vector<int> n(r.begin()+1, r.end());
    // resize the arrays with sizes in r
    for(int i=0;i<r.front();++i)
     std::vector<Array<T,d-1> >::at(i).resize(n,value);
   }
}

// Various member operators

template <class T,int d> 
const Array<T,d> & Array<T,d>::operator = (const T &num)
{
   int length = std::vector<Array<T,d-1> >::size();
   for(int i=0;i<length;i++) std::vector<Array<T,d-1> >::at(i) = num;
   return *this;
}

template <class T,int d> 
Array<T,d> Array<T,d>::operator *= (const T &num)
{
   int length = std::vector<Array<T,d-1> >::size();
   for(int i=0;i<length;i++) std::vector<Array<T,d-1> >::at(i) *= num;
   return *this;
}

template <class T,int d> 
Array<T,d> Array<T,d>::operator += (const Array<T,d> &m)
{ return *this = *this + m; }

template <class T,int d> 
Array<T,d> Array<T,d>::operator -= (const Array<T,d> &m)
{ return *this = *this - m; }

template <class T,int d> 
Array<T,d> Array<T,d>::operator + (const Array<T,d> &m)
{
   int length = std::vector<Array<T,d-1> >::size();
   assert(m.size() == (std::vector<Array<T,d-1> >::size()));
   Array<T,d> temp(*this);
   for(int i=0;i<length;i++)
    temp[i] = std::vector<Array<T,d-1> >::at(i)+m[i];
   return temp;
}

template <class T,int d> 
Array<T,d> Array<T,d>::operator - (const Array<T,d> &m)
{
   int length = std::vector<Array<T,d-1> >::size();
   assert(m.size() == (std::vector<Array<T,d-1> >::size()));
   Array<T,d> temp(*this);
   for(int i=0;i<length;i++)
    temp[i] = std::vector<Array<T,d-1> >::at(i)-m[i];
   return temp;
}

template <class T,int d> 
ostream & operator << (std::ostream &s,const Array<T,d> &m)
{
   for(int i=0;i<int(m.size());i++) s << m[i] << std::endl;
   return s;
}

//Override the template definition for the 1-dimensional case

template <class T>
class Array<T,1> : public std::vector<T>
{
   public:
      // Constructors
      Array(int = 0);
      Array(std::vector<int>);
      Array(int,const T&);
      Array(std::vector<int>,const T&);
      Array(const Array<T,1>&);
      ~Array();

      // Member Functions
      void resize(int);
      void resize(std::vector<int>);
      void resize(int,const T&);
      void resize(std::vector<int>,const T&);

      // Arithmetic Operators
      const Array<T,1> & operator = (const T&);
      Array<T,1> operator *= (const T&);
      Array<T,1> operator += (const Array<T,1>&);
      Array<T,1> operator -= (const Array<T,1>&);
      Array<T,1> operator +  (const Array<T,1>&);
      Array<T,1> operator -  (const Array<T,1>&);
};    // end declaration class Array<T,1>

// Constructors, destructors and copy constructor.

template <class T> 
Array<T,1>::Array(int n) : std::vector<T>(n) { }

template <class T> 
Array<T,1>::Array(std::vector<int> n)
{ if(!n.empty()) std::vector<T>::resize(n.front()); }

template <class T> 
Array<T,1>::Array(int n,const T &num) : std::vector<T>(n,num) { }

template <class T> 
Array<T,1>::Array(std::vector<int> n,const T &num)
{ if(!n.empty()) std::vector<T>::resize(n.front(),num); }

template <class T> 
Array<T,1>::Array(const Array<T,1> &v) : std::vector<T>(v) { }

template <class T> Array<T,1>::~Array() { }

// Member functions

template <class T> void Array<T,1>::resize(int n)
{ std::vector<T>::resize(n); }

template <class T> void Array<T,1>::resize(std::vector<int> n)
{ if(!n.empty()) std::vector<T>::resize(n.front()); }

template <class T> 
void Array<T,1>::resize(int n,const T &value)
{ std::vector<T>::resize(n,value); }

template <class T> 
void Array<T,1>::resize(std::vector<int> n,const T &value)
{ if(!n.empty()) std::vector<T>::resize(n.front(),value); }

// Various member operators

template <class T> 
const Array<T,1> & Array<T,1>::operator = (const T &num)
{
   int length = std::vector<T>::size();
   for(int i=0;i<length;i++) std::vector<T>::at(i) = num;
   return *this;
}

template <class T> 
Array<T,1> Array<T,1>::operator *= (const T &num)
{
   int length = std::vector<T>::size();
   for(int i=0;i<length;i++) std::vector<T>::at(i) *= num;
   return *this;
}

template <class T> 
Array<T,1> Array<T,1>::operator += (const Array<T,1> &v)
{ return *this = *this + v; }

template <class T> 
Array<T,1> Array<T,1>::operator -= (const Array<T,1> &v)
{ return *this = *this - v; }

template <class T> 
Array<T,1> Array<T,1>::operator + (const Array<T,1> &v)
{
   int length = std::vector<T>::size();
   assert(std::vector<T>::size() == v.size());
   Array<T,1> temp(length);
   for(int i=0;i<length;i++) temp[i] = std::vector<T>::at(i)+v[i];
   return temp;
}

template <class T> 
Array<T,1> Array<T,1>::operator - (const Array<T,1> &v)
{
   int length = std::vector<T>::size();
   assert(std::vector<T>::size() == v.size());
   Array<T,1> temp(length);
   for(int i=0;i<length;i++) temp[i] = std::vector<T>::at(i)-v[i];
   return temp;
}

template <class T> 
ostream & operator << (std::ostream &s,const Array<T,1> &v)
{
   s << "[";
   for(int i=0;i<int(v.size())-1;i++) s << v[i] << " ";
   s << v.back() << "]";
   return s;
}

#endif
