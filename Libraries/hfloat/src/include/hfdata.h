#if !defined HAVE_HFDATA_H__
#define      HAVE_HFDATA_H__


#include "types.h"     // says LIMB:=unsigned short


class hfdata
{
public:
    explicit hfdata(ulong n);

    ~hfdata();

public:
    void  copy(const hfdata &);


    LIMB *dig() const  { return limbs_; }

    ulong size() const  { return size_; }
    void  size(ulong);

    ulong prec() const  { return prec_; }
    void  prec(ulong);

    void  rand(ulong n1, ulong n2);

    void  dump(const char *bla=0, ulong n=0) const;
    int   check() const;
    int   OK() const  { return !check(); }

    static ulong radix()  { return rx; }
    static void  radix(ulong r, const char *rfmt=0);

    static void  print_statistics(ulong n);

private:
    hfdata(const hfdata &);               // forbidden (undefined)
    hfdata & operator =(const hfdata &);  // forbidden (undefined)


    // ---- implementation:
private:
    LIMB   *limbs_;      // the digit field
    ulong   size_;       // number of LIMBs
    ulong   prec_;       // computation precision (in LIMBs)

public:
    // radix stuff:
    static ulong    rx;         // radix (same for all)

    static const char  *  rxfmt;      // print format
    static ulong    rxbase;     // rx=rxbase^rxbspw
    static ulong    rxbspw;     //

    static ulong    ldrx;       // ld(rx)
    static ulong    rxbits;     // ld(rx)[+1]
    static double   lg10rx;     // log10(rx)
    static bool     rx2pw;      // whether radix is a power of two

    // global statistics:
    static ulong   nbytes;      // total bytes allocated
    static ulong   nbytesmax;   // max total bytes allocated
    static long    ndata;       // total number of hfdata

    // convolution methods:
    // convolution procedure used for multiplication:
    static void    (* mulcnvl)(double *,double *,ulong);
     // (auto-)convolution procedure used for squaring:
    static void    (* sqrcnvl)(double *,ulong);
};
//-------------------------------------------------------------

// functions are declared in hfdata.h

#endif // !defined HAVE_HFDATA_H__
