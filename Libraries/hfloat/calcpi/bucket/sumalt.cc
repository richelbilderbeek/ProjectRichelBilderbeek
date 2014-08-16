
#include "hfloat.h"

int
main()
{
    const int prec = 256;
    hfloat::default_prec(prec);
    hfloat s;  // less than , say 1024 decimal digits

    sumalt(log2_term, s);  // compute log(2) = 0.69314...
    cout << s << endl;
    return 0;

    sumalt(gregory_term, s);  // compute pi as arctan(1)
    s *= 4;
    cout << s << endl;
//    return 0;

    hfloat p = hfloat();
    p = constant_pi(p.prec());  // use default (iteration)
    s -= p;
    print("small=",s,3);
    cout << endl;
//    return 0;

    sumalt(catalan_term, s);  // compute catalan=0.91596...
    cout << s << endl;

    cout << endl;
    return 0;
}
//---------------
