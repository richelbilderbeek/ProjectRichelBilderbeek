
#include "fft/fft.h"
#include "fft/fft-default.h"

#include "aux0/cmult.h"

#include "bits/bit2pow.h" // ld()

#include "diskaux.h"

#include "aux1/arith1.h" // multiply_val()

#include "fxttypes.h"  // ulong

#include "fft/matrixfft.h"

#include "diskaux.h"


static const int is = +1;


void
disk_row_pass(int fd1, int fd2,
              double *fr, double *fi,
              ulong nr, ulong nc,
              double nx/*=0*/)
//
// nx: additional normalization factor
//
{
    ulong ldnc = ld(nc);
    double *pr = fr,  *pi = fi;
    double nn = 1.0/(double)(nc*nr);
    if ( 0.0!=nx )  nn *= nx;
    for (ulong r=0,k=0; r<nr; ++r,k+=nc)  // k=r*nc
    {
        seek_read(fd1, k, pr, nc);
        seek_read(fd2, k, pi, nc);

        double w = (double)r/(double)nr;

        fourier_shift(pr, pi, nc, w);
        fft(pr, pi, ldnc, is);

        for (ulong j=0; j<nc; j++)  csqr(pr[j], pi[j]);

        fft(pr, pi, ldnc, -is);
        fourier_shift(pr, pi, nc, -w);

        multiply_val(pr, nc, nn);
        multiply_val(pi, nc, nn);

        seek_write(fd1, k, pr, nc);
        seek_write(fd2, k, pi, nc);
    }
}
// -------------------------



void
disk_col_pass1(int fd1, int fd2,
               double *fr, double *fi,
               ulong nr, ulong nc, ulong xc,
               double w,
               int zq/*=0*/)
//
// zq = 1  =-->  imag part is zero (at start)
//
{
    ulong n = nr*nc;
    ulong nb = nc/xc;  // how many blocks
    for (ulong b=0;  b<nb;  ++b)
    {
        double *pr, *pi;
        pr = fr;
        pi = fi;
        for (ulong j=0, kk=b*xc;  j<nr;  ++j, kk+=nc) // kk = j*nc+b*xc;
        {
            seek_read(fd1, kk, pr, xc);
            if ( zq!=1 )  seek_read(fd2, kk, pi, xc);

            if ( w!=0 )
            {
                if ( zq==1 )  fourier_shift_imag0(pr, pi, n, w, kk, xc);
                else          fourier_shift(pr, pi, n, w, kk, xc);
            }

            pr += xc;
            pi += xc;
        }

        column_ffts(fr, fi, nr, xc, is, 0, 0, 0);

        pr = fr;
        pi = fi;
        for (ulong j=0, kk=b*xc;  j<nr;  ++j, kk+=nc) // kk = j*nc+b*xc;
        {
            seek_write(fd1, kk, pr, xc);
            seek_write(fd2, kk, pi, xc);

            pr += xc;
            pi += xc;
        }
    }
}
// -------------------------


void
disk_col_pass3(int fd1, int fd2,
               double *fr, double *fi,
               ulong nr, ulong nc, ulong xc,
               double w,
               int zq/*=0*/)
//
// zq = 1  =-->  real part of output is discarded
// zq = 2  =-->  imag part of output is discarded
{
    ulong n = nr*nc;
    ulong nb = nc/xc;  // how many blocks
    for (ulong b=0;  b<nb;  ++b)
    {
        double *pr, *pi;
        pr = fr;
        pi = fi;
        for (ulong j=0, kk=b*xc;  j<nr;  ++j, kk+=nc) // kk = j*nc+b*xc;
        {
            seek_read(fd1, kk, pr, xc);
            seek_read(fd2, kk, pi, xc);

            pr += xc;
            pi += xc;
        }

        column_ffts(fr, fi, nr, xc, -is, 0, 0, 0);

        pr = fr;
        pi = fi;
        for (ulong j=0, kk=b*xc;  j<nr;  ++j, kk+=nc) // kk = j*nc+b*xc;
        {
            if ( w!=0 )   fourier_shift(pr, pi, n, -w, kk, xc);

            if ( zq!=1 )  seek_write(fd1, kk, pr, xc);
            if ( zq!=2 )  seek_write(fd2, kk, pi, xc);

            pr += xc;
            pi += xc;
        }
    }
}
// -------------------------

