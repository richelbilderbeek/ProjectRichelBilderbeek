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


// cloning.h

#ifndef SYMBOLIC_CPLUSPLUS_CLONING
#define SYMBOLIC_CPLUSPLUS_CLONING

#include <typeinfo>

using namespace std;

class Cloning
{
 private: int refcount;
          void (*free_p)(Cloning*);
          template <class T> static void free(Cloning*);

 public:  Cloning();
          Cloning(const Cloning&);
          virtual ~Cloning();

          virtual Cloning *clone() const = 0;
          template <class T> static Cloning *clone(const T&);
          static void reference(Cloning*);
          static void unreference(Cloning*);
};

class CloningPtr
{
 protected: Cloning *value;

 public:    CloningPtr();
            CloningPtr(const Cloning&);
            CloningPtr(const CloningPtr&);
            ~CloningPtr();

            CloningPtr &operator=(const Cloning&);
            CloningPtr &operator=(const CloningPtr&);
};

template <class T>
class CastPtr: public CloningPtr
{
 public:  CastPtr();
          CastPtr(const Cloning&);
          CastPtr(const CloningPtr&);
          ~CastPtr();

          T *operator->() const;
          T &operator*() const;
};

#define LIBSYMBOLICCPLUSPLUS

///////////////////////////////
// Cloning Implementation    //
///////////////////////////////

Cloning::Cloning() : refcount(0), free_p(0) {}

Cloning::Cloning(const Cloning &c) : refcount(c.refcount), free_p(c.free_p) { }

Cloning::~Cloning() {}

#undef LIBSYMBOLICCPLUSPLUS

template <class T> Cloning *Cloning::clone(const T &t)
{
 T *tp = new T(t);
 tp->refcount = 1;
 tp->free_p = Cloning::free<T>;
 return tp;
}

template <class T> void Cloning::free(Cloning *c)
{
 T *tp = dynamic_cast<T*>(c);
 if(tp != 0) delete tp;
}

#define LIBSYMBOLICCPLUSPLUS

void Cloning::reference(Cloning *c)
{ if(c != 0 && c->refcount != 0) c->refcount++; }

void Cloning::unreference(Cloning *c)
{
 if(c != 0 && c->refcount != 0 && c->free_p != 0)
 {
  if(c->refcount == 1) c->free_p(c);
  else c->refcount--;
 }
}

///////////////////////////////
// CloningPtr Implementation //
///////////////////////////////

CloningPtr::CloningPtr() : value(0) { }

CloningPtr::CloningPtr(const Cloning &p)
{ value = p.clone(); }

CloningPtr::CloningPtr(const CloningPtr &p) : value(p.value)
{ Cloning::reference(value); }

CloningPtr::~CloningPtr()
{ Cloning::unreference(value); }

CloningPtr &CloningPtr::operator=(const Cloning &p)
{
 if(value == &p) return *this;
 Cloning::unreference(value);
 value = p.clone();
 return *this;
}

CloningPtr &CloningPtr::operator=(const CloningPtr &p)
{
 if(this == &p) return *this;
 if(value == p.value) return *this;
 Cloning::unreference(value);
 Cloning::reference(value = p.value);
 return *this;
}

#undef LIBSYMBOLICCPLUSPLUS

///////////////////////////////
// CastPtr Implementation    //
///////////////////////////////

template <class T> CastPtr<T>::CastPtr() : CloningPtr() {}

template <class T> CastPtr<T>::CastPtr(const Cloning &p) : CloningPtr(p) {}

template <class T> CastPtr<T>::CastPtr(const CloningPtr &p) : CloningPtr(p) {}

template <class T> CastPtr<T>::~CastPtr() {}

template <class T> T *CastPtr<T>::operator->() const
{
 T *tp = dynamic_cast<T*>(value);
 if(tp == 0) throw bad_cast();
 return tp;
}

template <class T> T &CastPtr<T>::operator*() const
{
 T *tp = dynamic_cast<T*>(value);
 if(tp == 0) throw bad_cast();
 return *tp;
}

#endif
