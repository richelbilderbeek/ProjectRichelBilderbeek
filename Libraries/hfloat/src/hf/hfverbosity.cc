
#include "hfverbosity.h"

#include "fxtmult.h"

#include <fxt/fxtio.h>


const char *hfverbosity::add = NULL;
const char *hfverbosity::sub = NULL;

const char *hfverbosity::mulint = NULL;
const char *hfverbosity::sqr = NULL;
const char *hfverbosity::mul = NULL;

const char *hfverbosity::powbegin = NULL;
const char *hfverbosity::powend = NULL;

int   hfverbosity::itbegin = 0;
int   hfverbosity::itprec = 0;

int   hfverbosity::meanname = 0;
int   hfverbosity::meannums = 0;
int   hfverbosity::meanprec = 10;

int   hfverbosity::piname = 0;
int   hfverbosity::pistep = 0;
int   hfverbosity::piprec = 0;
int   hfverbosity::pinums = 0;
int   hfverbosity::pimorenums = 0;
long  hfverbosity::pinumprec = 10;

// these are for debugging:
int   hfverbosity::printhfcd = 0;
int   hfverbosity::printdtcd = 0;
int   hfverbosity::printresize = 0;
int   hfverbosity::printcopy = 0;


void
hfverbosity::say(const char *v)
{
    if ( v )
    {
        cout << v;
        cout.flush();
    }
}
//--------------


void
hfverbosity::tell_arith()
{
    add = "+";
    sub = "-";

    mulint = "m";
    sqr = "S";
    mul = "M";

    powbegin = "P[";
    powend = "]";

    itbegin = 1;
    itprec = 1;
}
//--------------


void
hfverbosity::tell_pi()
{
    piname = 1;
    pistep = 1;
    piprec = 1;
    pinums = 1;
    pimorenums = 1;
}
//--------------


void
hfverbosity::tell_mean()
{
    meanname = 1;
    meannums = 1;
}
//--------------


void
hfverbosity::tell_all()
{
    tell_arith();
    tell_mean();
    tell_pi();
}
//--------------


void
hfverbosity::tell_fxtmult()
{
    fxtmult::verbosity = 1;
}
//--------------



void
hfverbosity::hush_arith()
{
    add = NULL;
    sub = NULL;
    mulint = NULL;
    mul = NULL;
    sqr = NULL;
    powbegin = NULL;
    powend = NULL;
    itbegin = 0;
    itprec = 0;
}
//--------------


void
hfverbosity::hush_pi()
{
    piname = 0;
    pistep = 0;
    piprec = 0;
    pinums = 0;
    pimorenums = 0;
}
//--------------


void
hfverbosity::hush_mean()
{
    meanname = 0;
    meannums = 0;
}
//--------------

void
hfverbosity::hush_all()
{
    hush_arith();
    hush_mean();
    hush_pi();
    hush_fxtmult();
}
//--------------


void
hfverbosity::hush_fxtmult()
{
    fxtmult::verbosity = 0;
}
//--------------

