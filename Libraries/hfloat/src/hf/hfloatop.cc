
#include "hfloat.h"

#include <fxt/fxtio.h>

hfloat &
hfloat::operator = (const hfloat &h)
{
    if ( this==&h )  return *this; // nothing to do

    if ( h.is_zero() )  set_zero();
    else                copy(h);

    return  *this;
}
//--------------


hfloat &
hfloat::operator = (int i)
{
    if ( 0==i )  set_zero();
    else         i2hfloat((long)i,*this);

    return  *this;
}
//--------------


hfloat &
hfloat::operator = (long i)
{
    if (0==i)  set_zero();
    else       i2hfloat(i,*this);

    return *this;
}
//--------------


hfloat &
hfloat::operator = (ulong i)
{
    if (0==i)  set_zero();
    else       u2hfloat(i,*this);
    return *this;
}
//--------------


hfloat &
hfloat::operator = (double d)
{
    if (0==d)  set_zero();
    else       d2hfloat(d,*this);
    return *this;
}
//--------------

hfloat &
hfloat::operator = (const char *c)
{
    st2hfloat(c,*this);
    return *this;
}
//--------------


//hfloat::operator long() const
//{
//    long r;
//    hfloat2i(*this,r);
//    return r;
//}
////--------------
//
//
//hfloat::operator double() const
//{
//    double d;
//    hfloat2d(*this,d);
//    return d;
//}
////--------------
