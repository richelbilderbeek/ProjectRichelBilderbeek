
#include "fxttypes.h"

// jjnote: fixme: move asserts into function
#include "jjassert.h" // jjnote: asserts used in code: disk convolution

#include "fxtio.h"

// masscolpass.cc:
void disk_col_pass1(int fd1, int fd2,
                    double *fr, double *fi,
                    ulong nr, ulong nc, ulong xc,
                    double w,
                    int zq=0);

void disk_col_pass3(int fd1, int fd2,
                    double *fr, double *fi,
                    ulong nr, ulong nc, ulong xc,
                    double w,
                    int zq=0);

// massrowpass.cc:
void disk_row_pass(int fd1, int fd2,
                   double *fr, double *fi,
                   ulong nr, ulong nc,
                   double nx=0);

void
disk_weighted_complex_auto_convolution(int fd1, int fd2,
                                       double *fr, ulong fn, ulong al,
                                       double w,
                                       double nx,
                                       int zq1/*=0*/, int zq3/*=0*/)
//
// fd1/fd2: real/imag part of data  (#= fn*al)
// fr[0,...,fn-1]: workspace
// w:  weight for whole convolution
// nx: additional normalization factor (cf. disk_row_pass())
//
{
    double *fi = fr + fn/2;  // split workspace for real/imag part
    fn /= 2;  // semantic change: here fn means max # complex in ram

    ulong nr = al;    // # of rows
    ulong nc = fn;    // # of cols
    ulong xc = nc/al; // how many cols processed in each row pass

    jjassert( al >= 1 );
    jjassert( xc >= 1 ); // "set NOSWAP_BYTES or buy more RAM"
    jjassert( al <= nc );
    jjassert( xc*al == nc );
    jjassert( nr*xc == fn );
    jjassert( nr*nc == al*fn );


    disk_col_pass1(fd1, fd2, fr, fi,  nr, nc, xc,  w, zq1);

    disk_row_pass( fd1, fd2, fr, fi,  nr, nc,  nx);

    disk_col_pass3(fd1, fd2, fr, fi,  nr, nc, xc,  w, zq3);
}
// -------------------------
