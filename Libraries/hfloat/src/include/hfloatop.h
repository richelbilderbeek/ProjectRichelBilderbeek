#if !defined HAVE_HFLOATOP_H__
#define      HAVE_HFLOATOP_H__

// this file is #included by hfloat.h:
#if !defined HAVE_HFLOAT_H__
#error  "do not #include hfloatop.h, instead #include hfloat.h"
#endif


#include "fxt/fxtio.h"


// -------- arithmetic operators:

inline hfloat &
operator ++ (hfloat &t)  // pre-increment
{
    add(t, (ulong)1, t);
    return t;
}

inline hfloat &
operator -- (hfloat &t)  // pre-decrement
{
    sub(t, (ulong)1, t);
    return t;
}


inline hfloat & operator += (hfloat &t, const hfloat &h)  { add(t, h, t); return t; }
inline hfloat & operator -= (hfloat &t, const hfloat &h)  { sub(t, h, t); return t; }
inline hfloat & operator *= (hfloat &t, const hfloat &h)  { mul(t, h, t); return t; }
inline hfloat & operator /= (hfloat &t, const hfloat &h)  { div(t, h, t); return t; }

inline hfloat & operator += (hfloat &t, long i)  { add(t, i, t); return t; }
inline hfloat & operator -= (hfloat &t, long i)  { sub(t, i, t); return t; }
inline hfloat & operator *= (hfloat &t, long i)  { mul(t, i, t); return t; }
inline hfloat & operator /= (hfloat &t, long i)  { div(t, i, t); return t; }

inline hfloat & operator += (hfloat &t, ulong i)  { add(t, i, t); return t; }
inline hfloat & operator -= (hfloat &t, ulong i)  { sub(t, i, t); return t; }
inline hfloat & operator *= (hfloat &t, ulong i)  { mul(t, i, t); return t; }
inline hfloat & operator /= (hfloat &t, ulong i)  { div(t, i, t); return t; }

inline hfloat & operator += (hfloat &t, int i)  { add(t, (long)i, t); return t; }
inline hfloat & operator -= (hfloat &t, int i)  { sub(t, (long)i, t); return t; }
inline hfloat & operator *= (hfloat &t, int i)  { mul(t, (long)i, t); return t; }
inline hfloat & operator /= (hfloat &t, int i)  { div(t, (long)i, t); return t; }

inline hfloat & operator += (hfloat &t, uint i)  { add(t, (ulong)i, t); return t; }
inline hfloat & operator -= (hfloat &t, uint i)  { sub(t, (ulong)i, t); return t; }
inline hfloat & operator *= (hfloat &t, uint i)  { mul(t, (ulong)i, t); return t; }
inline hfloat & operator /= (hfloat &t, uint i)  { div(t, (ulong)i, t); return t; }



// -------------------------------------------

/*
inline hfloat
operator - (const hfloat &h) return h3;
//
// do not use, instead of
// h = -g;
// use
// h = g;  h.negate();
//
{
    h3 = h;
    h3.sign(-h3.sign());
    return h3;
}
*/


inline int operator == (const hfloat &h1, const hfloat &h2)  { return cmp(h1,h2) ==0; }
inline int operator != (const hfloat &h1, const hfloat &h2)  { return  cmp(h1,h2) !=0; }
inline int operator >  (const hfloat &h1, const hfloat &h2)  { return  cmp(h1,h2) >0; }
inline int operator >= (const hfloat &h1, const hfloat &h2)  { return cmp(h1,h2) >= 0; }
inline int operator <  (const hfloat &h1, const hfloat &h2)  { return  cmp(h1,h2) < 0; }
inline int operator <= (const hfloat &h1, const hfloat &h2)  { return cmp(h1,h2) <= 0; }

inline int operator == (long i, const hfloat &h)  { return cmp(h,i) ==0; }
inline int operator == (const hfloat &h, long i)  { return cmp(h,i) ==0; }
inline int operator != (long i, const hfloat &h)  { return cmp(h,i) !=0; }
inline int operator != (const hfloat &h, long i)  { return cmp(h,i) !=0; }
inline int operator >  (long i, const hfloat &h)  { return cmp(h,i) <0; }
inline int operator >  (const hfloat &h, long i)  { return cmp(h,i) >0; }
inline int operator >= (long i, const hfloat &h)  { return cmp(h,i) <=0; }
inline int operator >= (const hfloat &h, long i)  { return cmp(h,i) >=0; }
inline int operator <  (long i, const hfloat &h)  { return cmp(h,i) >0; }
inline int operator <  (const hfloat &h, long i)  { return cmp(h,i) <0; }
inline int operator <= (long i, const hfloat &h)  { return cmp(h,i) >=0; }
inline int operator <= (const hfloat &h, long i)  { return cmp(h,i) <=0; }

inline int operator == (ulong i, const hfloat &h)  { return cmp(h,i) ==0; }
inline int operator == (const hfloat &h, ulong i)  { return cmp(h,i) ==0; }
inline int operator != (ulong i, const hfloat &h)  { return cmp(h,i) !=0; }
inline int operator != (const hfloat &h, ulong i)  { return cmp(h,i) !=0; }
inline int operator >  (ulong i, const hfloat &h)  { return cmp(h,i) <0; }
inline int operator >  (const hfloat &h, ulong i)  { return cmp(h,i) >0; }
inline int operator >= (ulong i, const hfloat &h)  { return cmp(h,i) <=0; }
inline int operator >= (const hfloat &h, ulong i)  { return cmp(h,i) >=0; }
inline int operator <  (ulong i, const hfloat &h)  { return cmp(h,i) >0; }
inline int operator <  (const hfloat &h, ulong i)  { return cmp(h,i) <0; }
inline int operator <= (ulong i, const hfloat &h)  { return cmp(h,i) >=0; }
inline int operator <= (const hfloat &h, ulong i)  { return cmp(h,i) <=0; }

inline int operator == (int i, const hfloat &h)  { return cmp(h,(long)i) ==0; }
inline int operator == (const hfloat &h, int i)  { return cmp(h,(long)i) ==0; }
inline int operator != (int i, const hfloat &h)  { return cmp(h,(long)i) !=0; }
inline int operator != (const hfloat &h, int i)  { return cmp(h,(long)i) !=0; }
inline int operator >  (int i, const hfloat &h)  { return cmp(h,(long)i) <0; }
inline int operator >  (const hfloat &h, int i)  { return cmp(h,(long)i) >0; }
inline int operator >= (int i, const hfloat &h)  { return cmp(h,(long)i) <=0; }
inline int operator >= (const hfloat &h, int i)  { return cmp(h,(long)i) >=0; }
inline int operator <  (int i, const hfloat &h)  { return cmp(h,(long)i) >0; }
inline int operator <  (const hfloat &h, int i)  { return cmp(h,(long)i) <0; }
inline int operator <= (int i, const hfloat &h)  { return cmp(h,(long)i) >=0; }
inline int operator <= (const hfloat &h, int i)  { return cmp(h,(long)i) <=0; }

inline int operator == (uint i, const hfloat &h)  { return cmp(h,(ulong)i) ==0; }
inline int operator == (const hfloat &h, uint i)  { return cmp(h,(ulong)i) ==0; }
inline int operator != (uint i, const hfloat &h)  { return cmp(h,(ulong)i) !=0; }
inline int operator != (const hfloat &h, uint i)  { return cmp(h,(ulong)i) !=0; }
inline int operator >  (uint i, const hfloat &h)  { return cmp(h,(ulong)i) <0; }
inline int operator >  (const hfloat &h, uint i)  { return cmp(h,(ulong)i) >0; }
inline int operator >= (uint i, const hfloat &h)  { return cmp(h,(ulong)i) <=0; }
inline int operator >= (const hfloat &h, uint i)  { return cmp(h,(ulong)i) >=0; }
inline int operator <  (uint i, const hfloat &h)  { return cmp(h,(ulong)i) >0; }
inline int operator <  (const hfloat &h, uint i)  { return cmp(h,(ulong)i) <0; }
inline int operator <= (uint i, const hfloat &h)  { return cmp(h,(ulong)i) >=0; }
inline int operator <= (const hfloat &h, uint i)  { return cmp(h,(ulong)i) <=0; }


inline int operator >  (double d, const hfloat &h)  { return cmp(h,d) <0; }
inline int operator >  (const hfloat &h, double d)  { return cmp(h,d) >0; }
inline int operator <  (double d, const hfloat &h)  { return cmp(h,d) >0; }
inline int operator <  (const hfloat &h, double d)  { return cmp(h,d) <0; }

// -------------------------------------------


// defined in hfloatios.cc:
std::istream & operator >> (std::istream& is, hfloat &x);        // is >> x
std::ostream & operator << (std::ostream& os, const hfloat &x);  // os << x


// -------------------------------------------

// binary operators: (temporary objects --> inefficient!)

inline hfloat
operator + (const hfloat &h1, const hfloat &h2)
{
    hfloat h3;
    add(h1,h2,h3);
    return h3;
}


inline hfloat
operator + (long i, const hfloat &h)
{
    hfloat h3;
    add(h,i,h3);
    return h3;
}


inline hfloat
operator + (const hfloat &h, long i)
{
    hfloat h3;
    add(h,i,h3);
    return h3;
}


inline hfloat
operator - (const hfloat &h1, const hfloat &h2)
{
    hfloat h3;
    sub(h1,h2,h3);
    return h3;
}


inline hfloat
operator - (long i, const hfloat &h)
{
    hfloat h3;
    sub(i,h,h3);
    return h3;
}


inline hfloat
operator - (const hfloat &h, long i)
{
    hfloat h3;
    sub(h,i,h3);
    return h3;
}


inline hfloat
operator * (const hfloat &h1, const hfloat &h2)
{
    hfloat h3;
    mul(h1,h2,h3);
    return h3;
}


inline hfloat
operator * (const hfloat &h, long i)
{
    hfloat h3;
    mul(h,i,h3);
    return h3;
}


inline hfloat
operator * (long i, const hfloat &h)
{
    hfloat h3;
    mul(h,i,h3);
    return h3;
}


inline hfloat
operator / (const hfloat &h1, const hfloat &h2)
{
    hfloat h3;
    div(h1,h2,h3);
    return h3;
}

inline hfloat
operator / (const hfloat &h, long i)
{
    hfloat h3;
    div(h,i,h3);
    return h3;
}


inline hfloat
operator / (long i, const hfloat &h)
{
    hfloat h3;
    inv(h,h3);
    mul(h3,i,h3);
    return h3;
}

#endif // !defined HAVE_HFLOATOP_H__
