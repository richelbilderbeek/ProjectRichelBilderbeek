
#include "hfloat.h"
#include "hfverbosity.h"
#include "hfdatafu.h"

#include "fxtmult.h"  // class fxtmult


//#define  NDEBUG
#include <fxt/jjassert.h>


#define  VERBINIT  0  // 0 ro 1, default is 0

#if ( VERBINIT==1 )
#warning 'FYI: verbose hfloat initialiser'
#include <fxt/fxtio.h>
#endif

bool hfloat_init::init_done = false;

hfloat_init::hfloat_init(LIMB rx,
                         ulong defprec,
                         int check_mul,
                         int check_roots)
{
#if ( VERBINIT==1 )
    cout << endl;
    cout << "******* " << __PRETTY_FUNCTION__ << " *******" << endl;
#endif

    jjassert( init_done==false );
    init_done = true;

    hfloat::hello();

    // radix:
    hfloat::radix(rx);

    // default precision:
    hfloat::default_prec(defprec);

    hfloat::longlimbs = 64;

    // whether to check multiplies via sum of digit:
    fxtmult::checkmult = check_mul;

    // whether to check that the last step in iteration really
    // produced (almost) a full precision result.
    // this decreases performance by about 30%
    hfloat::check_itiroot_result = check_roots;

    hfverbosity::tell_pi();  // echo pi related stuff
//    hfverbosity::tell_all();  // do echo operations
//    hfverbosity::hush_all();  // do not echo any operations
}
//----------- end ------------


hfloat_init::~hfloat_init()  // 'hfloat_exit()'
{
#if ( VERBINIT==1 )
    cout << endl;
    cout << __PRETTY_FUNCTION__ << endl;
#endif
}
//----------- end -------------

