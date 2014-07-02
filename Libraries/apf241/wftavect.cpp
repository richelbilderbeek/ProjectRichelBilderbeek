#include "ap.h"


// Efficient "vector" WFTA algorithms

const int NALGS = 41;

const int MAXN = 5040;
const int BSIZ = 560;

// All possible transform lengths
int n[] = {2, 3, 4, 5, 6, 8, 9, 10, 12, 16,
           18, 20, 24, 30, 36, 40, 48, 60, 72, 80,
           84, 90, 120, 144, 168, 180, 240, 252, 280, 336,
           360, 420, 504, 560, 720, 840, 1008, 1260, 1680, 2520,
           5040};

// Sequences for all possible transform lengths
int s2[] = {2}, s3[] = {3}, s4[] = {4}, s5[] = {5}, s6[] = {3, 2},
    s8[] = {8}, s9[] = {9}, s10[] = {2, 5}, s12[] = {3, 4}, s16[] = {16},
    s18[] = {2, 9}, s20[] = {4, 5}, s24[] = {3, 8}, s30[] = {3, 2, 5},
    s36[] = {4, 9}, s40[] = {8, 5}, s48[] = {3, 16}, s60[] = {3, 4, 5},
    s72[] = {8, 9}, s80[] = {16, 5}, s84[] = {3, 4, 7}, s90[] = {2, 9, 5},
    s120[] = {3, 8, 5}, s144[] = {16, 9}, s168[] = {3, 8, 7}, s180[] = {4, 9, 5},
    s240[] = {3, 16, 5}, s252[] = {4, 9, 7}, s280[] = {8, 7, 5},
    s336[] = {3, 16, 7}, s360[] = {8, 9, 5}, s420[] = {3, 4, 7, 5},
    s504[] = {8, 9, 7}, s560[] = {16, 7, 5}, s720[] = {16, 9, 5},
    s840[] = {3, 8, 7, 5}, s1008[] = {16, 9, 7}, s1260[] = {4, 9, 7, 5},
    s1680[] = {3, 16, 7, 5}, s2520[] = {8, 9, 7, 5}, s5040[] = {16, 9, 7, 5};

int *s[] = {s2, s3, s4, s5, s6, s8, s9, s10, s12, s16,
            s18, s20, s24, s30, s36, s40, s48, s60, s72, s80,
            s84, s90, s120, s144, s168, s180, s240, s252, s280, s336,
            s360, s420, s504, s560, s720, s840, s1008, s1260, s1680, s2520,
            s5040};

// Multiplication counts
int m[] = {2, 3, 4, 6, 6, 8, 11, 12, 12, 18,
           22, 24, 24, 36, 44, 48, 54, 72, 88, 108,
           108, 132, 144, 198, 216, 264, 324, 396, 432, 486,
           528, 648, 792, 972, 1188, 1296, 1782, 2376, 2916, 4752,
           10692};

// Multiplication sequences
int ms2[] = {2}, ms3[] = {3}, ms4[] = {4}, ms5[] = {6}, ms6[] = {3, 2},
    ms8[] = {8}, ms9[] = {11}, ms10[] = {2, 6}, ms12[] = {3, 4}, ms16[] = {18},
    ms18[] = {2, 11}, ms20[] = {4, 6}, ms24[] = {3, 8}, ms30[] = {3, 2, 6},
    ms36[] = {4, 11}, ms40[] = {8, 6}, ms48[] = {3, 18}, ms60[] = {3, 4, 6},
    ms72[] = {8, 11}, ms80[] = {18, 6}, ms84[] = {3, 4, 9}, ms90[] = {2, 11, 6},
    ms120[] = {3, 8, 6}, ms144[] = {18, 11}, ms168[] = {3, 8, 9}, ms180[] = {4, 11, 6},
    ms240[] = {3, 18, 6}, ms252[] = {4, 11, 9}, ms280[] = {8, 9, 6},
    ms336[] = {3, 18, 9}, ms360[] = {8, 11, 6}, ms420[] = {3, 4, 9, 6},
    ms504[] = {8, 11, 9}, ms560[] = {18, 9, 6}, ms720[] = {18, 11, 6},
    ms840[] = {3, 8, 9, 6}, ms1008[] = {18, 11, 9}, ms1260[] = {4, 11, 9, 6},
    ms1680[] = {3, 18, 9, 6}, ms2520[] = {8, 11, 9, 6}, ms5040[] = {18, 11, 9, 6};

int *ms[] = {ms2, ms3, ms4, ms5, ms6, ms8, ms9, ms10, ms12, ms16,
             ms18, ms20, ms24, ms30, ms36, ms40, ms48, ms60, ms72, ms80,
             ms84, ms90, ms120, ms144, ms168, ms180, ms240, ms252, ms280, ms336,
             ms360, ms420, ms504, ms560, ms720, ms840, ms1008, ms1260, ms1680, ms2520,
             ms5040};

modint t0[BSIZ],  t1[BSIZ],  t2[BSIZ],  t3[BSIZ],  t4[BSIZ],  t5[BSIZ],
       t6[BSIZ],  t7[BSIZ],  t8[BSIZ],  t9[BSIZ],  t10[BSIZ],  t11[BSIZ],
       t12[BSIZ],  t13[BSIZ],  t14[BSIZ],  t15[BSIZ],  t16[BSIZ],  t17[BSIZ],
       t18[BSIZ],  t19[BSIZ],  t20[BSIZ],  t21[BSIZ];
modint b[2 * BSIZ];

#if defined (USEASMGCC386)

inline void vecadd (modint *d, modint *s1, modint *s2, int n)
{
    asm ("movl _modulus, %%edx;\
          leal (%%esi, %%ecx, 4), %%esi;\
          leal (%%ebx, %%ecx, 4), %%ebx;\
          leal (%%edi, %%ecx, 4), %%edi;\
          negl %%ecx;\
          1: movl (%%esi, %%ecx, 4), %%eax;\
          addl (%%ebx, %%ecx, 4), %%eax;\
          cmpl %%edx, %%eax; jb 0f; subl %%edx, %%eax; 0:;\
          movl %%eax, (%%edi, %%ecx, 4);\
          incl %%ecx; jnz 1b"
          :
          : "D" (d), "S" (s1) , "b" (s2) , "c" (n)
          : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "cc");
}

inline void vecsub (modint *d, modint *s1, modint *s2, int n)
{
    asm ("movl _modulus, %%edx;\
          leal (%%esi, %%ecx, 4), %%esi;\
          leal (%%ebx, %%ecx, 4), %%ebx;\
          leal (%%edi, %%ecx, 4), %%edi;\
          negl %%ecx;\
          1: movl (%%esi, %%ecx, 4), %%eax;\
          subl (%%ebx, %%ecx, 4), %%eax;\
          jnc 0f; addl %%edx, %%eax; 0:;\
          movl %%eax, (%%edi, %%ecx, 4);\
          incl %%ecx; jnz 1b"
          :
          : "D" (d), "S" (s1) , "b" (s2) , "c" (n)
          : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "cc");
}

inline void vecaddsub (modint *d1, modint *d2, modint *s1, modint *s2, int n)
{
    asm ("pushl %%ebp;\
          leal (%%esi, %%ecx, 4), %%esi;\
          leal (%%ebx, %%ecx, 4), %%ebx;\
          leal (%%edx, %%ecx, 4), %%edx;\
          leal (%%edi, %%ecx, 4), %%edi;\
          negl %%ecx;\
          1: movl (%%esi, %%ecx, 4), %%ebp;\
          movl (%%ebx, %%ecx, 4), %%eax;\
          addl %%ebp, %%eax; addl %%ebp, %%ebp; subl %%eax, %%ebp;\
          jnc 0f; addl _modulus, %%ebp; 0:;\
          movl %%ebp, (%%edx, %%ecx, 4);\
          movl _modulus, %%ebp;\
          cmpl %%ebp, %%eax; jb 0f; subl %%ebp, %%eax; 0:;\
          movl %%eax, (%%edi, %%ecx, 4);\
          incl %%ecx; jnz 1b;\
          popl %%ebp"
          :
          : "D" (d1), "d" (d2), "S" (s1) , "b" (s2) , "c" (n)
          : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "cc");
}

inline void veccopy (modint *d, modint *s, int n)
{
    asm ("cld; rep; movsl"
          :
          : "D" (d), "S" (s) , "c" (n)
          : "%ecx", "%esi", "%edi", "cc");
}

#else

inline void vecadd (modint *d, modint *s1, modint *s2, int n)
{
    do
    {
        *(d++) = *(s1++) + *(s2++);
    } while (--n);
}

inline void vecsub (modint *d, modint *s1, modint *s2, int n)
{
    do
    {
        *(d++) = *(s1++) - *(s2++);
    } while (--n);
}

inline void vecaddsub (modint *d1, modint *d2, modint *s1, modint *s2, int n)
{
    modint t1, t2;
    do
    {
        t1 = *s1 + *s2;
        t2 = *(s1++) - *(s2++);
        *(d1++) = t1;
        *(d2++) = t2;
    } while (--n);
}

inline void veccopy (modint *d, modint *s, int n)
{
    do
    {
        *(d++) = *(s++);
    } while (--n);
}

#endif

void wfta2 (modint x[], modint w[])
{
    modint m0, m1;

    m0 = w[0] * (x[0] + x[1]);
    m1 = w[1] * (x[0] - x[1]);

    x[0] = m0;
    x[1] = m1;
}

void wfta3 (modint x[], modint w[])
{
    modint t0;
    modint m0, m1, m2;

    t0 = x[1] + x[2];

    m0 = w[0] * (x[0] + t0);
    m1 = w[1] * t0;
    m2 = w[2] * (x[1] - x[2]);

    t0 = m0 + m1;

    x[0] = m0;
    x[1] = t0 + m2;
    x[2] = t0 - m2;
}

void wfta4 (modint x[], modint w[])
{
    modint t0, t1;
    modint m0, m1, m2, m3;

    t0 = x[0] + x[2];
    t1 = x[1] + x[3];

    m0 = w[0] * (t0 + t1);
    m1 = w[1] * (t0 - t1);
    m2 = w[2] * (x[0] - x[2]);
    m3 = w[3] * (x[1] - x[3]);

    x[0] = m0;
    x[2] = m1;
    x[1] = m2 + m3;
    x[3] = m2 - m3;
}

void wfta5 (modint x[], modint w[])
{
    modint t0, t1, t2, t3, t4;
    modint m0, m1, m2, m3, m4, m5;

    t0 = x[1] + x[4];
    t2 = x[1] - x[4];
    t1 = x[3] + x[2];
    t3 = x[3] - x[2];
    t4 = t0 + t1;

    m0 = w[0] * (x[0] + t4);
    m1 = w[1] * t4;
    m2 = w[2] * (t0 - t1);
    m3 = w[3] * (t2 + t3);
    m4 = w[4] * t3;
    m5 = w[5] * t2;

    t0 = m0 + m1;
    t1 = t0 + m2;
    t3 = t0 - m2;
    t2 = m3 - m4;
    t4 = m3 + m5;

    x[0] = m0;
    x[1] = t1 + t2;
    x[4] = t1 - t2;
    x[2] = t3 + t4;
    x[3] = t3 - t4;
}

void wfta7 (modint x[], modint w[])
{
    modint t0, t1, t2, t3, t4, t5, t6;
    modint m0, m1, m2, m3, m4, m5, m6, m7, m8;

    t0 = x[1] + x[6];
    t4 = x[1] - x[6];
    t1 = x[2] + x[5];
    t5 = x[2] - x[5];
    t2 = x[4] + x[3];
    t6 = x[4] - x[3];
    t3 = t0 + t1 + t2;

    m0 = w[0] * (x[0] + t3);
    m1 = w[1] * t3;
    m2 = w[2] * (t0 - t2);
    m3 = w[3] * (t2 - t1);
    m4 = w[4] * (t1 - t0);
    m5 = w[5] * (t4 + t5 + t6);
    m6 = w[6] * (t4 - t6);
    m7 = w[7] * (t6 - t5);
    m8 = w[8] * (t5 - t4);

    t0 = m0 + m1;
    t1 = t0 + m2 + m3;
    t2 = t0 - m2 - m4;
    t3 = t0 - m3 + m4;
    t4 = m5 + m6 + m7;
    t5 = m5 - m6 - m8;
    t6 = m5 - m7 + m8;

    x[0] = m0;
    x[1] = t1 + t4;
    x[6] = t1 - t4;
    x[2] = t2 + t5;
    x[5] = t2 - t5;
    x[4] = t3 + t6;
    x[3] = t3 - t6;
}

void wfta8 (modint x[], modint w[])
{
    modint t0, t1, t2, t3, t4, t5, t6, t7;
    modint m0, m1, m2, m3, m4, m5, m6, m7;

    t0 = x[0] + x[4];
    t1 = x[2] + x[6];
    t2 = x[1] + x[5];
    t3 = x[1] - x[5];
    t4 = x[3] + x[7];
    t5 = x[3] - x[7];
    t6 = t0 + t1;
    t7 = t2 + t4;

    m0 = w[0] * (t6 + t7);
    m1 = w[1] * (t6 - t7);
    m2 = w[2] * (t0 - t1);
    m3 = w[3] * (x[0] - x[4]);
    m5 = w[5] * (t2 - t4);
    m6 = w[6] * (x[2] - x[6]);
    m7 = w[7] * (t3 + t5);
    m4 = w[4] * (t3 - t5);

    t0 = m3 + m4;
    t1 = m3 - m4;
    t2 = m6 + m7;
    t3 = m6 - m7;

    x[0] = m0;
    x[4] = m1;
    x[1] = t0 + t2;
    x[7] = t0 - t2;
    x[2] = m2 + m5;
    x[6] = m2 - m5;
    x[5] = t1 + t3;
    x[3] = t1 - t3;
}

void wfta9 (modint x[], modint w[])
{
    modint t0, t1, t2, t3, t4, t5, t6, t7;
    modint m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10;
    modint r0, r1, r2, r3, r4, r5, r6, r7;

    t0 = x[8] + x[1];
    t7 = x[8] - x[1];
    t1 = x[7] + x[2];
    t6 = x[7] - x[2];
    t2 = x[6] + x[3];
    t5 = x[6] - x[3];
    t3 = x[5] + x[4];
    t4 = x[5] - x[4];

    m0 = w[0] * x[0];
    m2 = w[2] * t2;
    m1 = w[1] * (t0 + t1 + t3);
    m3 = w[3] * (t0 - t3);
    m4 = w[4] * (t1 - t3);
    m5 = w[5] * (t0 - t1);
    m6 = w[6] * t5;
    m7 = w[7] * (t7 - t6 + t4);
    m8 = w[8] * (t7 - t4);
    m9 = w[9] * (t4 + t6);
    m10 = w[10] * (t7 + t6);

    t0 = m2 + m2 + m0;
    t2 = m0 - m2;
    t1 = m3 + m4;
    t3 = m3 - m5;
    t6 = m4 + m5;
    t4 = m8 - m10;
    t5 = m9 + m8;
    t7 = m9 + m10;

    r0 = t0 + m1 + m1;
    r1 = t0 - m1;
    r2 = t2 - t1;
    r4 = t2 + t3;
    r3 = t6 + t2;
    r5 = t4 + m6;
    r6 = t7 + m6;
    r7 = t5 - m6;


    x[0] = r0;
    x[8] = r3 + r6;
    x[1] = r3 - r6;
    x[7] = r2 + r7;
    x[2] = r2 - r7;
    x[6] = r1 + m7;
    x[3] = r1 - m7;
    x[5] = r4 + r5;
    x[4] = r4 - r5;
}

void wfta16 (modint x[], modint w[])
{
    modint t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12,
           t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25;
    modint m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17;

    t0 = x[0] + x[8];
    t1 = x[4] + x[12];
    t2 = x[2] + x[10];
    t3 = x[2] - x[10];
    t4 = x[6] + x[14];
    t5 = x[6] - x[14];
    t6 = x[1] + x[9];
    t7 = x[1] - x[9];
    t8 = x[3] + x[11];
    t9 = x[3] - x[11];
    t10 = x[5] + x[13];
    t11 = x[5] - x[13];
    t12 = x[7] + x[15];
    t13 = x[7] - x[15];
    t14 = t0 + t1;
    t15 = t2 + t4;
    t16 = t14 + t15;
    t17 = t6 + t10;
    t18 = t6 - t10;
    t19 = t8 + t12;
    t20 = t8 - t12;
    t21 = t17 + t19;
    t22 = t7 + t13;
    t23 = t7 - t13;
    t24 = t11 + t9;
    t25 = t11 - t9;

    m0 = w[0] * (t16 + t21);
    m1 = w[1] * (t16 - t21);
    m2 = w[2] * (t14 - t15);
    m3 = w[3] * (t0 - t1);
    m4 = w[4] * (x[0] - x[8]);
    m13 = w[13] * (t18 + t20);
    m5 = w[5] * (t18 - t20);
    m14 = w[14] * (t3 + t5);
    m6 = w[6] * (t3 - t5);
    m7 = w[7] * (t23 + t25);
    m8 = w[8] * t23;
    m9 = w[9] * t25;
    m10 = w[10] * (t17 - t19);
    m11 = w[11] * (t2 - t4);
    m12 = w[12] * (x[4] - x[12]);
    m15 = w[15] * (t22 + t24);
    m16 = w[16] * t22;
    m17 = w[17] * t24;

    t0 = m3 + m5;
    t1 = m3 - m5;
    t2 = m13 + m11;
    t3 = m13 - m11;
    t4 = m4 + m6;
    t5 = m4 - m6;
    t6 = m8 - m7;
    t7 = m9 - m7;
    t8 = t4 + t6;
    t9 = t4 - t6;
    t10 = t5 + t7;
    t11 = t5 - t7;
    t12 = m12 + m14;
    t13 = m12 - m14;
    t14 = m15 + m16;
    t15 = m15 - m17;
    t16 = t12 + t14;
    t17 = t12 - t14;
    t18 = t13 + t15;
    t19 = t13 - t15;

    x[0] = m0;
    x[8] = m1;
    x[1] = t8 + t16;
    x[15] = t8 - t16;
    x[2] = t0 + t2;
    x[14] = t0 - t2;
    x[13] = t11 + t19;
    x[3] = t11 - t19;
    x[4] = m2 + m10;
    x[12] = m2 - m10;
    x[5] = t10 + t18;
    x[11] = t10 - t18;
    x[6] = t1 + t3;
    x[10] = t1 - t3;
    x[9] = t9 + t17;
    x[7] = t9 - t17;
}

void (*wftas[]) (modint x[], modint w[]) =
{0, 0, wfta2, wfta3, wfta4, wfta5, 0, wfta7, wfta8, wfta9, 0, 0, 0, 0, 0, 0, wfta16};

void permute (modint x[], int p[], int n)
{
    int k;
    modint t[MAXN];

    for (k = 0; k < n; k++)
        t[k] = x[p[k]];

    for (k = 0; k < n; k++)
        x[k] = t[k];
}

void unpermute (modint x[], int p[], int n)
{
    int k;
    modint t[MAXN];

    for (k = 0; k < n; k++)
        t[p[k]] = x[k];

    for (k = 0; k < n; k++)
        x[k] = t[k];
}

extern void (*wftan[]) (modint x[], modint w[], int n, int s[], int m, int ms[]);

void wftan2 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, nn, nm;
    modint *p;

    p = x + n;

    vecaddsub (x, p, x, p, n);

    k = s[0];

    if (k == n)
    {
        wftas[k] (x, w);
        wftas[k] (p, w + m);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        wftan[k] (x, w, nn, s, nm, ms);
        wftan[k] (p, w + m, nn, s, nm, ms);
    }
}

void wftan3 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, nn, nm;
    modint *p[3];

    p[2] = (p[1] = (p[0] = x) + n) + n;

    vecaddsub (p[1], p[2], p[1], p[2], n);
    vecadd (p[0], p[0], p[1], n);

    k = s[0];

    if (k == n)
    {
        wftas[k] (x, w);
        wftas[k] (x + k, w + m);
        wftas[k] (x + k + k, w + m + m);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        wftan[k] (x, w, nn, s, nm, ms);
        wftan[k] (x + n, w + m, nn, s, nm, ms);
        wftan[k] (x + n + n, w + m + m, nn, s, nm, ms);
    }

    vecadd (p[1], p[1], p[0], n);
    vecaddsub (p[1], p[2], p[1], p[2], n);
}

void wftan4 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, na, ma;
    modint *p[4], *t[2] = {t0, t1};

    p[3] = (p[2] = (p[1] = (p[0] = x) + n) + n) + n;

    vecaddsub (t[0], p[2], p[0], p[2], n);
    vecaddsub (t[1], p[3], p[1], p[3], n);
    vecaddsub (p[0], p[1], t[0], t[1], n);

    k = s[0];

    if (k == n)
    {
        for (na = ma = j = 0; j < 4; j++, na += k, ma += m)
            wftas[k] (x + na, w + ma);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        for (na = ma = j = 0; j < 4; j++, na += n, ma += m)
            wftan[k] (x + na, w + ma, nn, s, nm, ms);
    }

    vecaddsub (t[0], p[3], p[2], p[3], n);
    veccopy (p[2], p[1], n);
    veccopy (p[1], t[0], n);
}

void wftan5 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint *p[6], *t[2] = {t0, t1};

    for (p[0] = x, k = 1; k < 5; k++)
        p[k] = p[k - 1] + n;

    p[5] = b;

    vecaddsub (t[0], p[5], p[1], p[4], n);
    vecaddsub (t[1], p[4], p[3], p[2], n);
    vecaddsub (p[1], p[2], t[0], t[1], n);
    vecadd (p[0], p[0], p[1], n);
    vecadd (p[3], p[4], p[5], n);

    k = s[0];

    if (k == n)
    {
        for (ma = j = 0; j < 6; j++, ma += m)
            wftas[k] (p[j], w + ma);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        for (ma = j = 0; j < 6; j++, ma += m)
            wftan[k] (p[j], w + ma, nn, s, nm, ms);
    }

    vecadd (p[1], p[1], p[0], n);
    vecaddsub (p[1], p[2], p[1], p[2], n);
    vecsub (p[4], p[3], p[4], n);
    vecadd (p[3], p[3], p[5], n);

    vecaddsub (p[1], p[4], p[1], p[4], n);
    vecaddsub (p[2], p[3], p[2], p[3], n);
}

void wftan7 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint *p[9], *t[7] = {t0, t1, t2, t3, t4, t5, t6};

    for (p[0] = x, k = 1; k < 7; k++)
        p[k] = p[k - 1] + n;

    p[8] = (p[7] = b) + n;

    vecaddsub (t[0], p[6], p[1], p[6], n);
    vecaddsub (p[2], p[5], p[2], p[5], n);
    vecaddsub (p[4], p[3], p[4], p[3], n);
    vecadd (p[1], t[0], p[2], n);
    vecadd (p[1], p[1], p[4], n);
    vecadd (p[0], p[0], p[1], n);

    vecsub (p[7], p[3], p[5], n);
    vecsub (p[8], p[5], p[6], n);
    vecaddsub (t[1], p[6], p[6], p[3], n);
    vecadd (p[5], p[5], t[1], n);

    vecsub (p[3], p[4], p[2], n);
    vecsub (t[1], p[2], t[0], n);
    vecsub (p[2], t[0], p[4], n);
    veccopy (p[4], t[1], n);

    k = s[0];

    if (k == n)
    {
        for (ma = j = 0; j < 9; j++, ma += m)
            wftas[k] (p[j], w + ma);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        for (ma = j = 0; j < 9; j++, ma += m)
            wftan[k] (p[j], w + ma, nn, s, nm, ms);
    }

    vecadd (t[0], p[0], p[1], n);
    vecaddsub (p[1], p[2], t[0], p[2], n);
    vecadd (t[1], p[1], p[3], n);
    vecsub (t[2], p[2], p[4], n);
    vecsub (t[3], t[0], p[3], n);
    vecadd (t[3], t[3], p[4], n);

    vecaddsub (t[4], t[5], p[5], p[6], n);
    vecadd (t[4], t[4], p[7], n);
    vecsub (t[5], t[5], p[8], n);
    vecsub (t[6], p[5], p[7], n);
    vecadd (t[6], t[6], p[8], n);

    vecaddsub (p[1], p[6], t[1], t[4], n);
    vecaddsub (p[2], p[5], t[2], t[5], n);
    vecaddsub (p[4], p[3], t[3], t[6], n);
}

void wftan8 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint *p[8], *t[8] = {t0, t1, t2, t3, t4, t5, t6, t7};

    for (p[0] = x, k = 1; k < 8; k++)
        p[k] = p[k - 1] + n;

    vecaddsub (t[1], p[6], p[2], p[6], n);
    vecaddsub (t[2], t[3], p[1], p[5], n);
    vecaddsub (t[4], t[5], p[3], p[7], n);
    vecaddsub (t[0], p[3], p[0], p[4], n);
    vecaddsub (t[6], p[2], t[0], t[1], n);
    vecaddsub (t[7], p[5], t[2], t[4], n);

    vecaddsub (p[0], p[1], t[6], t[7], n);
    vecaddsub (p[7], p[4], t[3], t[5], n);

    k = s[0];

    if (k == n)
    {
        for (ma = j = 0; j < 8; j++, ma += m)
            wftas[k] (p[j], w + ma);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        for (ma = j = 0; j < 8; j++, ma += m)
            wftan[k] (p[j], w + ma, nn, s, nm, ms);
    }

    vecaddsub (t[0], t[1], p[3], p[4], n);
    vecaddsub (t[2], t[3], p[6], p[7], n);

    veccopy (p[4], p[1], n);
    vecaddsub (p[1], p[7], t[0], t[2], n);
    vecaddsub (p[2], p[6], p[2], p[5], n);
    vecaddsub (p[5], p[3], t[1], t[3], n);
}

void wftan9 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint *p[11], *t[8] = {t0, t1, t2, t3, t4, t5, t6, t7};

    for (p[0] = x, k = 1; k < 9; k++)
        p[k] = p[k - 1] + n;

    p[10] = (p[9] = b) + n;

    vecaddsub (t[0], t[7], p[8], p[1], n);
    vecaddsub (t[1], t[6], p[7], p[2], n);
    vecaddsub (p[2], p[6], p[6], p[3], n);
    vecaddsub (t[3], t[4], p[5], p[4], n);

    vecaddsub (p[1], p[3], t[0], t[3], n);
    vecadd (p[1], p[1], t[1], n);
    vecsub (p[3], t[0], t[3], n);
    vecsub (p[4], t[1], t[3], n);
    vecsub (p[5], t[0], t[1], n);

    vecaddsub (p[7], p[8], t[7], t[4], n);
    vecsub (p[7], p[7], t[6], n);
    vecsub (p[8], t[7], t[4], n);
    vecadd (p[9], t[4], t[6], n);
    vecadd (p[10], t[7], t[6], n);

    k = s[0];

    if (k == n)
    {
        for (ma = j = 0; j < 11; j++, ma += m)
            wftas[k] (p[j], w + ma);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        for (ma = j = 0; j < 11; j++, ma += m)
            wftan[k] (p[j], w + ma, nn, s, nm, ms);
    }

    vecaddsub (t[0], t[2], p[0], p[2], n);
    vecadd (t[0], t[0], p[2], n);

    vecadd (t[1], p[3], p[4], n);
    vecsub (t[3], p[3], p[5], n);
    vecadd (t[6], p[4], p[5], n);
    vecsub (t[4], p[8], p[10], n);
    vecadd (t[5], p[9], p[8], n);
    vecadd (t[7], p[9], p[10], n);

    vecaddsub (p[0], t[0], t[0], p[1], n);
    vecadd (p[0], p[0], p[1], n);
    vecsub (p[2], t[2], t[1], n);
    vecadd (p[3], t[2], t[6], n);
    vecadd (p[4], t[2], t[3], n);
    vecadd (p[5], t[4], p[6], n);
    vecadd (t[6], t[7], p[6], n);
    vecsub (t[7], t[5], p[6], n);

    vecaddsub (p[8], p[1], p[3], t[6], n);
    vecaddsub (p[6], p[3], t[0], p[7], n);
    vecaddsub (p[7], p[2], p[2], t[7], n);
    vecaddsub (p[5], p[4], p[4], p[5], n);
}

void wftan16 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint *p[18], *t[22] = {t0, t1, t2, t3, t4, t5, t6, t7,
                             t8, t9, t10, t11, t12, t13, t14,
                             t15, t16, t17, t18, t19, t20, t21};

    for (p[0] = x, k = 1; k < 16; k++)
        p[k] = p[k - 1] + n;

    p[17] = (p[16] = b) + n;

    vecaddsub (t[1], p[12], p[4], p[12], n);
    vecaddsub (t[0], p[4], p[0], p[8], n);
    vecaddsub (t[2], t[3], p[2], p[10], n);
    vecaddsub (t[4], t[5], p[6], p[14], n);
    vecaddsub (t[6], t[7], p[1], p[9], n);
    vecaddsub (t[8], t[9], p[3], p[11], n);
    vecaddsub (t[10], t[11], p[5], p[13], n);
    vecaddsub (t[12], t[13], p[7], p[15], n);

    vecaddsub (t[14], p[3], t[0], t[1], n);
    vecaddsub (t[15], p[11], t[2], t[4], n);
    vecaddsub (t[17], t[18], t[6], t[10], n);
    vecaddsub (t[19], t[20], t[8], t[12], n);
    vecaddsub (p[16], p[8], t[7], t[13], n);
    vecaddsub (p[17], p[9], t[11], t[9], n);

    vecaddsub (t[16], p[2], t[14], t[15], n);
    vecaddsub (t[21], p[10], t[17], t[19], n);

    vecaddsub (p[0], p[1], t[16], t[21], n);
    vecaddsub (p[13], p[5], t[18], t[20], n);
    vecaddsub (p[14], p[6], t[3], t[5], n);

    vecadd (p[7], p[8], p[9], n);
    vecadd (p[15], p[16], p[17], n);

    k = s[0];

    if (k == n)
    {
        for (ma = j = 0; j < 18; j++, ma += m)
            wftas[k] (p[j], w + ma);
    }
    else
    {
        nn = n / k;
        nm = m / ms[0];
        s++;
        ms++;
        for (ma = j = 0; j < 18; j++, ma += m)
            wftan[k] (p[j], w + ma, nn, s, nm, ms);
    }

    vecaddsub (t[0], t[1], p[3], p[5], n);
    vecaddsub (t[2], t[3], p[13], p[11], n);
    vecaddsub (t[4], t[5], p[4], p[6], n);

    vecsub (t[6], p[8], p[7], n);
    vecsub (t[7], p[9], p[7], n);

    vecaddsub (t[8], t[9], t[4], t[6], n);
    vecaddsub (t[10], t[11], t[5], t[7], n);
    vecaddsub (t[12], t[13], p[12], p[14], n);

    vecadd (t[14], p[15], p[16], n);
    vecsub (t[15], p[15], p[17], n);

    vecaddsub (t[16], t[17], t[12], t[14], n);
    vecaddsub (t[18], t[19], t[13], t[15], n);

    veccopy (p[8], p[1], n);

    vecaddsub (p[1], p[15], t[8], t[16], n);
    vecaddsub (p[4], p[12], p[2], p[10], n);
    vecaddsub (p[2], p[14], t[0], t[2], n);
    vecaddsub (p[13], p[3], t[11], t[19], n);
    vecaddsub (p[5], p[11], t[10], t[18], n);
    vecaddsub (p[6], p[10], t[1], t[3], n);
    vecaddsub (p[9], p[7], t[9], t[17], n);
}

void (*wftan[]) (modint x[], modint w[], int n, int s[], int m, int ms[]) =
{0, 0, wftan2, wftan3, wftan4, wftan5, 0, wftan7, wftan8, wftan9, 0, 0, 0, 0, 0, 0, wftan16};

void wfta (modint x[], modint *w[], int nn)
{
    int t, k;

    for (t = 0; t < NALGS; t++)
        if (n[t] == nn) break;

    if (t == NALGS) return;

    k = s[t][0];

    if (k == nn)
        wftas[k] (x, w[t]);
    else
    {
        permute (x, p[t], nn);
        wftan[k] (x, w[t], nn / k, s[t] + 1, m[t] / ms[t][0], ms[t] + 1);
        unpermute (x, ip[t], nn);
    }
}
