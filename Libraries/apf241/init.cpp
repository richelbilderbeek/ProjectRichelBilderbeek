#include <cstdlib>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include "ap.h"


// Automatic init stuff

bool apfloatinitialized = false;

class apfloatinit
{
public:
    apfloatinit ()
    {
        int apfloatinitok = apinit ();

        assert (!apfloatinitok);
    };

    ~apfloatinit ()
    {
        apdeinit ();
    };
};

// Constructor is called at program init, destructor at program exit
apfloatinit autoinit;


// Code size in megabytes (approx.)
const size_t CODESIZE = 2;

// The actual workspace buffer, not necessarily aligned to a cache line
rawtype *unalignedworkspace;

size_t rnd2down (size_t x)
{
    size_t r = 1;

    if (!x) return 0;

    while (x >>= 1) r <<= 1;

    return r;
}

size_t rnd23down (size_t x)
{
    size_t r = 1, p;

    if (!x) return 0;

    while (r <= x)
    {
        p = r;
        if (r == 1)
            r = 2;
        else if (r == (r & -r))
            r = r / 2 * 3;
        else
            r = r / 3 * 4;
    }

    return p;
}

size_t sqrt4down (size_t x)
{
    size_t r = 1;

    if (!x) return 0;

    while (x >>= 2) r <<= 1;

    return r;
}

// Inits global variables
bool apinit (void)
{
    using namespace std;

    if (apfloatinitialized) return false;
    apfloatinitialized = true;

    size_t v;
    char *p;
    string str1, str2;
    ifstream fs ("apfloat.ini");

    // RAM size
    // Set this to the size of actual RAM memory you have on your computer.
    // Ramsize = 8 * (1 << 20);
    Ramsize = 16 * (1 << 20);

    // L1 cache size
    // 486's and Pentiums have 8KB (data) L1 cache
    CacheL1size = 8 * (1 << 10);

    // L2 cache size
    // set to amount of L2 cache
    CacheL2size = 256 * (1 << 10);

    // cache burst width
    // 16 bytes for 486, 32 for Pentium
    // Cacheburst = 16;
    Cacheburst = 32;

    // Longer numbers than this will be stored by default to disk
    Memorytreshold = 16384;

    // Efficient read/write block size
    Blocksize = 16384;

    if (!fs.fail ())
    {
        while (!fs.eof ())
        {
            getline (fs, str1);
            if ((v = str1.find ('=')) != 0)
            {
                str2 = str1.substr (v + 1);
                str1 = str1.substr (0, v);
                istringstream s1 (str1);
                s1 >> str1;
                for (v = str1.length (); v--;)
                    str1.at (v) = tolower (str1.at (v));
                istringstream s2 (str2);
                s2 >> v;
                if (str1 == "ramsize") Ramsize = v;
                else if (str1 == "cachel1size") CacheL1size = v;
                else if (str1 == "cachel2size") CacheL2size = v;
                else if (str1 == "cacheburst") Cacheburst = v;
                else if (str1 == "memorytreshold") Memorytreshold = v;
                else if (str1 == "blocksize") Blocksize = v;
                else if (str1 == "nprocessors") NProcessors = v;
            }
        }
    }

    if ((p = getenv ("RAMSIZE")) != 0) { istringstream s (p); s >> Ramsize; }
    if ((p = getenv ("CACHEL1SIZE")) != 0) { istringstream s (p); s >> CacheL1size; }
    if ((p = getenv ("CACHEL2SIZE")) != 0) { istringstream s (p); s >> CacheL2size; }
    if ((p = getenv ("CACHEBURST")) != 0) { istringstream s (p); s >> Cacheburst; }
    if ((p = getenv ("MEMORYTRESHOLD")) != 0) { istringstream s (p); s >> Memorytreshold; }
    if ((p = getenv ("BLOCKSIZE")) != 0) { istringstream s (p); s >> Blocksize; }
    if ((p = getenv ("NPROCESSORS")) != 0) { istringstream s (p); s >> NProcessors; }

    if ((p = getenv ("MAXBLOCKSIZE")) != 0)
    {
        istringstream s (p);
        s >> Maxblocksize;
    }
    else
    {
        Maxblocksize = Ramsize - CODESIZE * (1 << 20);
    }

    // Set to the maximum 2^n or 3*2^n size block of modints that fits in the memory
    Maxblocksize = rnd23down (Maxblocksize / sizeof (modint));

    // Size of matrix that fits in L2 cache
    Cachetreshold = rnd2down (CacheL2size / sizeof (modint));

    // Cache burst in modints
    Cacheburstblocksize = rnd2down (Cacheburst / sizeof (modint));

    // Block size that fits in L1 cache
    Cachemaxblocksize = rnd2down (CacheL1size / sizeof (modint));

    // Transpose block size, fits in processor L1 cache
    Cacheblocksize = sqrt4down (CacheL1size / sizeof (modint));

    if (Blocksize > Memorytreshold)
        Blocksize = Memorytreshold;

    if (Cachemaxblocksize > Memorytreshold)
        Cachemaxblocksize = rnd2down (Memorytreshold);

    if ((unalignedworkspace = new rawtype[Maxblocksize + Cacheburstblocksize - 1]) == 0)
        return true;

    // Memory block aligned at the beginning of a cache line
    workspace = (rawtype *) (((size_t) unalignedworkspace + sizeof (modint) * Cacheburstblocksize - 1) & -(sizeof (modint) * Cacheburstblocksize));

    return false;
}

void apdeinit (void)
{
    if (!apfloatinitialized) return;
    apfloatinitialized = false;

    delete[] unalignedworkspace;
    workspace = 0;

    clearmodulus ();
}

// Set the fpu for doing fpu multiplication.
void setmodulus (rawtype m)
{
    modint::modulus = m;
}

// Clear what setmodulus () did.
// Call in the end of the program.
void clearmodulus (void)
{
}
