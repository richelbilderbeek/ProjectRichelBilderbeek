

#if 0 // defined __GNUC__

#warning "FYI: timing uses GNU C timer (which returns user time)"

#else

#define  USE_CLOCK  0   // whether to use clock()

#if USE_CLOCK

#warning "FYI: timing uses clock() (which returns user time)"

#include <time.h>

static time_t t0;

void
start_timer()
{
    t0 = clock();
}
// ----------------------------

double
return_elapsed_time()
{
    return  1.0*(clock()-t0)/CLOCKS_PER_SEC;
}
// ----------------------------

#else // USE_CLOCK

#warning "FYI: timing uses gettimeofday() (which returns user time)"

#include <sys/time.h>  // gettimeofday()

static struct timeval t0, t1;

void
start_timer()
{
    gettimeofday( &t0, NULL );
}
// ----------------------------

//
// time (in seconds) elapsed since call of start_timer()
// resolution is microseconds, accuracy may be much less
//
double
return_elapsed_time()
{
    gettimeofday( &t1, NULL );

    double dt =
        ((double)t1.tv_sec  - (double)t0.tv_sec) +
        ((double)t1.tv_usec - (double)t0.tv_usec)*1e-6;

    return dt;
}
// ----------------------------
#endif // USE_CLOCK


#endif // !defined __GNUC__
