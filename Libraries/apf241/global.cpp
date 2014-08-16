#include "ap.h"


// Global variables

// Call apinit () to initialize these to appropriate values

size_t Ramsize = 16777216;
size_t CacheL1size = 8192;
size_t CacheL2size = 262144;
size_t Cacheburst = 32;
size_t Cachetreshold = 65536;
size_t Cacheburstblocksize = 8;
size_t Cachemaxblocksize = 1024;
size_t Cacheblocksize = 32;
size_t Maxblocksize = 1048576;
size_t Memorytreshold = 16384;
size_t Blocksize = 16384;
size_t NProcessors = 1;

rawtype Base = BASE;
rawtype Basedigit = BASEDIGIT;
int Basedigits = BASEDIGITS;
rawtype Basefactors[16] = {BASEFACTORS[0], BASEFACTORS[1]};     // All prime factors of Base
int NBasefactors = NBASEFACTORS;                                // Number of prime factors of Base


// For scratch filenames
int fno = 0;


// Common workspace
rawtype *workspace = 0;
int workspaceused = 0;


// Must have these declared in order to use them from elsewhere

rawtype modint::modulus;
bool apfloat::prettyprint = false;


// Some good precalculated values from raw.h

rawtype moduli[3] = {MODULI[0], MODULI[1], MODULI[2]};
rawtype primitiveroots[3] = {PRIMITIVEROOTS[0], PRIMITIVEROOTS[1], PRIMITIVEROOTS[2]};
rawtype wftamoduli[3] = {WFTAMODULI[0], WFTAMODULI[1], WFTAMODULI[2]};
rawtype wftaprimitiveroots[3] = {WFTAPRIMITIVEROOTS[0], WFTAPRIMITIVEROOTS[1], WFTAPRIMITIVEROOTS[2]};
