
#include "fxttypes.h"
//#include "aux0/timer.h"
#include "fxtmult.h"  // diskio
#include "diskaux.h"

#include "jjassert.h"  // jjnote: asserts used in code: disk operation errors

//#include <sys/time.h>  // gettimeofday(), timeval
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>  // EBADF etc.
#include <cstdio>
#include <errno.h>

#include "fxtio.h"


#define  PRINTRW  0
//
#if  ( PRINTRW==1 )
#warning  'FYI: verbose disk read/write'
#endif

//static timeval t0, t1;


void
seek_read(int fd, ulong off, double *f, ulong fn)
// Read doubles f[0..fn-1] from file with filedescriptor fd.
// Start in file after (double) offset off.
{
#if  ( PRINTRW==1 )
    cerr << "seek_read():"
         << "  d_off=" << off
         << "  d_len="<< fn
         << "  d_end="<< off+fn-1
         << "  c_end="<< (off+fn)*sizeof(double)-1
         << endl;
#endif

    v_seek_read(fd, off*sizeof(double), (void *)f, fn*sizeof(double)); // jjcast
}
// -------------------------


void
v_seek_read(int fd, ulong off, void *f, ulong fn)
// From file with filedescriptor fd read fn bytes into f[].
// Start in file after (byte) offset off.
// Called by seek_read().
{
//    gettimeofday(&t0, 0);
    ulong w;

    w = (ulong)lseek(fd, (off_t)off, SEEK_SET);  // jjcast
//    fxtmult::ndiskseeks += 1;
    if ( -1UL==w )
    {
        perror("lseek");
        jjassert( 0 );
    }

    w = (ulong)read(fd, f, (size_t)fn);  // jjcast
    if ( w < fn )
    {
        perror("read");
        jjassert( 0 );
    }

//    gettimeofday(&t1, 0);
//    fxtmult::diskiotime += timediff(t0, t1);
//    fxtmult::diskio += (double)fn;
}
// -------------------------


void
seek_write(int fd, ulong off, double *f, ulong fn)
// Write doubles from f[0..fn-1] to file with filedescriptor fd.
// Start in file after (double) offset off.
{
#if  ( PRINTRW==1 )
    cerr << "seek_write():"
         << "  doff=" << off
         << "  dlen="<< fn
         << "  d_end="<< off+fn-1
         << "  c_end="<< (off+fn)*sizeof(double)-1
         << endl;
#endif

    v_seek_write(fd, off*sizeof(double), (void *)f, fn*sizeof(double)); // jjcast
}
// -------------------------


void
v_seek_write(int fd, ulong off, void *f, ulong fn)
// To file with filedescriptor fd write fn bytes from f[].
// Start in file after (byte) offset off.
// Called by seek_write().
{
//    gettimeofday(&t0, 0);
    ulong w;

    w = (ulong)lseek(fd, (off_t)off, SEEK_SET);  // jjcast
//    fxtmult::ndiskseeks += 1;
    if ( -1UL==w )
    {
        perror("lseek");
        jjassert( 0 );
    }

    w = (ulong)write(fd, f, fn);  // jjcast
//    w = TEMP_FAILURE_RETRY (write (fd, f, fn));
    if ( w < fn )
    {
        perror("write");
        jjassert( 0 );
    }

//    gettimeofday(&t1, 0);
//    fxtmult::diskiotime += timediff(t0, t1);
//    fxtmult::diskio += (double)fn;
}
// -------------------------



void
open_or_die(const char *fn, int *fd)
// Open file.  Die if that fails.
{
    int flag = O_RDWR | O_CREAT;
//    int flag = O_RDWR | O_CREAT | O_TRUNC;  // debug

    *fd = open(fn, flag, 0600);
    jjassert( -1!=*fd );
}
// -------------------------

void
close_or_die(int fd)
// Close file.  Die if that fails.
{
    int w = close(fd);
    jjassert( 0==w );
}
// -------------------------

