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


// symbolicc++.h

// normal include headers
#include <iostream>
#include <iterator>
#include <list>
#include "cloning.h"
#include "identity.h"

// phased include headers
// according to class hierarchy
#include "symbolic/symbolic.h"  // SymbolicInterface, Symbolic ...
#include "symbolic/equation.h"  //   Equation : CloningSymbolicInterface
#include "symbolic/number.h"    //   Numeric  : CloningSymbolicInterface
#include "symbolic/product.h"   //   Product  : CloningSymbolicInterface
#include "symbolic/sum.h"       //   Sum      : CloningSymbolicInterface
#include "symbolic/symbol.h"    //   Symbol   : CloningSymbolicInterface
#include "symbolic/functions.h" //     Sin    : Symbol ...
#include "symbolic/symmatrix.h" //   SymbolicMatrix : CloningSymbolicInterface
#include "symbolic/symerror.h"  //   SymbolicError  : CloningSymbolicInterface
#include "symbolic/constants.h"
#include "symbolic/integrate.h"
#include "symbolic/solve.h"

#ifndef SYMBOLIC_CPLUSPLUS
#define SYMBOLIC_CPLUSPLUS

// Include the relevant classes in 3 phases
//  Phase 1 ensures that every class has a forward
//  declaration for use in phase 2.
//  Phase 2 ensures that every constructor and method
//  has a forward declaration for use in phase 3.
// 1. Forward declarations: class X;
// 2. Declaraions:          class X { ... };
// 3. Definitions:          X::X() ...

// This overcomes mutual recursion in dependencies,
// for example class Sum needs class Product
// and class Product needs class Sum.

// forward declarations of all classes first
#define SYMBOLIC_FORWARD
#include "symbolic/symbolicc++.h"
#undef  SYMBOLIC_FORWARD

typedef list<Equation> Equations;
typedef list<Equations> PatternMatches;

// declarations of classes without definitions
#define SYMBOLIC_DECLARE
#include "symbolic/symbolicc++.h"
#undef  SYMBOLIC_DECLARE

// declarations for non-member functions
// also used in definition phase for clarity

Symbolic expand(const SymbolicInterface&);
ostream &operator<<(ostream &,const Symbolic &);
ostream &operator<<(ostream &,const Equation &);
Symbolic operator+(const Symbolic &);
Symbolic operator+(const Symbolic &,const Symbolic &);
Symbolic operator+(const int &,const Symbolic &);
Symbolic operator+(const Symbolic &,const int &);
Symbolic operator+(const double &,const Symbolic &);
Symbolic operator+(const Symbolic &,const double &);
Symbolic operator++(Symbolic &);
Symbolic operator++(Symbolic &,int);
Symbolic operator-(const Symbolic &);
Symbolic operator-(const Symbolic &,const Symbolic &);
Symbolic operator-(const int &,const Symbolic &);
Symbolic operator-(const Symbolic &,const int &);
Symbolic operator-(const double &,const Symbolic &);
Symbolic operator-(const Symbolic &,const double &);
Symbolic operator--(Symbolic &);
Symbolic operator--(Symbolic &,int);
Symbolic operator*(const Symbolic &,const Symbolic &);
Symbolic operator*(const int &,const Symbolic &);
Symbolic operator*(const Symbolic &,const int &);
Symbolic operator*(const double &,const Symbolic &);
Symbolic operator*(const Symbolic &,const double &);
Symbolic operator/(const Symbolic &,const Symbolic &);
Symbolic operator/(const int &,const Symbolic &);
Symbolic operator/(const Symbolic &,const int &);
Symbolic operator/(const double &,const Symbolic &);
Symbolic operator/(const Symbolic &,const double &);
Symbolic operator+=(Symbolic &,const Symbolic &);
Symbolic operator+=(Symbolic &,const int &);
Symbolic operator+=(Symbolic &,const double &);
Symbolic operator-=(Symbolic &,const Symbolic &);
Symbolic operator-=(Symbolic &,const int &);
Symbolic operator-=(Symbolic &,const double &);
Symbolic operator*=(Symbolic &,const Symbolic &);
Symbolic operator*=(Symbolic &,const int &);
Symbolic operator*=(Symbolic &,const double &);
Symbolic operator/=(Symbolic &,const Symbolic &);
Symbolic operator/=(Symbolic &,const int &);
Symbolic operator/=(Symbolic &,const double &);
Equation operator==(const Symbolic &,const Symbolic &);
Equation operator==(const Symbolic &,int);
Equation operator==(int,const Symbolic &);
Equation operator==(const Symbolic &,double);
Equation operator==(double,const Symbolic &);
int operator!=(const Symbolic &,const Symbolic &);
int operator!=(const Symbolic &,int);
int operator!=(int,const Symbolic &);
int operator!=(const Symbolic &,double);
int operator!=(double,const Symbolic &);
Symbolic sin(const Symbolic &);
Symbolic cos(const Symbolic &);
Symbolic tan(const Symbolic &);
Symbolic cot(const Symbolic &);
Symbolic sec(const Symbolic &);
Symbolic csc(const Symbolic &);
Symbolic sinh(const Symbolic &);
Symbolic cosh(const Symbolic &);
Symbolic ln(const Symbolic &);
Symbolic log(const Symbolic &,const Symbolic &);
Symbolic pow(const Symbolic &,const Symbolic &);
Symbolic operator^(const Symbolic &,const Symbolic &);
Symbolic operator^(const Symbolic &,int);
Symbolic operator^(int,const Symbolic &);
Symbolic operator^(const Symbolic &,double);
Symbolic operator^(double,const Symbolic &);
Symbolic exp(const Symbolic &);
Symbolic sqrt(const Symbolic &);
Symbolic factorial(const Symbolic &);
Symbolic gamma(const Symbolic &);
Symbolic df(const Symbolic &,const Symbolic &);
Symbolic df(const Symbolic &,const Symbolic &,unsigned int);
Symbolic &rhs(Equations &,const Symbolic &);
Symbolic &lhs(Equations &,const Symbolic &);
template<> Symbolic zero(Symbolic);
template<> Symbolic one(Symbolic);
Equations operator,(const Equation &,const Equation &);
Equations operator,(const Equations &,const Equation &);
Equations operator,(const Equation &,const Equations &);
list<Symbolic> operator,(const Symbolic &,const Symbolic &);
list<Symbolic> operator,(const int &,const Symbolic &);
list<Symbolic> operator,(const double &,const Symbolic &);
list<Symbolic> operator,(const Symbolic &,const int &);
list<Symbolic> operator,(const Symbolic &,const double &);
list<Symbolic> operator,(const list<Symbolic> &,const Symbolic &);
list<Symbolic> operator,(const list<Symbolic> &,const int &);
list<Symbolic> operator,(const list<Symbolic> &,const double &);
list<Symbolic> operator,(const Symbolic &,const list<Symbolic> &);
list<Symbolic> operator,(const int &,const list<Symbolic> &);
list<Symbolic> operator,(const double &,const list<Symbolic> &);
list<list<Symbolic> >
operator,(const list<Symbolic> &,const list<Symbolic> &);
list<list<Symbolic> >
operator,(const list<list<Symbolic> > &,const list<Symbolic> &);
list<list<Symbolic> >
operator,(const list<Symbolic> &,const list<list<Symbolic> > &);
Equation operator,(const Symbolic &, const Equation &);
Equation operator,(const list<Symbolic> &, const Equation &);
ostream &operator<<(ostream &,const Equations &);
ostream &operator<<(ostream &,const list<Symbolic> &);
Symbolic tr(const Symbolic &);
Symbolic trace(const Symbolic &);
Symbolic det(const Symbolic &);
Symbolic determinant(const Symbolic &);
Symbolic kron(const Symbolic &,const Symbolic &);
Symbolic dsum(const Symbolic &,const Symbolic &);
Symbolic hadamard(const Symbolic &,const Symbolic &);
void pattern_match_TRUE(PatternMatches &);
void pattern_match_FALSE(PatternMatches &);
int pattern_match_AND(Equations&, const Equation&);
int pattern_match_AND(Equations&, const Equations&);
void pattern_match_AND(PatternMatches &, const Equation&);
void pattern_match_AND(PatternMatches &, const Equations&);
void pattern_match_AND(PatternMatches &, const PatternMatches &);
void pattern_match_OR(PatternMatches &, const Equation&);
void pattern_match_OR(PatternMatches &, const Equations&);
void pattern_match_OR(PatternMatches &, const PatternMatches &);

// definitions for classes, member functions
#define SYMBOLIC_DEFINE
#include "symbolic/symbolicc++.h"
#undef SYMBOLIC_DEFINE

#define LIBSYMBOLICCPLUSPLUS

// definitions for non-member functions
// also used in definition phase for clarity

Symbolic expand(const SymbolicInterface &s)
{ return s.expand(); }

ostream &operator<<(ostream &o,const Symbolic &s)
{ s.print(o); return o; }

ostream &operator<<(ostream &o,const Equation &s)
{ s.print(o); return o; }

Symbolic operator+(const Symbolic &s)
{ return s; }

Symbolic operator+(const Symbolic &s1,const Symbolic &s2)
{ return Sum(s1,s2); }

Symbolic operator+(const int &s1,const Symbolic &s2)
{ return Symbolic(Number<int>(s1)) + s2; }

Symbolic operator+(const Symbolic &s1,const int &s2)
{ return s1 + Symbolic(Number<int>(s2)); }

Symbolic operator+(const double &s1,const Symbolic &s2)
{ return Symbolic(Number<double>(s1)) + s2; }

Symbolic operator+(const Symbolic &s1,const double &s2)
{ return s1 + Symbolic(Number<double>(s2)); }

Symbolic operator++(Symbolic &s)
{ return s = s + 1; }

Symbolic operator++(Symbolic &s,int)
{ Symbolic t = s; ++s; return t; }

Symbolic operator-(const Symbolic &s)
{ return Product(Number<int>(-1),s); }

Symbolic operator-(const Symbolic &s1,const Symbolic &s2)
{ return Sum(s1,-s2); }

Symbolic operator-(const int &s1,const Symbolic &s2)
{ return Symbolic(s1) - s2; }

Symbolic operator-(const Symbolic &s1,const int &s2)
{ return s1 - Symbolic(s2); }

Symbolic operator-(const double &s1,const Symbolic &s2)
{ return Symbolic(s1) - s2; }

Symbolic operator-(const Symbolic &s1,const double &s2)
{ return s1 - Symbolic(s2); }

Symbolic operator--(Symbolic &s)
{ return s = s - 1; }

Symbolic operator--(Symbolic &s,int)
{ Symbolic t = s; --s; return t; }

Symbolic operator*(const Symbolic &s1,const Symbolic &s2)
{ return Product(s1,s2); }

Symbolic operator*(const int &s1,const Symbolic &s2)
{ return Symbolic(s1) * s2; }

Symbolic operator*(const Symbolic &s1,const int &s2)
{ return s1 * Symbolic(s2); }

Symbolic operator*(const double &s1,const Symbolic &s2)
{ return Symbolic(s1) * s2; }

Symbolic operator*(const Symbolic &s1,const double &s2)
{ return s1 * Symbolic(s2); }

Symbolic operator/(const Symbolic &s1,const Symbolic &s2)
{ return Product(s1,Power(s2,Number<int>(-1))); }

Symbolic operator/(const int &s1,const Symbolic &s2)
{ return Symbolic(s1) / s2; }

Symbolic operator/(const Symbolic &s1,const int &s2)
{ return s1 / Symbolic(s2); }

Symbolic operator/(const double &s1,const Symbolic &s2)
{ return Symbolic(s1) / s2; }

Symbolic operator/(const Symbolic &s1,const double &s2)
{ return s1 / Symbolic(s2); }

Symbolic operator+=(Symbolic &s1,const Symbolic &s2)
{ return s1 = s1 + s2; }

Symbolic operator+=(Symbolic &s1,const int &s2)
{ return s1 = s1 + s2; }

Symbolic operator+=(Symbolic &s1,const double &s2)
{ return s1 = s1 + s2; }

Symbolic operator-=(Symbolic &s1,const Symbolic &s2)
{ return s1 = s1 - s2; }

Symbolic operator-=(Symbolic &s1,const int &s2)
{ return s1 = s1 - s2; }

Symbolic operator-=(Symbolic &s1,const double &s2)
{ return s1 = s1 - s2; }

Symbolic operator*=(Symbolic &s1,const Symbolic &s2)
{ return s1 = s1 * s2; }

Symbolic operator*=(Symbolic &s1,const int &s2)
{ return s1 = s1 * s2; }

Symbolic operator*=(Symbolic &s1,const double &s2)
{ return s1 = s1 * s2; }

Symbolic operator/=(Symbolic &s1,const Symbolic &s2)
{ return s1 = s1 / s2; }

Symbolic operator/=(Symbolic &s1,const int &s2)
{ return s1 = s1 / s2; }

Symbolic operator/=(Symbolic &s1,const double &s2)
{ return s1 = s1 / s2; }

Equation operator==(const Symbolic &s1,const Symbolic &s2)
{ return Equation(s1,s2); }

Equation operator==(const Symbolic &s1,int i)
{ return s1 == Symbolic(i); }

Equation operator==(int i,const Symbolic &s1)
{ return Symbolic(i) == s1; }

Equation operator==(const Symbolic &s1,double d)
{ return s1 == Symbolic(d); }

Equation operator==(double d,const Symbolic &s1)
{ return Symbolic(d) == s1; }

int operator!=(const Symbolic &s1,const Symbolic &s2)
{ return !s1.compare(s2); }

int operator!=(const Symbolic &s1,int i)
{ return s1 != Symbolic(i); }

int operator!=(int i,const Symbolic &s1)
{ return Symbolic(i) != s1; }

int operator!=(const Symbolic &s1,double d)
{ return s1 != Symbolic(d); }

int operator!=(double d,const Symbolic &s1)
{ return Symbolic(d) != s1; }

Symbolic sin(const Symbolic &s)
{ return Sin(s); }

Symbolic cos(const Symbolic &s)
{ return Cos(s); }

Symbolic tan(const Symbolic &s)
{ return sin(s) / cos(s); }

Symbolic cot(const Symbolic &s)
{ return cos(s) / sin(s); }

Symbolic sec(const Symbolic &s)
{ return 1 / cos(s); }

Symbolic csc(const Symbolic &s)
{ return 1 / sin(s); }

Symbolic sinh(const Symbolic &s)
{ return Sinh(s); }

Symbolic cosh(const Symbolic &s)
{ return Cosh(s); }

Symbolic ln(const Symbolic &s)
{ return Log(SymbolicConstant::e,s); }

Symbolic log(const Symbolic &a,const Symbolic &b)
{ return Log(a,b); }

Symbolic pow(const Symbolic &s,const Symbolic &n)
{ return Power(s,n); }

Symbolic operator^(const Symbolic &s,const Symbolic &n)
{ return Power(s,n); }

Symbolic operator^(const Symbolic &s,int i)
{ return Power(s,Symbolic(i)); }

Symbolic operator^(int i,const Symbolic &s)
{ return Power(Symbolic(i),i); }

Symbolic operator^(const Symbolic &s,double d)
{ return Power(s,Symbolic(d)); }

Symbolic operator^(double d,const Symbolic &s)
{ return Power(Symbolic(d),s); }

Symbolic exp(const Symbolic &s)
{ return SymbolicConstant::e ^ s; }

Symbolic sqrt(const Symbolic &s)
{ return s ^ (Number<int>(1) / 2); }

Symbolic factorial(const Symbolic &s)
{ return Gamma(s + 1); }

Symbolic gamma(const Symbolic &s)
{ return Gamma(s); }

Symbolic df(const Symbolic &s,const Symbolic &x)
{ return s.df(x); }

Symbolic df(const Symbolic &s,const Symbolic &x,unsigned int i)
{
 Symbolic r = s;
 while(i-- > 0) r = r.df(x);
 return r;
}

Symbolic &rhs(Equations &l,const Symbolic &lhs)
{
 Equations::iterator i = l.begin();
 for(i=l.begin();i!=l.end();++i)
  if(i->lhs == lhs) return i->rhs;
 cerr << "Equation list does not contain lhs " << lhs << endl;
 throw SymbolicError(SymbolicError::NoMatch);
 return i->rhs;
}

Symbolic &lhs(Equations &l,const Symbolic &rhs)
{
 Equations::iterator i = l.begin();
 for(i=l.begin();i!=l.end();++i)
  if(i->rhs == rhs) return i->lhs;
 cerr << "Equation list does not contain rhs " << rhs << endl;
 throw SymbolicError(SymbolicError::NoMatch);
 return i->lhs;
}

template<> Symbolic zero(Symbolic) { return Number<int>(0); }

template<> Symbolic one(Symbolic) { return Number<int>(1); }

Equations
operator,(const Equation &x,const Equation &y)
{
 Equations l;
 l.push_back(x); l.push_back(y);
 return l;
}

Equations
operator,(const Equations &x,const Equation &y)
{
 Equations l(x);
 l.push_back(y);
 return l;
}

Equations
operator,(const Equation &x,const Equations &y)
{
 Equations l(y);
 l.push_front(x);
 return l;
}

list<Symbolic>
operator,(const Symbolic &x,const Symbolic &y)
{
 list<Symbolic> l;
 l.push_back(x);
 l.push_back(y);
 return l;
}

list<Symbolic> operator,(const int &x,const Symbolic &y)
{ return (Symbolic(x), y); }

list<Symbolic> operator,(const double &x,const Symbolic &y)
{ return (Symbolic(x), y); }

list<Symbolic> operator,(const Symbolic &x,const int &y)
{ return (x,Symbolic(y)); }

list<Symbolic> operator,(const Symbolic &x,const double &y)
{ return (x,Symbolic(y)); }

list<Symbolic>
operator,(const list<Symbolic> &x,const Symbolic &y)
{
 list<Symbolic> l(x);
 l.push_back(y);
 return l;
}

list<Symbolic> operator,(const list<Symbolic> &x,const int &y)
{ return (x, Symbolic(y)); }

list<Symbolic> operator,(const list<Symbolic> &x,const double &y)
{ return (x, Symbolic(y)); }

list<Symbolic>
operator,(const Symbolic &x,const list<Symbolic> &y)
{
 list<Symbolic> l(y);
 l.push_front(x);
 return l;
}

list<Symbolic> operator,(const int &x,const list<Symbolic> &y)
{ return (Symbolic(x), y); }

list<Symbolic> operator,(const double &x,const list<Symbolic> &y)
{ return (Symbolic(x), y); }

list<list<Symbolic> >
operator,(const list<Symbolic> &x,const list<Symbolic> &y)
{
 list<list<Symbolic> > l;
 l.push_back(x); l.push_back(y);
 return l;
}

list<list<Symbolic> >
operator,(const list<list<Symbolic> > &x,const list<Symbolic> &y)
{
 list<list<Symbolic> > l(x);
 l.push_back(y);
 return l;
}

list<list<Symbolic> >
operator,(const list<Symbolic> &x,const list<list<Symbolic> > &y)
{
 list<list<Symbolic> > l(y);
 l.push_front(x);
 return l;
}

Equation operator,(const Symbolic &x, const Equation &e)
{
 if(x.type() == typeid(UniqueSymbol) || x.type() != typeid(Symbol))
 {
  Equation p = e;
  p.free.push_front(x);
  return p;
 }

 UniqueSymbol u(*CastPtr<Symbol>(x));
 Equation p = e;
 p.free.push_front(u);
 p.lhs = p.lhs[x == u];
 p.rhs = p.rhs[x == u];
 return p;
}

Equation operator,(const list<Symbolic> &x, const Equation &e)
{
 Equation p = e;
 list<Symbolic>::const_reverse_iterator i;
 for(i=x.rbegin(); i!=x.rend(); ++i)
  if(i->type() != typeid(UniqueSymbol) && i->type() == typeid(Symbol))
  {
   UniqueSymbol u(*CastPtr<Symbol>(*i));
   p.free.push_front(u);
   p.lhs = p.lhs[*i == u];
   p.rhs = p.rhs[*i == u];
  }
  else p.free.push_front(x);
 return p;
}

ostream &operator<<(ostream &o,const Equations &e)
{
 Equations::const_iterator i = e.begin();
 o << "[ ";
 while(i != e.end())
 {
  o << *(i++);
  if(i != e.end()) o << ",\n  ";
 }
 o << " ]" << endl;
 return o;
}

ostream &operator<<(ostream &o,const list<Symbolic> &e)
{
 list<Symbolic>::const_iterator i = e.begin();
 o << "[ ";
 while(i != e.end())
 {
  o << *(i++);
  if(i != e.end()) o << ", ";
 }
 o << " ]" << endl;
 return o;
}

Symbolic tr(const Symbolic &x) { return Trace(x); }

Symbolic trace(const Symbolic &x) { return Trace(x); }

Symbolic det(const Symbolic &x) { return Determinant(x); }

Symbolic determinant(const Symbolic &x) { return Determinant(x); }

Symbolic kron(const Symbolic &x,const Symbolic &y)
{ return Kronecker(x,y); }

Symbolic dsum(const Symbolic &x,const Symbolic &y)
{ return DirectSum(x,y); }

Symbolic hadamard(const Symbolic &x,const Symbolic &y)
{ return Hadamard(x,y); }

void pattern_match_TRUE(PatternMatches &l)
{
 PatternMatches p;
 // successful match, without bindings
 p.push_back(Equations());
 l = p;
}

void pattern_match_FALSE(PatternMatches &l)
{ l = PatternMatches(); /* empty: no matches */ }

int pattern_match_AND(Equations &l, const Equation &e)
{
 Equations::iterator i;
 for(i=l.begin(); i!=l.end(); ++i)
 {
  if(i->lhs == e.lhs && i->rhs != e.rhs)
   return 0; // conflicting binding
  if(i->lhs == e.lhs && i->rhs == e.rhs)
   return 1; // already added
 }
 l.push_back(e);
 return 1;
}

int pattern_match_AND(Equations &l, const Equations &e)
{
 Equations::const_iterator j;
 for(j=e.begin();j!=e.end();++j)
  if(!pattern_match_AND(l,*j)) return 0;
 return 1;
}

void pattern_match_AND(PatternMatches &l, const Equation &e)
{
 PatternMatches::iterator i;
 
 for(i=l.begin();i!=l.end();)
 {
  Equations eq(*i);
  if(pattern_match_AND(eq,e)) *(i++) = eq;
  else i = l.erase(i);
 }
}

void pattern_match_AND(PatternMatches &l, const Equations &e)
{
 PatternMatches::iterator i;

 for(i=l.begin();i!=l.end();)
 {
  Equations eq(*i);
  if(pattern_match_AND(eq,e)) *(i++) = eq;
  else i = l.erase(i);
 }
}

void pattern_match_AND(PatternMatches &l, const PatternMatches &e)
{
 PatternMatches::iterator i;
 PatternMatches::const_iterator j;
 PatternMatches newl;

 for(i=l.begin();i!=l.end();++i)
  for(j=e.begin();j!=e.end();++j)
  {
   Equations eq(*i);
   if(pattern_match_AND(eq,*j)) newl.push_back(eq);
  }

 l = newl;
}

void pattern_match_OR(PatternMatches &l, const Equation &e)
{
 Equations eq;
 eq.push_back(e);
 pattern_match_OR(l, eq);
}

void pattern_match_OR(PatternMatches &l, const Equations &e)
{
 PatternMatches::iterator i;
 Equations::const_iterator j, k;
 for(i=l.begin(); i!=l.end(); ++i)
 {
  if(i->size() != e.size()) continue;
  for(j=i->begin(); j!=i->end(); ++j)
  {
   for(k=e.begin(); k!=e.end(); ++k) if(j->compare(*k)) break;
   if(k == e.end()) break;
  }
  if(j == i->end()) return;
 }
 if(i == l.end()) l.push_back(e);
}

void pattern_match_OR(PatternMatches &l, const PatternMatches &e)
{
 PatternMatches::const_iterator i;
 for(i=e.begin(); i!=e.end(); ++i)
  pattern_match_OR(l, *i);
//l.insert(l.end(), e.begin(), e.end());
}

#undef LIBSYMBOLICCPLUSPLUS

#endif
