#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ap.h"


using namespace std;


#define PROCESS_INFORMATION pid_t

const char FILETOKEN = '_';
const char FILESUFFIX[] = ".dat";
const char DEFCHAR = '1';

// On some systems (e.g. Linux) only one forked child process at a time works
// Four can be utilized at most
// const size_t MAX_FORKED_PROCESSES = 4;
const size_t MAX_FORKED_PROCESSES = 2;

static char *progname;
static char **baseenv;
static bool output;
static size_t prec, totalproc;

const size_t MAXENVVARS = 1024;
const size_t MAXARGS = 10;

typedef struct
{
    PROCESS_INFORMATION procinfo;
    size_t startproc;
    size_t endproc;
} procdata;

// Program for testing the apfloat class, actually calculates pi

void dump (void)
{
    int i;

    cerr << "Ramsize = " << Ramsize << endl;
    cerr << "CacheL1size = " << CacheL1size << endl;
    cerr << "CacheL2size = " << CacheL2size << endl;
    cerr << "Cacheburst = " << Cacheburst << endl;
    cerr << "Maxblocksize = " << Maxblocksize << endl;
    cerr << "Memorytreshold = " << Memorytreshold << endl;
    cerr << "Blocksize = " << Blocksize << endl;
    cerr << "NProcessors = " << NProcessors << endl;
    cerr << "Cachetreshold = " << Cachetreshold << endl;
    cerr << "Cacheburstblocksize = " << Cacheburstblocksize << endl;
    cerr << "Cachemaxblocksize = " << Cachemaxblocksize << endl;
    cerr << "Cacheblocksize = " << Cacheblocksize << endl;
    cerr << "Base = " << setprecision (20) << Base << endl;
    cerr << "Basedigit = " << setprecision (20) << Basedigit << endl;
    cerr << "Basedigits = " << Basedigits << endl;
    cerr << "NBasefactors = " << NBasefactors << endl;
    cerr << "Basefactors = ";

    for (i = 0; i < NBasefactors; i++)
        cerr << Basefactors[i] << (i < NBasefactors - 1 ? ", " : "");

    cerr << endl;
}


// Calculates pi using the binary splitting algorithm of the Chudnovsky brothers

apfloat A, B, J, one, two, five, six, isqrt;
size_t maxk, currk, oldpct = 0;

// Approximates the size (in baseints) of Q when n terms are calculated
// Use Stirling's formula for approximation of n!: for large values of n
// (n/e)^n * sqrt (2*n*pi) < n! < (n/e)^n (1 + 1 / (12*n-1)) sqrt (2*n*pi)
size_t termsize (size_t n)
{
    if (!n)
        return 0;
    else
        return (size_t) ceil (n * (3 * log ((double) n) - 3 + log (10939058860032000.0)) / log ((double) Base));
}

void setfno (size_t startproc, size_t endproc)
{
    // To avoid overwriting disk-based numbers
    // Scaled so that startproc and endproc can be 0, ..., 31
    fno += startproc * 3000000 + endproc * 90000;
}

const char *filename (size_t startproc, size_t endproc, char c = DEFCHAR)
{
    ostringstream s;
    static string f;

    s << startproc << FILETOKEN << endproc << FILETOKEN << c << FILESUFFIX;

    f = s.str ();

    return f.c_str ();
}

size_t availablememory (size_t availableproc)
{
    // Might overflow on 32-bit architectures with large Maxblocksize and availableproc
    // return Maxblocksize * availableproc / totalproc;

    return (size_t) ((double) Maxblocksize * availableproc / totalproc);
}

const char **env (size_t startproc, size_t endproc)
{
    size_t t = 0, i, avproc;
    static string envb[MAXARGS];
    static const char *envs[MAXENVVARS];

    avproc = endproc - startproc + 1;

    { ostringstream s; s << "CACHEL1SIZE=" << CacheL1size; envb[t++] = s.str (); }
    { ostringstream s; s << "CACHEL2SIZE=" << CacheL2size; envb[t++] = s.str (); }
    { ostringstream s; s << "CACHEBURST=" << Cacheburst; envb[t++] = s.str (); }
    { ostringstream s; s << "MEMORYTRESHOLD=" << Memorytreshold; envb[t++] = s.str (); }
    { ostringstream s; s << "BLOCKSIZE=" << Blocksize; envb[t++] = s.str (); }
    { ostringstream s; s << "NPROCESSORS=" << avproc; envb[t++] = s.str (); }
    { ostringstream s; s << "MAXBLOCKSIZE=" << rnd23up (availablememory (avproc) * sizeof (modint)); envb[t++] = s.str (); }

    assert (t < MAXARGS);

    for (i = 0; i < t; i++)
        envs[i] = envb[i].c_str ();

    for (i = 0; baseenv[i] && t < MAXENVVARS; i++)
        if (string (baseenv[i], 12) != "CACHEL1SIZE=" &&
            string (baseenv[i], 12) != "CACHEL2SIZE=" &&
            string (baseenv[i], 11) != "CACHEBURST=" &&
            string (baseenv[i], 15) != "MEMORYTRESHOLD=" &&
            string (baseenv[i], 10) != "BLOCKSIZE=" &&
            string (baseenv[i], 12) != "NPROCESSORS=" &&
            string (baseenv[i], 13) != "MAXBLOCKSIZE=")
        {
            envs[t] = baseenv[i];
            t++;
        }

    assert (t < MAXENVVARS);

    envs[t] = 0;

    return envs;
}

// Nonportable code starts here
void setprocessaffinity (size_t startproc, size_t endproc)
{
    // No actual affinity settings done here, system specific

    // This should be set here, it may be used by the parallel fnt
    NProcessors = endproc - startproc + 1;
}

void startprocess (const char **args, const char **envs, PROCESS_INFORMATION *procinfo)
{
    *procinfo = fork ();                                // Returns child process ID to the parent process

    if (*procinfo == 0)                                 // Returns zero to the child process
    {
        if (envs)                                       // In the child process load new program
            execve (progname, (char* const*) args, (char* const*) envs);
        else
            execv (progname, (char* const*) args);
    }

    assert (*procinfo != -1);                           // The process was started successfully
}

void waitforprocess (PROCESS_INFORMATION *procinfo)
{
    PROCESS_INFORMATION retval;
    int status;

    // If you don't have waitpid () you can use wait () instead if you set
    // MAX_FORKED_PROCESSES = 2 above.
    // Otherwise wait () is not enough since multiple child processes may exist
    // retval = wait (&status);

    // Wait for the created process to terminate
    retval = waitpid (*procinfo, &status, 0);

    assert (*procinfo == retval);                       // The process that terminated was the one we waited for
    assert (!status);                                   // The process terminated without errors
}
// Nonportable code ends here

size_t getnthreads (size_t *threadsleft, size_t *processesleft, size_t *startthread, procdata *proc)
{
    size_t nthreads;

    // Rounds up the number of threads per process left
    nthreads = (*threadsleft + *processesleft - 1) / *processesleft;

    // Take threads for this process
    *threadsleft -= nthreads;
    (*processesleft)--;

    proc->startproc = *startthread;
    proc->endproc = *startthread + nthreads - 1;
    *startthread += nthreads;

    return nthreads;
}

void writenumber (size_t startproc, size_t endproc, apfloat *x, apfloat *y = 0, apfloat *z = 0, char c = DEFCHAR)
{
    x->swapto (filename (startproc, endproc, c));
    if (y) y->swapto (filename (startproc, endproc, c + 1));
    if (z) z->swapto (filename (startproc, endproc, c + 2));
}

inline void writenumber (size_t startproc, size_t endproc, apfloat *x, char c)
{
    writenumber (startproc, endproc, x, 0, 0, c);
}

void readnumber (size_t startproc, size_t endproc, apfloat *x, apfloat *y = 0, apfloat *z = 0, char c = DEFCHAR)
{
    x->swapfrom (filename (startproc, endproc, c));
    if (y) y->swapfrom (filename (startproc, endproc, c + 1));
    if (z) z->swapfrom (filename (startproc, endproc, c + 2));
}

inline void readnumber (size_t startproc, size_t endproc, apfloat *x, char c)
{
    readnumber (startproc, endproc, x, 0, 0, c);
}

void startsubprocess (size_t startproc, size_t endproc, size_t N1, size_t N2, procdata *proc)
{
    size_t t = 0;
    string argb[MAXARGS];
    const char *args[MAXARGS];

    { ostringstream s; s << progname; argb[t++] = s.str (); }
    { ostringstream s; s << "-p"; argb[t++] = s.str (); }
    { ostringstream s; s << prec; argb[t++] = s.str (); }
    { ostringstream s; s << startproc; argb[t++] = s.str (); }
    { ostringstream s; s << endproc; argb[t++] = s.str (); }
    { ostringstream s; s << N1; argb[t++] = s.str (); }
    { ostringstream s; s << N2; argb[t++] = s.str (); }
    { ostringstream s; s << Basedigit; argb[t++] = s.str (); }

    assert (t < MAXARGS);

    args[t] = 0;
    while (t--)
        args[t] = argb[t].c_str ();

    proc->startproc = startproc;
    proc->endproc = endproc;

    startprocess (args, env (startproc, endproc), &proc->procinfo);
}

void startmultiply (apfloat *x, apfloat *y, procdata *proc)
{
    size_t t = 0;
    string argb[MAXARGS];
    const char *args[MAXARGS];

    writenumber (proc->startproc, proc->endproc, x, 'a');
    writenumber (proc->startproc, proc->endproc, y, 'b');

    { ostringstream s; s << progname; argb[t++] = s.str (); }
    { ostringstream s; s << "-m"; argb[t++] = s.str (); }
    { ostringstream s; s << proc->startproc; argb[t++] = s.str (); }
    { ostringstream s; s << proc->endproc; argb[t++] = s.str (); }
    { ostringstream s; s << 'a'; argb[t++] = s.str (); }
    { ostringstream s; s << 'b'; argb[t++] = s.str (); }
    { ostringstream s; s << Basedigit; argb[t++] = s.str (); }

    assert (t < MAXARGS);

    args[t] = 0;
    while (t--)
        args[t] = argb[t].c_str ();

    startprocess (args, 0, &proc->procinfo);
}

void startsqrt (procdata *proc)
{
    size_t t = 0;
    string argb[MAXARGS];
    const char *args[MAXARGS];

    { ostringstream s; s << progname; argb[t++] = s.str (); }
    { ostringstream s; s << "-s"; argb[t++] = s.str (); }
    { ostringstream s; s << proc->startproc; argb[t++] = s.str (); }
    { ostringstream s; s << proc->endproc; argb[t++] = s.str (); }
    { ostringstream s; s << prec; argb[t++] = s.str (); }
    { ostringstream s; s << Basedigit; argb[t++] = s.str (); }

    assert (t < MAXARGS);

    args[t] = 0;
    while (t--)
        args[t] = argb[t].c_str ();

    startprocess (args, 0, &proc->procinfo);
}

void waitprocresult (procdata *proc, apfloat *x, apfloat *y = 0, apfloat *z = 0, char c = DEFCHAR)
{
    waitforprocess (&proc->procinfo);
    readnumber (proc->startproc, proc->endproc, x, y, z, c);
}

inline void waitprocresult (procdata *proc, apfloat *x, char c)
{
    waitprocresult (proc, x, 0, 0, c);
}

void print (void)
{
    size_t pct;

    if (output)
    {
        pct = (size_t) (100.0 * currk / maxk);

        if (pct != oldpct)
        {
            cerr << pct << "% complete\r";
            cerr.flush ();

            oldpct = pct;
        }
    }
}

apfloat a (size_t n)
{
    apfloat v = A + B * n;

    v.sign (1 - 2 * (n & 1));

    return v;
}

apfloat p (size_t n)
{
    apfloat f = n, sixf = six * f;

    if (!n)
        return one;
    else
        return (sixf - one) * (two * f - one) * (sixf - five);
}

apfloat q (size_t n)
{
    apfloat f = n;

    if (!n)
        return one;
    else
        return J * f * f * f;
}

void r (size_t startproc, size_t endproc, size_t N1, size_t N2, apfloat *T, apfloat *Q, apfloat *P, bool toplevel = false)
{
    switch (N2 - N1)
    {
        case 0:
        {
            assert (N1 != N2);

            break;
        }
        case 1:
        {
            apfloat p0 = p (N1);

            *T = a (N1) * p0;
            *Q = q (N1);
            if (P) *P = p0;

            currk += 1;

            break;
        }
        case 2:
        {
            apfloat p0 = p (N1), p01 = p0 * p (N1 + 1),
                    q1 = q (N1 + 1);

            *T = q1 * a (N1) * p0 +
                 a (N1 + 1) * p01;
            *Q = q (N1) * q1;
            if (P) *P = p01;

            currk += 4;

            break;
        }
        case 3:
        {
            apfloat p0 = p (N1), p01 = p0 * p (N1 + 1), p012 = p01 * p (N1 + 2),
                    q2 = q (N1 + 2), q12 = q (N1 + 1) * q2;

            *T = q12 * a (N1) * p0 +
                 q2 * a (N1 + 1) * p01 +
                 a (N1 + 2) * p012;
            *Q = q (N1) * q12;
            if (P) *P = p012;

            currk += 8;

            break;
        }
        case 4:
        {
            apfloat p0 = p (N1), p01 = p0 * p (N1 + 1), p012 = p01 * p (N1 + 2), p0123 = p012 * p (N1 + 3),
                    q3 = q (N1 + 3), q23 = q (N1 + 2) * q3, q123 = q (N1 + 1) * q23;

            *T = q123 * a (N1) * p0 +
                 q23 * a (N1 + 1) * p01 +
                 q3 * a (N1 + 2) * p012 +
                 a (N1 + 3) * p0123;
            *Q = q (N1) * q123;
            if (P) *P = p0123;

            currk += 12;

            break;
        }
        default:
        {
            size_t midproc, Nm, avproc, maxmem, avmem, avthreads, startthread;
            procdata proc1, proc2, proc3;
            apfloat LT, LQ, LP, RT, RQ, RP, tmp;
            bool sqrtp = false;

            // Split calculation of r by number of available processes
            // and available memory (all numbers must fit in memory for effective parallelization

            avproc = endproc - startproc + 1;               // Number of processes we can use

            if (avproc > 1)
            {
                midproc = (startproc + endproc + 1) / 2;
                Nm = N1 + (N2 - N1) * (midproc - startproc) / (endproc - startproc + 1);

                avmem = availablememory (avproc);           // Memory available for us

                // T will be the largest number, and its size is dominated by Q
                // Calculate how big Q would get and see how much memory would be needed
                if (termsize (N2) - termsize (N1) >= avmem)
                {
                    cerr << "Memory limiting calculation split at this level" << endl;
                    avproc = 1;
                }
            }

            if (avproc > 1)
            {
                // Processor available, calculate one half in another process in parallel
                startsubprocess (startproc, midproc - 1, N1, Nm, &proc1);

                // Set this process to use the other processors
                setprocessaffinity (midproc, endproc);
            }
            else
            {
                midproc = startproc;
                Nm = (N1 + N2) / 2;

                // No processor available, do the calculation in this process
                r (startproc, endproc, N1, Nm, &LT, &LQ, &LP);
            }

            // Do the calculation of the other half in this process
            r (midproc, endproc, Nm, N2, &RT, &RQ, (P ? &RP : 0));

            if (avproc > 1)
            {
                waitprocresult (&proc1, &LT, &LQ, &LP);

                currk += (size_t) ((Nm - N1) * (log ((double) (Nm - N1)) / log (2.0) + 1));

                print ();
            }
            else
            {
                currk += Nm - N1;
            }

            // Divide tasks by number of available processes
            // and available memory (all numbers must fit in memory for effective parallelization
            // The inverse square root takes about 1.5 - 1.7 times that of a multiplication

            avproc = endproc - startproc + 1;               // Number of processes we can use

            if (avproc > 1)
            {
                avthreads = avproc;                         // Number of threads we can use
                startthread = startproc;                    // Starting thread number

                avmem = availablememory (avproc);           // Memory available for us

                if (MAX_FORKED_PROCESSES < avproc)
                    avproc = MAX_FORKED_PROCESSES;

                if (toplevel && avmem / (2 * prec / Basedigits + 1) > 1)
                {
                    cerr << "Calculating isqrt in parallel" << endl;
                    avproc--;
                    avmem -= 2 * prec / Basedigits + 1;
                    sqrtp = true;
                }

                maxmem = avmem / (RQ.ap->size + LT.ap->size + 2);
                if (maxmem < avproc)
                {
                    cerr << "Memory limiting processes from " << avproc << " to " << maxmem << endl;
                    avproc = maxmem;
                }

                assert (avproc);                            // Must have sufficient memory

                if (sqrtp)
                {
                    avproc++;                               // Will be decreased by getnthreads
                    getnthreads (&avthreads, &avproc, &startthread, &proc3);
                    startsqrt (&proc3);
                }

                // Set number threads to be used in this process
                getnthreads (&avthreads, &avproc, &startthread, &proc1);
                setprocessaffinity (proc1.startproc, proc1.endproc);
            }
            else
            {
                avproc = 0;
            }

            switch (avproc)
            {
                case 0:
                {
                    *T = RQ * LT + LP * RT;
                    *Q = LQ * RQ;
                    if (P) *P = LP * RP;

                    break;
                }
                case 1:
                {
                    getnthreads (&avthreads, &avproc, &startthread, &proc1);

                    tmp = LP;
                    startmultiply (&tmp, &RT, &proc1);
                    *T = RQ * LT;
                    waitprocresult (&proc1, &tmp);
                    *T += tmp;

                    if (P)
                        startmultiply (&LP, &RP, &proc1);

                    *Q = LQ * RQ;

                    if (P)
                        waitprocresult (&proc1, P);

                    break;
                }
                case 2:
                {
                    getnthreads (&avthreads, &avproc, &startthread, &proc1);
                    getnthreads (&avthreads, &avproc, &startthread, &proc2);

                    tmp = LP;
                    startmultiply (&tmp, &RT, &proc1);
                    tmp = RQ;
                    startmultiply (&tmp, &LT, &proc2);

                    *Q = LQ * RQ;
                    if (P) *P = LP * RP;

                    waitprocresult (&proc1, T);
                    waitprocresult (&proc2, &tmp);

                    *T += tmp;


                    break;
                }
                default:
                {
                    getnthreads (&avthreads, &avproc, &startthread, &proc1);
                    getnthreads (&avthreads, &avproc, &startthread, &proc2);
                    if (P)
                        getnthreads (&avthreads, &avproc, &startthread, &proc3);

                    tmp = LP;
                    startmultiply (&tmp, &RT, &proc1);
                    tmp = RQ;
                    startmultiply (&tmp, &LT, &proc2);

                    if (P)
                        startmultiply (&LP, &RP, &proc3);

                    *Q = LQ * RQ;

                    waitprocresult (&proc1, T);
                    waitprocresult (&proc2, &tmp);
                    *T += tmp;

                    if (P)
                        waitprocresult (&proc3, P);

                    break;
                }
            }

            if (sqrtp)
                waitprocresult (&proc3, &isqrt);            // Read the inverse square root of 640320

            if (endproc > startproc)
                setprocessaffinity (startproc, endproc);    // Restore threads

            currk += N2 - Nm;
        }
    }

    print ();
}

void calcpart (size_t startproc, size_t endproc, size_t startterm, size_t endterm, apfloat *T, apfloat *Q, apfloat *P, bool toplevel)
{
    size_t n;
    time_t tt;

    if (toplevel)
    {
        cerr << "Using the Chudnovsky brothers' binary splitting algorithm" << endl;
    }

    A = 13591409;
    B = 545140134;
    J = 101568000; J *= 107701824;       // J = 10939058860032000

    one = 1;
    two = 2;
    five = 5;
    six = 6;

    A.prec (prec);
    B.prec (prec);
    J.prec (prec);

    one.prec (prec);
    two.prec (prec);
    five.prec (prec);
    six.prec (prec);

    n = endterm - startterm + 1;
    maxk = (size_t) (n * (log ((double) n) / log (2.0) + 1));
    currk = 0;

    tt = time (0);

    r (startproc, endproc, startterm, endterm, T, Q, P, toplevel);

    if (toplevel)
    {
        cerr.setf (ios::fixed, ios::floatfield);
        cerr << "100% complete, elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;
    }
}

apfloat final (apfloat T, apfloat Q)
{
    time_t tt;
    apfloat p;

    cerr << "Final value";

    tt = time (0);

    if (!isqrt.ap) isqrt = invroot (apfloat (640320, prec), 2);
    p = invroot (isqrt * T, 1) * 53360 * Q;

    cerr.setf (ios::fixed, ios::floatfield);
    cerr << " took " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;

    return p;
}

int main (int argc, char *argv[], char *env[])
{
    size_t startproc, endproc, startterm, endterm;
    int n = 2, m = 0, b = 3, base = 10;
    time_t tt;
    apfloat T, Q, P;

    if (argc > 1)
    {
        if (!strncmp (argv[1], "-p", 2))
        {
            m = 1;
            n = 7;
            b = 7;
        }
        else if (!strncmp (argv[1], "-m", 2))
        {
            m = 2;
            n = 6;
            b = 6;
        }
        else if (!strncmp (argv[1], "-s", 2))
        {
            m = 3;
            n = 5;
            b = 5;
        }
    }

    if (argc < n)
    {
        cerr << "USAGE: aptestm digits [processes] [base]" << endl;
        cerr << "       aptestm -p[rocess] digits startproc endproc startterm endterm [base]" << endl;
        cerr << "       aptestm -m[ultiply] startproc endproc in1 in2 [base]" << endl;
        cerr << "       aptestm -s[qrt] startproc endproc digits [base]" << endl;
        cerr << "    base must be 2...36" << endl;
        return 2;
    }

    if (argc > b)
    {
        istringstream s (argv[b]);
        if (!(s >> base))
        {
            cerr << "Invalid argument base: " << argv[b] << endl;
            return 1;
        }
    }

    progname = argv[0];
    baseenv = env;

    apbase (base);

    if (m == 0)
    {
        apfloat p;

        istringstream s (argv[1]);
        if (!(s >> prec) || !prec)
        {
            cerr << "Invalid argument digits: " << argv[1] << endl;
            return 1;
        }

        if (argc > 2)
        {
            istringstream s (argv[2]);
            if (!(s >> endproc) || !endproc || endproc > 32)
            {
                cerr << "Invalid argument processes: " << argv[2] << endl;
                return 1;
            }
        }
        else
        {
            endproc = NProcessors;          // Assumed to be set or detected appropriately
            if (!endproc) endproc = 1;
            else if (endproc > 32) endproc = 32;
        }

        dump ();

        cerr << "Calculating pi to " << prec << " base-" << Basedigit << " digits";
        if (endproc > 1) cerr << " using up to " << endproc << " processes";
        cerr << endl;

        tt = time (0);

        startterm = 0;
        endterm = (size_t) (prec * log ((double) Basedigit) / 32.65445004177);
        totalproc = endproc;
        startproc = 0;
        endproc--;              // Count starts from zero

        output = true;

        setfno (startproc, endproc);
        setprocessaffinity (startproc, endproc);

        calcpart (startproc, endproc, startterm, endterm + 1, &T, &Q, 0, true);
        p = final (T, Q);

        cout << pretty << p << endl;

        cerr.setf (ios::fixed, ios::floatfield);
        cerr << "Total elapsed time " << setprecision (0) << difftime (time (0), tt) << " seconds" << endl;
    }
    else if (m == 1)
    {
        istringstream s2 (argv[2]);
        if (!(s2 >> prec) || !prec)
        {
            cerr << "Invalid argument digits: " << argv[2] << endl;
            return 1;
        }

        istringstream s3 (argv[3]);
        if (!(s3 >> startproc))
        {
            cerr << "Invalid argument startproc: " << argv[3] << endl;
            return 1;
        }

        istringstream s4 (argv[4]);
        if (!(s4 >> endproc) || endproc < startproc)
        {
            cerr << "Invalid argument endproc: " << argv[4] << endl;
            return 1;
        }

        istringstream s5 (argv[5]);
        if (!(s5 >> startterm))
        {
            cerr << "Invalid argument startterm: " << argv[5] << endl;
            return 1;
        }

        istringstream s6 (argv[6]);
        if (!(s6 >> endterm) || endterm < startterm)
        {
            cerr << "Invalid argument endterm: " << argv[6] << endl;
            return 1;
        }

        output = false;

        totalproc = endproc - startproc + 1;

        setfno (startproc, endproc);
        setprocessaffinity (startproc, endproc);

        calcpart (startproc, endproc, startterm, endterm, &T, &Q, &P, false);

        writenumber (startproc, endproc, &T, &Q, &P);
    }
    else if (m == 2)
    {
        apfloat x, y;

        istringstream s2 (argv[2]);
        if (!(s2 >> startproc))
        {
            cerr << "Invalid argument startproc: " << argv[2] << endl;
            return 1;
        }

        istringstream s3 (argv[3]);
        if (!(s3 >> endproc) || endproc < startproc)
        {
            cerr << "Invalid argument endproc: " << argv[3] << endl;
            return 1;
        }

        totalproc = endproc - startproc + 1;

        setfno (startproc, endproc);
        setprocessaffinity (startproc, endproc);

        readnumber (startproc, endproc, &x, argv[4][0]);
        readnumber (startproc, endproc, &y, argv[5][0]);

        x *= y;

        writenumber (startproc, endproc, &x);
    }
    else if (m == 3)
    {
        apfloat x;

        istringstream s2 (argv[2]);
        if (!(s2 >> startproc))
        {
            cerr << "Invalid argument startproc: " << argv[2] << endl;
            return 1;
        }

        istringstream s3 (argv[3]);
        if (!(s3 >> endproc) || endproc < startproc)
        {
            cerr << "Invalid argument endproc: " << argv[3] << endl;
            return 1;
        }

        istringstream s4 (argv[4]);
        if (!(s4 >> prec) || !prec)
        {
            cerr << "Invalid argument digits: " << argv[4] << endl;
            return 1;
        }

        totalproc = endproc - startproc + 1;

        setfno (startproc, endproc);
        setprocessaffinity (startproc, endproc);

        x = invroot (apfloat (640320, prec), 2);

        writenumber (startproc, endproc, &x);
    }

    return 0;
}
