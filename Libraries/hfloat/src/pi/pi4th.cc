
#include "hfloat.h"
#include "hfverbosity.h"

#include <cmath>
#include <fxt/fxtio.h>


// see borwein^2 p.171:
#define LOG_PREC_R(k,r)  -(log(16.0*sqrt(r))+k*log(4.0)-pow(4.0,k)*sqrt(r)*M_PI)
#define LOG_PREC(k)  LOG_PREC_R((double)(k),(double)r)

#define LIMB_PREC(k)  (long)floor(LOG_PREC(k)/log(drx))  // precision in LIMBS
#define DEC_PREC(k)   floor(LOG_PREC(k)/log(10.))        // precision in decimal digits
#define BYTE_PREC(k)  floor(LOG_PREC(k)/log(255.))       // binary precision in bytes


int
pi_4th_order(hfloat &p, int var/*=0*/)
//
// quartic iteration for pi
// var !=0 chooses r=16 variant (default is r=4)
//
// return number of iterations needed
{
    int r;
    if ( var==0 )  r = 4;
    else           r = 16;

    if ( hfverbosity::piname )
    {
        cout << "\n ===== PI_algorithm: " << __FUNCTION__;
        cout << "(" << "r=" << r << " variant)" << endl;
    }

    long n = p.prec();
    long pnp = hfverbosity::pinumprec;
    double drx;
    hfloat y(n);
    hfloat a(n);
    hfloat z(n);

    drx = (double)a.radix();

    if ( r==4 )
    {
	sqrt(2,a);                   // sqrt(2)
	sub(a,(ulong)1,y);           // y_0 = sqrt(2)-1

	mul2pow(y,2,p);              // 4*sqrt(2)-4
	sub(p,(ulong)2,a);           // 4*sqrt(2)-6
	a.negate();                  // a_0 = 6-4*sqrt(2)
    }
    else
    {
        iroot(2,4,a);                // 1/sqrt(sqrt(2))
	z = a;                       // 1/sqrt(sqrt(2))
	z += 1;                      // 1/sqrt(sqrt(2))+1
	inv(z,p);                    // 1/(1/sqrt(sqrt(2))+1)
	sub((ulong)1,a,y);           // 1-1/sqrt(sqrt(2))
	y *= p;                      // y_0 = (1-1/sqrt(sqrt(2)))/(1/sqrt(sqrt(2))+1)

	pow(p,4,p);                  // 1/(1/sqrt(sqrt(2))+1)^4
	sqr(a,a);                    // 1/sqrt(2)
	a *= 8;                      // 8/sqrt(2)
	a -= 2;                      // 8/sqrt(2)-2
	a *= p;                      // a_0 = (8/sqrt(2)-2)/(1/sqrt(sqrt(2))+1)^4
    }
    if ( hfverbosity::pinums )  print("\nY_0=\n",y,pnp);
    if ( hfverbosity::pinums )  print("\nA_0=\n",a,pnp);


    int k;
    for (k=1;  ; ++k)
    {
        if ( hfverbosity::pistep )
            cout << "\n ----- step " << k << ": ----- " << endl;

	// Y_k:
	sqr(y,y);                        // y^2
	sqr(y,y);                        // y^4
	sub(1,y,y);                      // (1-y^4)

	z = 1;                           // inv root --> 1.0000000000
        ulong stpr = LIMB_PREC(k-1);     // startprec for iroot_iteration
	iroot_iteration(y, 4, z, stpr);  // (1-y^4)^(-1/4)
	sub(z,(ulong)1,y);               // (1-y^4)^(-1/4)-1
	add(y,(ulong)2,p);               // (1-y^4)^(-1/4)+1
	z = 1;
	z /= 2;                          // inv --> .49999999999999
	iroot_iteration(p, 1, z, stpr);  // 1/(y^(-1/4)+1)
//	inv_iteration(p, z, stpr);       // 1/(y^(-1/4)+1)
	y *= z;                          // new y=(y^(-1/4)-1)/(y^(-1/4)+1)
        if ( hfverbosity::pinums )  print("\nY_k=\n",y,pnp);

	// A_k:
	add(y,(ulong)1,p);                // y+1
	sqr(p,z);                         // (y+1)^2
	sqr(z,p);                         // (y+1)^4
	mul(p,a,a);                       // a*(y+1)^4
	sub(z,y,z);                       // (y^2+y+1)
	mul(z,y,z);                       // y*(y^2+y+1)

	if ( r==4 )
	{
	    mul2pow(z, 2*(k-1)+3, z);    // y*(y^2+y+1)*2^(2*(k-1)+3)
	}
	else
	{
	    mul2pow(z, 2*(k-1)+4, z);    // y*(y^2+y+1)*2^(2*(k-1)+4)
	}

	a -= z;                          // new a=a*(y+1)^4-2^(2*k+3)*y*(y^2+y+1)
        if ( hfverbosity::pinums )  print("\nA_k=\n",a,pnp);

        long prec = LIMB_PREC(k);
        if ( hfverbosity::piprec )  cout << "\n precision=" << prec << endl;
	if( prec>=n )  break;
    }

    inv(a,p);         // ! pi !

    return k;
}
//========================== end PI_4TH_ORDER ==========================



/*
main() {
for(int k=0; k<25; ++k)
    cout.form("\n %18.18g %02d  %18.18g %02d",DEC_PREC(k),k,BYTE_PREC(k),k);
cout<<"\n\n";}

// this is for r=4:
       dec digits   #iter        bytes     #iter
-----------------------------------------------
                  1 00                   0 00
                  8 01                   3 01
                 40 02                  17 02
                171 03                  71 03
                694 04                 288 04

               2789 05                1159 05
              11171 06                4642 06
              44702 07               18575 07
             178825 08               74308 08
             715319 09              297239 09

            2861297 10             1188967 10
           11445210 11             4755877 11
           45780864 12            19023519 12
          183123485 13            76094089 13
          732493967 14           304376371 14

         2929975899 15          1217505497 15
        11719903627 16          4870022001 16
        46879614541 17         19480088021 17
       187518458201 18         77920352099 18
       750073832842 19        311681408414 19

      3000295331409 20       1246725633672 20
     12001181325679 21       4986902534706 21
     48004725302760 22      19947610138844 22
    192018901211085 23      79790440555395 23
    768075604844388 24     319161762221599 24


// this is for r=16:
       dec digits   #iter        bytes     #iter
-----------------------------------------------
                  3 00                   1 00
                 19 01                   8 01
                 84 02                  35 02
                345 03                 143 03

               1392 04                 578 04
               5583 05                2320 05
              22348 06                9286 06
              89409 07               37152 07
             357656 08              148618 08

            1430645 09              594482 09
            5722601 10             2377937 10
           22890428 11             9511758 11
           91561738 12            38047043 12
          366246979 13           152188183 13

         1464987944 14           608752746 14
         5859951808 15          2435010998 15
        23439807265 16          9740044008 16
        93759229094 17         38960176047 17
       375036916415 18        155840704204 18

      1500147665698 19        623362816833 19
      6000590662833 20       2493451267350 20
     24002362651373 21       9973805069419 21
     96009450605535 22      39895220277694 22
    384037802422186 23     159580881110796 23
   1536151209688791 24     638323524443206 24

*/
