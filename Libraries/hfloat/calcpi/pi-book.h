#if !defined HAVE_PI_BOOK_H__
#define      HAVE_PI_BOOK_H__


#include "hfloat.h"
#include <cstdio>
#include <cstring>


void do_examples(long n, int arg2, const char *argv0, char *fname);
void examples_usage(const char *argv0);

void pi_usage(const char *argv0);
void other_usage(const char *argv0);

void time_usage(const char *argv0);
void test_usage(const char *argv0);


int feigenbaum(ulong n);

void pi_check(long n, hfloat &r);

int exp_pi163(long n, hfloat &r);              // exp(pi*sqrt(163))
int euler_e(hfloat &e);                        // 2.718281828459045...
int euler_e_series(hfloat &e);                 // 2.718281828459045...
int log2(long n, hfloat &l);                   // log(2)=
int catalan(long n, hfloat &c);                //

// yourstuff.cc:
int your_stuff(long n, hfloat &r);              // your experiments !

#endif // !defined HAVE_PI_BOOK_H__
