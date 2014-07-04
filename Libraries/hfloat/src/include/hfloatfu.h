#if !defined HAVE_HFLOATFU_H__
#define      HAVE_HFLOATFU_H__


// this file is #included by hfloat.h:
#if !defined HAVE_HFLOAT_H__
#error  "do not #include hfloatfu.h, instead #include hfloat.h"
#endif


#include "fxt/fxtio.h"


// ----------------------------------------------
// hf/init.cc:
// constructor and destructor for hfloat_init class

// ----------------------------------------------
// hf/print.cc:

// print n LIMBs of r:
void print(const hfloat &r, ulong n=0);

// print what[] and n LIMBs of r:
void print(const char *what, const hfloat &a, ulong n=0);

// print what[] and the n last LIMBs of r:
void print_last(const char *what, const hfloat &a, ulong n);

// save to os n LIMBs of r:
void save(std::ostream &os, const hfloat &r, ulong n=0);

// save to os what[] and n LIMBs of r:
void save(std::ostream &os, const char *what, const hfloat &a, ulong n=0);
void save_nn(std::ostream &os, const char *what, const hfloat &a, ulong n=0);

// save to os what[] and the n last LIMBs of r:
void save_last(std::ostream &os, const char *what, const hfloat &a, ulong n);

// save to file named fname[] r:
void save(const char* fname, const hfloat &r);

void set_pretty_print(bool q);  // mostly for debugging


// ----------------------------------------------
// hf/binsave.cc:
// binary save to file named fname[] the LIMBs of r:
int binsave_limbs(const char *fname, const hfloat &a, long n=0, long s=0);


// ----------------------------------------------
// hf/convert.cc
void  i2hfloat_prec_adj(long i, hfloat &x);   // x = i, precision is set
void  u2hfloat_prec_adj(ulong i, hfloat &x);  // x = i, precision is set
ulong i2hfloat(long i, hfloat &x);            // x = i
ulong u2hfloat(ulong i, hfloat &x);           // x = i
int   hfloat2i(const hfloat &x, long &i);     // i = x
ulong d2hfloat(double d, hfloat &x);          // x = d
int   hfloat2d(const hfloat &x, double &d);   // d = x
ulong st2hfloat(const char *str, hfloat &x);  // x = str
// ... and of course there is (hfloat)x = (hfloat)y


// ----------------------------------------------
// hf/compare.cc:
int cmp(const hfloat &a, const hfloat &b);        // ? a><= b
int cmp(const hfloat &a, const hfloat &b, ulong &idx); // ? a><= b
int cmp(const hfloat &a, long b);                 // ? a><= b
int cmp(const hfloat &a, ulong b);                // ? a><= b
int cmp(const hfloat &a, double b);               // ? a><= b

//int cmp_abs(const hfloat &a, double b);           // ? |a|><= |b|

long cmp1(const hfloat &a);                        // ? a><= 1
//long cmp_limbs(const hfloat &a, const hfloat &b);  // ? how many LIMBs do agree
//ulong diff_limbs(const hfloat &a, const hfloat &b); // ? how many LIMBs disagree

//// returns 0 if exponent(a-b) >= 0 else returns -exponent(a-b) (which is > 0):
ulong agree_prec(const hfloat &a, const hfloat &b, hfloat &x);

//// whether a==d within relative error relerr:
int approximate(const hfloat &a, double d, double relerr=1.0e-12);


// ----------------------------------------------
// hf/funcsadd.cc:
void add(const hfloat &a, const hfloat &b, hfloat &c, ulong cp=0);  // c = a+b
void add(const hfloat &a, long i, hfloat &c);           // c = a+i
void add(const hfloat &a, ulong i, hfloat &c);          // c = a+i
void sub(const hfloat &a, const hfloat &b, hfloat &c, ulong cp=0);  // c = a-b
void sub(const hfloat &a, long i, hfloat &c);           // c = a-i
void sub(const hfloat &a, ulong i, hfloat &c);          // c = a-i
void sub(long i, const hfloat &a, hfloat &c);           // c = i-a
int addsub(const hfloat &a, const hfloat &b, hfloat &c, int subq, ulong cp=0);  // aux


// ----------------------------------------------
// hf/funcsmul.cc:
void sqr(const hfloat &a, hfloat &c);                          // c = a^2
void sqr(const hfloat &a, ulong ap, hfloat &c, ulong cp);      // c = a^2
void mul(const hfloat &a, const hfloat &b, hfloat &c);         // c = a*b
void mul(const hfloat &a, ulong ap, const hfloat &b, ulong bp, hfloat &c, ulong cp); // c = a*b
void mul(const hfloat &a, long i, hfloat &c);                  // c = a*i
void mul(const hfloat &a, ulong i, hfloat &c);                 // c = a*i
void mul_by_radix_pow(const hfloat &x, long ex, hfloat &c);    // c = x*radix^ex


// ----------------------------------------------
// hf/funcsdiv.cc:
void inv(const hfloat &a, hfloat &c);                 // c = 1/a
void inv(long i, hfloat &c);                          // c = 1/i
void inv(ulong i, hfloat &c);                         // c = 1/i
void div(const hfloat &a, const hfloat &b, hfloat &c);// c = a/b
void div(const hfloat &a, long i, hfloat &c, long *rem=0);          // c = a/i, rem = a%i
void div(const hfloat &a, ulong i, hfloat &c, ulong *rem=0);        // c = a/i, rem = a%i
void fmod(const hfloat &a, const hfloat &b, hfloat &c);             // c = a%b
void fmod(const hfloat &a, const hfloat &b, hfloat &c, hfloat &d);  // c = a/b, d = a%b
void div_by_radix_pow(const hfloat &x, int ex, hfloat &a);          // c = x*radix^(-ex)


// ----------------------------------------------
// hf/funcspow.cc:
void pow(const hfloat &a, long x, hfloat &c);         // c = a^x, x in Z
void pow_geq_3(const hfloat &a, ulong x, hfloat &c);  // c = a^x, x>=+3


// ----------------------------------------------
// hf/funcsrt.cc:
void sqrt(const hfloat &d, hfloat &c);            // c = d^(1/2)
void sqrt(long i, hfloat &c);                     // c = i^(1/2)
void isqrt(const hfloat &d, hfloat &c);           // c = d^(-1/2)
void isqrt(long i, hfloat &c);                    // c = i^(1/2)
void root(const hfloat &d, long r, hfloat &c);    // c = d^(1/r), r in Z
void root(long i, long r, hfloat &c);             // c = i^(1/r), r in Z
void iroot(const hfloat &d, ulong r, hfloat &c);  // c = d^(-1/r), r in N
void iroot(long i, ulong r, hfloat &c);           // c = i^(-1/r), r in N
void cbrt(const hfloat &d, hfloat &c);            // c = d^(1/3)
void cbrt(long i, hfloat &c);                     // c = i^(1/3)
void root_x(const hfloat &d, ulong r, hfloat &c); // c = d^(1/r), r in N
void root_x(long i, ulong r, hfloat &c);          // c = i^(1/r), r in N
void rootn(const hfloat &d, long r, hfloat &c);   // c = d^(1/r), r in Z


// ----------------------------------------------
// hf/ round.cc:
int integerq(const hfloat &a);          // ? a = floor(a)
int round(const hfloat &a, hfloat &b);  // b = floor(a+0.5)
int round0(const hfloat &a, hfloat &b); // round towards zero

// hf/frac.cc:
int floor(const hfloat &a, hfloat &b);  // b = floor(a)
int frac(const hfloat &a, hfloat &b);   // b = a-floor(a)
int frac0(const hfloat &a, hfloat &b);  // b = a-round0(a)



// ----------------------------------------------
// hf/contfrac.cc:

// cf[0..n-1]= n terms of the  simple continued fraction of x:
int hfloat_to_contfrac(const hfloat &x, ulong n, long cf[]);

// ratio from first n terms of continued fraction cf[]:
int contfrac_to_ratio(const long cf[], ulong n, hfloat &p, hfloat &q);

// x= n-th partial fraction of the simple continued fraction cf[]:
int contfrac_to_hfloat(const long cf[], ulong n, hfloat &x);


// ----------------------------------------------
// hf/funcs2pow.cc:
void ldexp(const hfloat &x, long ex, hfloat &a);   // a = x*(2^ex)
void mul2(const hfloat &x, hfloat &a);             // a = x*2
void mul2pow(const hfloat &x, long ex, hfloat &a); // a = x*(2^ex)
void div2(const hfloat &x, hfloat &a);             // a = x/2
void div2pow(const hfloat &x, long ex, hfloat &a); // a = x/(2^ex)


// ----------------------------------------------
// hf/mulpow.cc:
void mulpow(const hfloat &x, long b, long ex, hfloat &a); // a = x*(b^ex)


// ----------------------------------------------
// hf/ratpoly.cc:

// p = \sum_{k=0}^{deg}{num[k]/den[k]*x^k}:
void ratpoly(const hfloat &x, ulong deg, const long *num, const long *den, hfloat &p);

// dnmu[], dden[] = coefficients of derived poly with coefficients num[]/den[]
void ratpoly_derive(ulong deg, const long *num, const long *den, long *dnum, long *dden);

void print_ratpoly(const char *bla, ulong deg, const long *num, const long *den);


// ----------------------------------------------
// hf/sumalt.cc:

// s = \sum_{k=0}^{\infty}{termfct(k)}:
void sumalt( void (*termfct)(ulong, long &, ulong &), hfloat &s, ulong nn=0);

// examples for termfct():

// for arctan(1) = \sum_{k=0}^{\infty}{(-1)^k*1/(2*k+1)}
void gregory_term(ulong k, long &num, ulong &den);

// for catalan = \sum_{k=0}^{\infty}{(-1)^k*1/(2*k+1)^2}
void catalan_term(ulong k, long &num, ulong &den);

// for log(2) = \sum_{k=0}^{\infty}{(-1)^k*1/(k+1)}
void log2_term(ulong k, long &num, ulong &den);

void sum_partial( void (*termfct)(ulong, long &, ulong &), hfloat *p, ulong n); // aux
// compute the sumalt-estimate for a sum whose nn first partial sums are given in p[]:
void sumalt_partial(hfloat *p, hfloat &s, ulong nn);


// ----------------------------------------------
// tz/zeta3.cc:
int zeta3(hfloat &z3);  // t=zeta(3)

// ----------------------------------------------
// tz/log.cc:
void log(const hfloat &a, const hfloat &b, hfloat &c); // c = log_b(a)
void log(const hfloat &a, hfloat &b);              // b = log(a)
int  log_agm(const hfloat &a, hfloat &z);  // z = log(a),  0.5<=a<=1.5

// ----------------------------------------------
// tz/funcstrz.cc:
void acosh(const hfloat &a, hfloat &b);            // b = acosh(a)
void asinh(const hfloat &a, hfloat &b);            // b = asinh(a)
void exp(const hfloat &a, hfloat &b);              // b = exp(a)
void cosh(const hfloat &a, hfloat &b);             // b = cosh(a)
void sinh(const hfloat &a, hfloat &b);             // b = sinh(a)

// ----------------------------------------------
// tz/mean.cc:

// x = arithmetic_geometric_mean(a,b):
int agm(const hfloat &a, const hfloat &b, hfloat &x);  // x=agm(a,b)
int agm1(const hfloat &b, hfloat &x);                  // x=agm(1,b)

// x = harmonic_geometric_mean(a,b):
int hgm(const hfloat &a, const hfloat &b, hfloat &x);

// x = j_mean(a,b):
int j_mean(const hfloat &a, const hfloat &b, hfloat &x);

// ----------------------------------------------
// tz/power.cc:

void   pow(const hfloat &a, const hfloat &ex, hfloat &t);  //  t = a^ex


// ==============================================
// semi internal stuff, might be occasionally useful:

// tz/hfconst.cc:
const hfloat & constant_pi(ulong n);     // pi
const hfloat & constant_logrx(ulong n);  // log(radix)
const hfloat & constant_sqrt2(ulong n);  // sqrt(2)
const hfloat & constant_logsqrt2(ulong n); // log(sqrt(2))

// pi/piagmsch.cc:
int pi_agm_sch(hfloat &p);

// pi/pi4th.cc:
int pi_4th_order(hfloat &pi, int var=0);

// pi/pi5th.cc:
int pi_5th_order(hfloat &pi);

// pi/piagm.cc:
int pi_agm(hfloat &pi, int var=0);

// pi/piagm3.cc:
int pi_agm3(hfloat &pi, int var=4);

// pi/pi2nd.cc:
int pi_2nd_order(hfloat &p);

// pi/pideriv.cc:
int pi_derived_agm(hfloat &pi);

// pi/piarctan.cc:
int pi_arctan(hfloat &pi, int fno);

// pi/pi3rd.cc:
int pi_3rd_order(hfloat &p);

// pi/pi9th.cc:
int pi_9th_order(hfloat &p);

// pi/picubagm.cc:
int pi_cubic_agm(hfloat &p);

// tz/elliptic-k.cc:
void elliptic_K(const hfloat &k, hfloat &K, int pq=0);

// tz/elliptic-e.cc:
void elliptic_E(const hfloat &k, hfloat &E, int pq=0);


// ==============================================
// internal stuff:

// hf/itiroot.cc:
int iroot_iteration(const hfloat &d, ulong r, hfloat &x, ulong stpr=0); // x = d^(-1/r)
void approx_invpow(const hfloat &d, hfloat &x, long p);  // x = d^(1/p) to double prec.

// hf/itsqrt.cc:
int sqrt_iteration(const hfloat &d, hfloat &x);  // x = sqrt(d)

// hf/itinverse.cc:
int inv_iteration(const hfloat &d, hfloat &x, ulong stpr=0);  // x = 1/d


// pi/rprime.cc:
int r_prime_sum(const hfloat &b0, hfloat &s, ulong nn, hfloat *m=0, int sum0q=0);

// pi/rprime4th.cc:
int r_prime_sum_4th(const hfloat &b0, hfloat &s, ulong nn, hfloat *m=0);


// tz/pilogq.cc:
void theta2_invrx4(hfloat &th2);  // theta_2(1/radix^4)
void theta3_invrx4(hfloat &th3);  // theta_3(1/radix^4)
void pi_by_log_rx(ulong n, hfloat &x); // x = pi/log(radix)

// tz/itexp.cc:
int exp_iteration(const hfloat &x, hfloat &b, ulong stpr=0);  // b = exp(x)
void approx_exp(const hfloat &d, hfloat &x);  // x = exp(d) to double prec.


#endif // !defined HAVE_HFLOATFU_H__
