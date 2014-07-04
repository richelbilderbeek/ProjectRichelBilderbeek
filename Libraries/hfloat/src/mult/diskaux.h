#if !defined HAVE_DISKAUX_H__
#define      HAVE_DISKAUX_H__

#include "fxttypes.h"   // for ulong, LIMB

// mult/diskaux.cc:
void seek_read(int fd1, ulong off, double *f, ulong fn);
void v_seek_read(int fd1, ulong off, void *f, ulong fn);
void seek_write(int fd1, ulong off, double *f, ulong fn);
void v_seek_write(int fd1, ulong off, void *f, ulong fn);

void open_or_die(const char *fn, int *fd);
void close_or_die(int fd);


// mult/diskaux2.cc:
void disk_carry_thru_2limb(double *f, ulong fn, ulong al,
                           int fd1,
                           uint rx, ulong &cy,
                           LIMB *c, ulong cn, ulong coff,
                           ulong &sod);

void zeros2disk(double *f, ulong fn, ulong al,
                int fd, ulong off=0);

void limb2disk(const LIMB *a, ulong an,
               double *f, ulong fn, ulong al,
               int fd);


#endif // !defined HAVE_DISKAUX_H__
