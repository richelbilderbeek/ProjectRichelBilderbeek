#if !defined HAVE_HFLOAT_H__
#define      HAVE_HFLOAT_H__


#include "hfdata.h"
#include "types.h"


// the class 'hfloat_init' has the sole purpose
// of initialising the class 'hfloat'
// this is done with the static member 'hfloat_initialiser'
// of class 'hfloat'
class  hfloat_init
{
public:
    hfloat_init(LIMB rx, ulong defprec,
                int checkmul, int checkroots);

    ~hfloat_init();  // "hfloat_exit()"

    static bool init_done;
};
//--------------------------


class  hfloat // "_huge_float_"
{
public:
    explicit hfloat(ulong prec=defaultprec);
    hfloat(const hfloat &);
    ~hfloat();

    hfdata * data() const  { return dt; }

    hfloat& operator =(int);
    hfloat& operator =(long);
    hfloat& operator =(ulong);
    hfloat& operator =(double);
    hfloat& operator =(const hfloat &);
    hfloat& operator =(const char *);

//    operator long() const;
//    operator double() const;

    void    copy(const hfloat &);

    int     id() const  { return hfid; }

    void    size(ulong n)  { data()->size(n); }
    ulong   size() const   { return data()->size(); }

    void    prec(ulong p, int rr=0);
    ulong   prec() const  { return dt->prec(); }

    int     positive() const  { return sg > 0; }
    int     negative() const  { return sg < 0; }
    int     is_zero() const   { return 0==sg; }
    void    set_zero()        { sg = 0; }
    void    negate()          { sg = -sg; }
    int     sign() const      { return sg; }
    void    sign(int s)       { sg = s; }

    long    exp() const  { return (long)ex; }
    void    exp(long x);

    LIMB    get_limb(ulong) const;
    void    set_limb(ulong,LIMB);
    LIMB    get_limb_rtd(long) const;  // get limb relative to dot

    int     odd() const;
    int     even() const;

//    int     get_bit(ulong n) const;
//    int     get_bit_rtd(long n) const;  // get bit relative to dot

    int      normalized() const;
    void     normalize();

    void     rand01();

    void     dump(const char *, long) const;
    int      check() const;
    int      OK() const  { return !check(); }

private:
    // ---- implementation:
    const int hfid;           // unique identity number !=0  id()
    hfdata   *dt;          // the mantissa

    long      ex;          // exponent
    int       sg;          // sign   +1=pos, -1=neg, 0=zero

    static double  overflow;   // biggest exponent  ( -> +- infinity )
    static double  underflow;  // smallest exponent ( -> 0 )


public:
    static int forbid_unnormalized;
    // whether to check iteration for nth root:
    static int    check_itiroot_result;

    static void   hello();

    static ulong  default_prec()  { return defaultprec; }
    static void   default_prec(ulong n);

    // currently same radix for all hfloats:
    static ulong  radix()         { return hfdata::radix(); }
    static void   radix(ulong r)  { hfdata::radix(r); }

    static const char * version()  { return version_string; }

    // max # of LIMBs to contain a (long) integer or double:
    static ulong  longlimbs;

    static void print_info();

    // constants used for calculations:
    static hfloat *const_pi;
    static hfloat *const_logrx;
    static hfloat *const_sqrt2;
    static hfloat *const_logsqrt2;

private:
    static const char * version_string;     // string like "05-june-2001"
    static ulong defaultprec;

    // magic initialiser:
    friend class hfloat_init;
    static hfloat_init hfloat_initialiser;
};
//------ end class hfloat -----------------------------------

// functions:
#include "hfloatfu.h"

// operators:
#include "hfloatop.h"

// hf/hfloat.cc:
double prec_convert(ulong p, ulong rx2, ulong rx1=0);

#endif // !defined HAVE_HFLOAT_H__
