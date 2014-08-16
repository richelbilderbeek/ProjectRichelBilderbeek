#if !defined HAVE_WORKSPACE_H__
#define      HAVE_WORKSPACE_H__

#include "fxttypes.h"


class  workspace_init
{
public:
    workspace_init();
    ~workspace_init();  // "workspace_exit()"
};
// -------------------------


class workspace
// Auxiliary class for FFT multiplication algorithms
{
public:
    static void  grow(ulong n);

    static void get_ws(char *&, ulong n);
    static void get_ws(LIMB *&, ulong n);
    static void get_ws(double *&, ulong n);
    static void get_noswap_ws(char *&, ulong n);
    static void get_noswap_ws(LIMB *&, ulong n);
    static void get_noswap_ws(double *&, ulong n);
    static void let_ws();

    static ulong nbytes()    { return nbytes_; }
    static ulong ndoubles()  { return ndoubles_; }

    static ulong noswap_bytes()    { return noswap_bytes_; }
    static ulong cache_bytes()     { return cache_bytes_; }

    static ulong noswap_doubles()  { return noswap_doubles_; }
    static ulong cache_doubles()   { return cache_doubles_; }

    static void print_info();

    static const ulong extra_doubles_;  // pad space to avoid cache problems

private:
    static double *ptr_;           // pointer to whole workspace
    static int    inuse_;          // whether workspace is in use

    static ulong *sentinel_;       // for debug
    static ulong sentinel_val_;    // for debug

    static ulong nbytes_;          // size in bytes
    static ulong ndoubles_;        // size in doubles

    static ulong noswap_bytes_;    // max noswap size in bytes
    static ulong cache_bytes_;     // max cache size in bytes

    static ulong noswap_doubles_;  // max noswap size in doubles
    static ulong cache_doubles_;   // max cache size in doubles

    // magic initialiser:
    friend class workspace_init;
    static workspace_init workspace_initializer;

public:
    static const char * const classname;
};
// -------------------------


#endif // !define HAVE_WORKSPACE_H__
