#if !defined HAVE_HFDATAFU_H__
#define      HAVE_HFDATAFU_H__


#include "hfdata.h"    // class hfdata


// dtconvint.cc:
ulong dt_int_to_mantissa(ulong i, hfdata &a);

// dtconvdbl.cc:
ulong dt_mantissa_to_double(const hfdata &a, double &d);
ulong dt_double_to_mantissa(double d, hfdata &a);

// dtcmp.cc:
int dt_cmp(const hfdata &a, const hfdata &b, ulong *idx=0);

// dtadd.cc:
int  dt_add(const hfdata &big, const hfdata &sml, ulong dx, hfdata &c, ulong cp=0);
uint i_add_to(LIMB *rd, ulong rn, ulong dx, const LIMB *ad, ulong an, const uint rx);
uint i_add_to(LIMB *ad, ulong n, const LIMB *bd, const uint rx);
uint i_carry(LIMB *ad, ulong an, uint cy, const uint rx);

// dtsub.cc:
int dt_sub(const hfdata &big, const hfdata &sml, ulong dx, hfdata &c, ulong cp=0);
int i_sub_from(LIMB *rd, ulong rn, ulong dx, const LIMB *ad, ulong an, const uint rx);
int i_sub_from(LIMB *ad, ulong n, const LIMB *bd, const uint rx);
int i_sub_from2(LIMB *ad, ulong n, const LIMB *bd, const uint rx, int cy);
int i_borrow(LIMB *d, ulong n, int cy, const uint rx);
int i_negate(LIMB *rd, ulong rn, const uint rx);

// dtmul.cc:
int dt_mul(const hfdata &a, const hfdata &b, hfdata &c);
int dt_mul(const hfdata &a, ulong ap, const hfdata &b, ulong bp, hfdata &c, ulong cp);
int dt_sqr(const hfdata &a, hfdata &c);
int dt_sqr(const hfdata &a, ulong ap, hfdata &c, ulong cp);

// dtmulsh.cc:
int dt_mul_sh(hfdata &a, ulong b);
int i_mul(const LIMB *ad, ulong an, const LIMB *bd, ulong bn,
          LIMB *cd, ulong cn, const uint rx);

// dtdivsh.cc:
int dt_div_sh(hfdata &a, ulong b, ulong *rem);
int i_div_sh(LIMB *cd, ulong cn, ulong b, const uint rx, ulong *r);
#if defined __GNUC__
#define HAVE_IDIVSEMI
int i_div_semi(LIMB *cd, ulong cn, ulong b, const uint rx, ulong *r);
#endif

// dtldexp.cc:
int dt_mul2(hfdata &a);
int dt_div2(hfdata &a);


#endif // !defined HAVE_HFDATAFU_H__
