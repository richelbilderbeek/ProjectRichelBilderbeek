//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitRandom.h"
//---------------------------------------------------------------------------
long int rnd::idum;
int rnd::MBIG  = 1000000000;
int rnd::MSEED = 161803398;
int rnd::MZ = 0;
double rnd::FAC = (1.0/MBIG);

#pragma package(smart_init)

