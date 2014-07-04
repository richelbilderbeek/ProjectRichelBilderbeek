#if !defined HAVE_HFVERBOSITY_H__
#define      HAVE_HFVERBOSITY_H__

class hfverbosity
{
public:
    static void say(const char *);

    static const char *sqr;
    static const char *mul;

    static const char *mulint;

    static const char *add;
    static const char *sub;

    static const char *powbegin;
    static const char *powend;

    static int   itbegin;
    static int   itprec;

    static int   meanname;
    static int   meannums;
    static int   meanprec;

    static int   piname;
    static int   pistep;
    static int   piprec;
    static int   pinums;
    static int   pimorenums;
    static long  pinumprec;

    static void hush_arith();
    static void hush_mean();
    static void hush_pi();
    static void hush_all();
    static void hush_fxtmult();

    static void tell_arith();
    static void tell_mean();
    static void tell_pi();
    static void tell_all();
    static void tell_fxtmult();

    // for debug:
    static int printhfcd;    // verbose constr. and destr.
    static int printdtcd;    // verbose constr. and destr.

    static int printresize;    // verbose resize

    static int printcopy;    // verbose copy funcs.
};
//-------------------------------------------------------------


#endif // !defined HAVE_HFVERBOSITY_H__
