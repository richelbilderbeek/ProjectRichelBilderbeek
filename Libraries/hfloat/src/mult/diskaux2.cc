
#include "fxttypes.h"
#include "fxtmult.h"
#include "diskaux.h"

#include "aux1/copy.h"  // copy_cast()


void
disk_carry_thru_2limb(double *f, ulong fn, ulong al,
                      int fd,
                      uint rx, ulong &cyi,
                      LIMB *c, ulong cn, ulong coff,
                      ulong &si)
// Expect al*fn doubles on disk.
// Carry thru (from right to left) using f[0..fn-1] as workspace.
// Compute sum of digits and put to si.
{
    double cy = (double)cyi;
    ulong off = (al-1)*fn;  // last block
    ulong s = si;

    coff += off;            // offset in c[]
    while ( al )
    {
        seek_read(fd, off, f, fn);
        carry_thru(f, fn, rx, cy);

        s = sum_of_digits(f, fn, rx-1, s);

        if ( cn>=coff )
        {
            ulong n = cn - coff;
            if ( n>fn )  n = fn;
            copy_cast(f, c+coff, n);
        }

        off -= fn;
        coff -= fn;
        al--;
    }

    cyi = (ulong)cy;
    si = s;
}
// -------------------------

void
zeros2disk(double *f, ulong fn, ulong al,
            int fd, ulong off/*=0*/)
// Write  al*fn zeros to the file with filedescriptor fd.
// Start at offset off.
{
    null(f,fn);
    while ( al )
    {
        seek_write(fd, off, f, fn);
        off += fn;
        al--;
    }
}
// -------------------------

void
limb2disk(const LIMB *a, ulong an,
          double *f, ulong fn, ulong al,
          int fd)
// Write a[0..an-1] as doubles to the file with filedescriptor fd.
// If al*fn > an  then append al*fn-an zeros.
{
    ulong off = 0;

    // blocks filled with digits form a[]:
    while ( al && (an>=fn) )
    {
        copy_cast(a, f, fn);
        seek_write(fd, off, f, fn);
        off += fn;
        an -= fn;
        a += fn;
        al--;
    }

    if ( al==0 )  return;

    // block partially filled from a[]:
    copy0(a, an, f, fn);    // an<fn
    seek_write(fd, off, f, fn);
    off += fn;
    al--;

    // zeros:
    if ( al!=0 )  zeros2disk(f, fn, al, fd, off);
}
// -------------------------
