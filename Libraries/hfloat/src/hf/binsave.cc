

#include <fxt/fxttypes.h>
#include <fxt/jjassert.h>

#include "hfloat.h"
#include "hfdata.h"


#include <fxt/fxtio.h>

#include <fstream>
#include <cmath>


// for debug:
#define PR(x)

int
binsave_limbs(const char *fname, const hfloat &a, long n, long s)  //=0, =0
//
// return: 0 ==ok
//         -1==fail
//
{
    PR( long bfsz; );
    LIMB *ad;
    int bufct;
    const int buflen=4096;
    uchar buf[4096];
    const char *sbuf = (const char *)buf;

    std::fstream file;
    file.open(fname, ios::out | ios::binary | ios::trunc);
    jjassert( file.good() );


    if( (0==n) || (n>(long)a.prec()) )  n=(long)a.prec();
    if( n<0 )  n=(long)a.prec()+n;
    if( s<0 )  s=(long)a.prec()+s;

    if( (s>n) || (n>(long)a.prec()) )
    {
        cerr<< "\n binsave_limbs(): meaningless s,n - combination "<<endl;
        return -2;
    }

    ad = a.data()->dig();


    if( hfdata::rx2pw )  // radix is a power of 2
    {
         const uchar left_bit=0x80;
         long k=s;
         uint mr,ak;
         uchar mw, t;


         mr = (uint)(hfdata::rx>>1);       // bit read mask
         ak=ad[k];
         mw=left_bit;              // bit write mask
         t=0;
	 bufct=0;

         while(1)
	 {
             if ( mr & ak )  t |= mw;

             mw = (uchar)(mw >> 1);
             if ( mw==0 )
             {
		 buf[bufct]=t;
		 bufct++;

	         if ( bufct==buflen )
		 {
		     file.write(sbuf, buflen);
		     jjassert( file.good() ); // " write "
		     bufct=0;
		 }

		 t=0;
		 mw=left_bit;
	     }

             mr >>= 1;
             if ( mr==0 )
             {
                k++;
                if ( k==n )
		{
                    if ( mw!=left_bit )
		    {
		        buf[bufct]=t;
			bufct++;
			file.write(sbuf, bufct);
			jjassert( file.good() ); // " write "
			bufct=0;
		    }

		    goto thatsit;
		}

                ak = ad[k];
                mr = (uint)(hfdata::rx>>1);
	     }
	 }

       thatsit:

	 if(bufct)
	 {
	     file.write(sbuf, bufct);
	     jjassert( file.good() ); // " write "
	 }

	 PR( bfsz=hfdata::rxbits*n/8; );
    }
    else  // RADIX not a pow of 2
    {
        file.write( (const char*)(ad+s), sizeof(LIMB)*(n-s));
	jjassert( file.good() ); // " write "
	PR( bfsz=sizeof(LIMB)*n; );
    }



    PR( cout<<"\n binfile-size should be "<< bfsz <<" bytes "; );

    jjassert( file.good() );  // " end "

    file.close();
    if( !file.good() )
    {
        cerr<< "\n binsave(): close FAILED ! "<<endl;
	return -1;
    }

    return 0;
}
//================== end BINSAVE_LIMBS =============================
