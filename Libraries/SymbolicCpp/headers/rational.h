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


// rational.h
// Rational Numbers Class
#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector>
#include <ctype.h>
#include "identity.h"


template <class T>
class Rational
{
   public:
      enum output_type { decimal, fraction };

   private:
      // Data Fields : Numerator and Denominator
      T p,q;

      // Private member function
      T gcd(T,T);

      // output type : decimal or fraction
      static output_type output_preference;

   public:
      // Constructors and Destructor
      Rational();
      Rational(T);
      Rational(T,T);
      Rational(const Rational<T>&);
      Rational(const std::string&);
      Rational(const double&);
      ~Rational();

      // Conversion operator
      operator double () const;

      // Member functions
      T num() const;            // numerator of r
      T den() const;            // denominator of r
      Rational<T> frac() const; // fractional part of r
      void normalize();         // normalize the rational number

      // Arithmetic operators and Relational operators
      const Rational<T> &operator = (const Rational<T>&);
      Rational<T> operator - () const;
      const Rational<T> &operator += (const Rational<T>&);
      const Rational<T> &operator -= (const Rational<T>&);
      const Rational<T> &operator *= (const Rational<T>&);
      const Rational<T> &operator /= (const Rational<T>&);

      Rational<T> operator + (const Rational<T>&) const;
      Rational<T> operator - (const Rational<T>&) const;
      Rational<T> operator * (const Rational<T>&) const;
      Rational<T> operator / (const Rational<T>&) const;

      Rational<T>& operator ++ ();
      Rational<T>  operator ++ (int);
      Rational<T>& operator -- ();
      Rational<T>  operator -- (int);

      int operator == (const Rational<T>&) const;
      int operator != (const Rational<T>&) const;
      int operator >  (const Rational<T>&) const;
      int operator <  (const Rational<T>&) const;
      int operator >= (const Rational<T>&) const;
      int operator <= (const Rational<T>&) const;

      // I/O stream functions
      std::ostream &output(std::ostream&) const;
      std::istream &input(std::istream&);

      static void output_style(output_type);
};

template <class T>
typename Rational<T>::output_type
Rational<T>::output_preference = Rational<T>::fraction;

// Constructors, destructor and conversion operator.

template <class T> Rational<T>::Rational () : p(zero(T())),q(one(T())) {}

template <class T> Rational<T>::Rational (T N) : p(N),q(one(T())) {}

template <class T> Rational<T>::Rational (T N, T D) : p(N),q(D)
{
   if(D==zero(T()))
   {
      std::cerr << "Zero denominator in Rational Number " << std::endl;
      return;
   }
   if(q < zero(T())) {p = -p; q = -q;}
   normalize();
}

template <class T> Rational<T>::Rational(const Rational<T> &r) 
   : p(r.p), q(r.q) {}

// for a std::string "a" or "a/b" or "a.b"
// spaces are allowed for "a / b"
template <class T> Rational<T>::Rational(const std::string &s)
{
  std::string s1 = s;
  std::string::size_type fraction, decimal, space;
  p = zero(T());
  q = one(T());
  // erase spaces
  space = s1.find(" ");
  while(space != std::string::npos)
  {
   s1.erase(space, 1);
   space = s1.find(" ");
  }
  fraction = s1.find("/");
  decimal = s1.find(".");

  if(fraction != std::string::npos)
  {
   std::istringstream istr(s1.substr(0,fraction));
   istr >> p;
   // the following line allows 1/2/3 == 1/6
   *this /= Rational<T>(s1.substr(fraction+1));
  }
  else if(decimal != std::string::npos)
  {
   std::string s2 = s1.substr(decimal+1);
   int power = s2.length(); // 10^power in denomenator
   // change aaa.bbbb -> aaa + bbbb/10000
   while(s2[0] == '0') s2.erase(0,1);
   *this += Rational<T>(s2 + "/" + "1" + std::string(power, '0'));
  }
  else
  {
   std::istringstream istr(s1);
   istr >> p;
  }
}

template <class T> Rational<T>::Rational(const double &d)
{
 static int base = std::numeric_limits<double>::radix;
 static std::vector<Rational<T> > digits(0);
 static Rational<T> rbase("0");
 Rational<T> rint("0"), rfrac("0"), rfact;
 double integer, fraction;
 int sign = (d<0);

 // since we don't know the type T and base is usually small
 // we can increment to find rbase
 if(digits.size() == 0)
 {
  digits.resize(base);
  for(int i=0;i< base;i++) digits[i] = rbase++;
 }

 if(sign) fraction = modf(-d,&integer);
 else fraction = modf(d,&integer);

 rfact = Rational<T>("1");
 while(floor(integer) != 0.0)
 {
  rint += digits[int(fmod(integer, base))];
  integer /= base;
  rint /= rbase;
  rfact *= rbase;
 }

 rint *= rfact;
 rfact = Rational<T>("1");
 while(fraction != 0.0)
 {
  rfrac *= rbase;
  rfact /= rbase;
  fraction *= base;
  fraction = modf(fraction, &integer);
  rfrac += digits[int(integer)];
 }
 rfrac *= rfact;
 if(sign) *this = -rint - rfrac;
 else     *this =  rint + rfrac;
}

template <class T> Rational<T>::~Rational() {}

template <class T> Rational<T>::operator double() const
{ return double(p)/double(q); }

// Member functions
template <class T> T Rational<T>::num() const { return p; }

template <class T> T Rational<T>::den() const { return q; }

template <class T> Rational<T> Rational<T>::frac() const
{
   static Rational<T> zero(zero(T())), one(one(T()));
   Rational<T> temp(*this);

   if(temp < zero)
   {
      while(temp < zero) temp = temp + one;
      return temp - one;
   }
   else
   {
      while(zero < temp) temp = temp - one;
      return temp + one;
   }
}

template <class T> void Rational<T>::normalize()
{
   T t;
   if(p < zero(T())) t = -p; 
   else              t = p;
   t = gcd(t, q);
   if(t > one(T()))  { p /= t; q /= t;}
}

// Various operators

template <class T> 
const Rational<T> & Rational<T>::operator = (const Rational<T> &r)
{ p = r.p; q = r.q; return *this; }

template <class T> Rational<T> Rational<T>::operator - () const
{ return Rational<T>(-p,q); }

template <class T> 
const Rational<T> & Rational<T>::operator += (const Rational<T> &r)
{ return *this = *this + r; }

template <class T> 
const Rational<T> & Rational<T>::operator -= (const Rational<T> &r)
{ return *this = *this - r; }

template <class T> 
const Rational<T> & Rational<T>::operator *= (const Rational<T> &r)
{ return *this = *this * r; }

template <class T> 
const Rational<T> & Rational<T>::operator /= (const Rational<T> &r)
{ return *this = *this / r; }

template <class T> 
Rational<T> Rational<T>::operator + (const Rational<T> &r2) const
{ return Rational<T> (p * r2.q + r2.p * q, q * r2.q); }

template <class T> 
Rational<T> Rational<T>::operator - (const Rational<T> &r2) const
{ return Rational<T> (p * r2.q - r2.p * q, q * r2.q); }

template <class T> 
Rational<T> Rational<T>::operator * (const Rational<T> &r2) const
{ return Rational<T> (p * r2.p, q * r2.q); }

template <class T> 
Rational<T> Rational<T>::operator / (const Rational<T> &r2) const
{ return Rational<T> (p * r2.q, q * r2.p); }

template <class T> 
Rational<T>& Rational<T>::operator ++ () { p += q; return *this; }

template <class T> 
Rational<T> Rational<T>::operator ++ (int)
{ Rational<T> r = *this; ++(*this); return r; }

template <class T> 
Rational<T>& Rational<T>::operator -- () { p -= q; return *this; }

template <class T> 
Rational<T> Rational<T>::operator -- (int)
{ Rational<T> r = *this; --(*this); return r; }

template <class T> 
int Rational<T>::operator == (const Rational<T> &r2) const
{ return (p * r2.q) == (r2.p * q); }

template <class T> 
int Rational<T>::operator != (const Rational<T> &r2) const
{ return !(*this == r2); }

template <class T> 
int Rational<T>::operator >  (const Rational<T> &r2) const
{ return (p*r2.q - r2.p*q > zero(T())); }

template <class T> 
int Rational<T>::operator <  (const Rational<T> &r2) const
{ return (p*r2.q - r2.p*q < zero(T())); }

template <class T> 
int Rational<T>::operator >= (const Rational<T> &r2) const
{ return (*this>r2) || (*this==r2); }

template <class T> 
int Rational<T>::operator <= (const Rational<T> &r2) const
{ return (*this<r2) || (*this==r2); }

template <class T> 
std::ostream & Rational<T>::output(std::ostream &s) const
{  
   switch(output_preference)
   {
     case fraction:
       if(q == one(T())) return s << p;
       return s << p << "/" << q;
       break;
     case decimal:
       return s << double(*this);
       break;
     default:
       std::cerr << "Unknown output stylei in Rational::output." << std::endl;
       return s;
       break;
   }
}

template <class T> 
std::ostream & operator << (std::ostream &s,const Rational<T> &r)
{ return r.output(s); }

template <class T> 
std::istream & Rational<T>::input(std::istream &s)
{  
   char c;
   T n, d(one(T()));
   s.clear();                 // set stream state to good
   s >> n;                    // read numerator
   if(! s.good()) return s;  // can't get an integer, just return
   c = s.peek();              // peek next character
   if(c == '/')
   {
      c = s.get();            // clear '/'
      s >> d;                 // read denominator
      if(! s.good())
      {
         s.clear(s.rdstate() | std::ios::badbit);
         return s;
      }
   }
   *this = Rational<T>(n,d);
   return s;
}

template <class T> 
std::istream & operator >> (std::istream &s,Rational<T> &r)
{ return r.input(s); }

template <class T>
void Rational<T>::output_style(output_type t)
{ output_preference = t; }

// Private member function: gcd()
template <class T> T Rational<T>::gcd (T a, T b)
{
   while(b > zero(T())) { T m = a % b; a = b; b = m; }
   return a;
}

// This function is a global function.
// It should be in a global header file.
template <class T> T abs(const T &x)
{
   if(x > zero(T())) return x;
   return -x;
}

#include "verylong.h"
template <> Rational<Verylong>::operator double() const;

#define LIBSYMBOLICCPLUSPLUS

template <> Rational<Verylong>::operator double() const { return div(p,q); }

#undef LIBSYMBOLICCPLUSPLUS

template <class T>
Rational<T> zero(Rational<T>) { return Rational<T>(zero(T())); }

template <class T>
Rational<T> one(Rational<T>) { return Rational<T>(one(T())); }

#endif
