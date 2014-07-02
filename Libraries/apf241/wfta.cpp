#include "ap.h"


// Optimized but not-so-good performance WFTA routines

const int NALGS = 41;

const int B16 = 315;
const int B9 = 35;
const int B8 = 315;
const int B7 = 5;
const int B5 = 1;
const int B4 = 315;
const int B3 = 560;
const int B2 = 45;

const int MAXN = 5040;

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

#if defined (USEASMGCC386)

extern "C"
{
void wfta2 (modint x[], modint w[]);
void wfta3 (modint x[], modint w[]);
void wfta4 (modint x[], modint w[]);
void wfta5 (modint x[], modint w[]);
/*
void wfta7 (modint x[], modint w[]);
void wfta8 (modint x[], modint w[]);
void wfta9 (modint x[], modint w[]);
void wfta16 (modint x[], modint w[]);
*/
void wftan2 (modint x[], modint w[], int n, int s[], int m, int ms[]);
void wftan3 (modint x[], modint w[], int n, int s[], int m, int ms[]);
/*
void wftan4 (modint x[], modint w[], int n, int s[], int m, int ms[]);
void wftan5 (modint x[], modint w[], int n, int s[], int m, int ms[]);
void wftan7 (modint x[], modint w[], int n, int s[], int m, int ms[]);
void wftan8 (modint x[], modint w[], int n, int s[], int m, int ms[]);
void wftan9 (modint x[], modint w[], int n, int s[], int m, int ms[]);
void wftan16 (modint x[], modint w[], int n, int s[], int m, int ms[]);
*/
}

#else

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

#endif

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

#if !defined (USEASMGCC386)

void wftan2 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, nn, nm;
    modint t0, t1;
    modint *p;

    p = x + n;

    for (k = 0; k < n; k++)
    {
        t0 = x[k];
        t1 = p[k];
        x[k] = t0 + t1;
        p[k] = t0 - t1;
    }

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
    modint t0, t1, t2;
    modint *p[3];

    p[2] = (p[1] = (p[0] = x) + n) + n;

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t0 = t1 + t2;
        p[0][k] += t0;
        p[1][k] = t0;
        p[2][k] = t1 - t2;
    }

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

    for (k = 0; k < n; k++)
    {
        t0 = p[0][k] + p[1][k];
        t1 = p[2][k];
        p[1][k] = t0 + t1;
        p[2][k] = t0 - t1;
    }
}

#endif

void wftan4 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, na, ma;
    modint t0, t1, t2, t3;
    modint r0, r1;
    modint *p[4];

    p[3] = (p[2] = (p[1] = (p[0] = x) + n) + n) + n;

    for (k = 0; k < n; k++)
    {
        t0 = p[0][k];
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        r0 = t0 + t2;
        r1 = t1 + t3;
        p[0][k] = r0 + r1;
        p[1][k] = r0 - r1;
        p[2][k] = t0 - t2;
        p[3][k] = t1 - t3;
    }

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

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        p[1][k] = t2 + t3;
        p[3][k] = t2 - t3;
        p[2][k] = t1;
    }
}

void wftan5 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint t0, t1, t2, t3, t4, t5;
    modint r0, r1, r2, r3, r4;
    modint *p[6], b[B5];

    for (p[0] = x, k = 1; k < 5; k++)
        p[k] = p[k - 1] + n;

    p[5] = b;

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        r0 = t1 + t4;
        r2 = t1 - t4;
        r1 = t3 + t2;
        r3 = t3 - t2;
        r4 = r0 + r1;
        p[0][k] += r4;
        p[1][k] = r4;
        p[2][k] = r0 - r1;
        p[3][k] = r2 + r3;
        p[4][k] = r3;
        p[5][k] = r2;
    }

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

    for (k = 0; k < n; k++)
    {
        t0 = p[0][k];
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        r0 = t0 + t1;
        r1 = r0 + t2;
        r3 = r0 - t2;
        r2 = t3 - t4;
        r4 = t3 + t5;
        p[1][k] = r1 + r2;
        p[4][k] = r1 - r2;
        p[2][k] = r3 + r4;
        p[3][k] = r3 - r4;
    }
}

void wftan7 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint t0, t1, t2, t3, t4, t5, t6, t7, t8;
    modint r0, r1, r2, r3, r4, r5, r6;
    modint *p[9], b[2 * B7];

    for (p[0] = x, k = 1; k < 7; k++)
        p[k] = p[k - 1] + n;

    p[8] = (p[7] = b) + n;

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        r0 = t1 + t6;
        r4 = t1 - t6;
        r1 = t2 + t5;
        r5 = t2 - t5;
        r2 = t4 + t3;
        r6 = t4 - t3;
        r3 = r0 + r1 + r2;
        p[0][k] += r3;
        p[1][k] = r3;
        p[2][k] = r0 - r2;
        p[3][k] = r2 - r1;
        p[4][k] = r1 - r0;
        p[5][k] = r4 + r5 + r6;
        p[6][k] = r4 - r6;
        p[7][k] = r6 - r5;
        p[8][k] = r5 - r4;
    }

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

    for (k = 0; k < n; k++)
    {
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        t8 = p[8][k];
        r0 = p[0][k] + p[1][k];
        r1 = r0 + t2 + t3;
        r2 = r0 - t2 - t4;
        r3 = r0 - t3 + t4;
        r4 = t5 + t6 + t7;
        r5 = t5 - t6 - t8;
        r6 = t5 - t7 + t8;
        p[1][k] = r1 + r4;
        p[6][k] = r1 - r4;
        p[2][k] = r2 + r5;
        p[5][k] = r2 - r5;
        p[4][k] = r3 + r6;
        p[3][k] = r3 - r6;
    }
}

void wftan8 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint t0, t1, t2, t3, t4, t5, t6, t7;
    modint r0, r1, r2, r3, r4, r5, r6, r7;
    modint *p[8];

    for (p[0] = x, k = 1; k < 8; k++)
        p[k] = p[k - 1] + n;

    for (k = 0; k < n; k++)
    {
        t0 = p[0][k];
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        r0 = t0 + t4;
        r1 = t2 + t6;
        r2 = t1 + t5;
        r3 = t1 - t5;
        r4 = t3 + t7;
        r5 = t3 - t7;
        r6 = r0 + r1;
        r7 = r2 + r4;
        p[0][k] = r6 + r7;
        p[1][k] = r6 - r7;
        p[2][k] = r0 - r1;
        p[3][k] = t0 - t4;
        p[5][k] = r2 - r4;
        p[6][k] = t2 - t6;
        p[7][k] = r3 + r5;
        p[4][k] = r3 - r5;
    }

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

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        r0 = t3 + t4;
        r1 = t3 - t4;
        r2 = t6 + t7;
        r3 = t6 - t7;
        p[4][k] = t1;
        p[1][k] = r0 + r2;
        p[7][k] = r0 - r2;
        p[2][k] = t2 + t5;
        p[6][k] = t2 - t5;
        p[5][k] = r1 + r3;
        p[3][k] = r1 - r3;
    }
}

void wftan9 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    modint r0, r1, r2, r3, r4, r5, r6, r7;
    modint q0, q1, q2, q3, q4, q5, q6, q7;
    modint *p[11], b[2 * B9];

    for (p[0] = x, k = 1; k < 9; k++)
        p[k] = p[k - 1] + n;

    p[10] = (p[9] = b) + n;

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        t8 = p[8][k];
        r0 = t8 + t1;
        r7 = t8 - t1;
        r1 = t7 + t2;
        r6 = t7 - t2;
        r2 = t6 + t3;
        r5 = t6 - t3;
        r3 = t5 + t4;
        r4 = t5 - t4;
        p[2][k] = r2;
        p[1][k] = r0 + r1 + r3;
        p[3][k] = r0 - r3;
        p[4][k] = r1 - r3;
        p[5][k] = r0 - r1;
        p[6][k] = r5;
        p[7][k] = r7 - r6 + r4;
        p[8][k] = r7 - r4;
        p[9][k] = r4 + r6;
        p[10][k] = r7 + r6;
    }

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

    for (k = 0; k < n; k++)
    {
        t0 = p[0][k];
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        t8 = p[8][k];
        t9 = p[9][k];
        t10 = p[10][k];
        r0 = t2 + t2 + t0;
        r2 = t0 - t2;
        r1 = t3 + t4;
        r3 = t3 - t5;
        r6 = t4 + t5;
        r4 = t8 - t10;
        r5 = t9 + t8;
        r7 = t9 + t10;
        q0 = r0 + t1 + t1;
        q1 = r0 - t1;
        q2 = r2 - r1;
        q4 = r2 + r3;
        q3 = r6 + r2;
        q5 = r4 + t6;
        q6 = r7 + t6;
        q7 = r5 - t6;
        p[0][k] = q0;
        p[8][k] = q3 + q6;
        p[1][k] = q3 - q6;
        p[7][k] = q2 + q7;
        p[2][k] = q2 - q7;
        p[6][k] = q1 + t7;
        p[3][k] = q1 - t7;
        p[5][k] = q4 + q5;
        p[4][k] = q4 - q5;
    }
}

void wftan16 (modint x[], modint w[], int n, int s[], int m, int ms[])
{
    int k, j, nn, nm, ma;
    modint t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17;
    modint r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
           r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25;
    modint *p[18], b[2 * B16];

    for (p[0] = x, k = 1; k < 16; k++)
        p[k] = p[k - 1] + n;

    p[17] = (p[16] = b) + n;

    for (k = 0; k < n; k++)
    {
        t0 = p[0][k];
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        t8 = p[8][k];
        t9 = p[9][k];
        t10 = p[10][k];
        t11 = p[11][k];
        t12 = p[12][k];
        t13 = p[13][k];
        t14 = p[14][k];
        t15 = p[15][k];
        r0 = t0 + t8;
        r1 = t4 + t12;
        r2 = t2 + t10;
        r3 = t2 - t10;
        r4 = t6 + t14;
        r5 = t6 - t14;
        r6 = t1 + t9;
        r7 = t1 - t9;
        r8 = t3 + t11;
        r9 = t3 - t11;
        r10 = t5 + t13;
        r11 = t5 - t13;
        r12 = t7 + t15;
        r13 = t7 - t15;
        r14 = r0 + r1;
        r15 = r2 + r4;
        r16 = r14 + r15;
        r17 = r6 + r10;
        r18 = r6 - r10;
        r19 = r8 + r12;
        r20 = r8 - r12;
        r21 = r17 + r19;
        r22 = r7 + r13;
        r23 = r7 - r13;
        r24 = r11 + r9;
        r25 = r11 - r9;

        p[0][k] = r16 + r21;
        p[1][k] = r16 - r21;
        p[2][k] = r14 - r15;
        p[3][k] = r0 - r1;
        p[4][k] = t0 - t8;
        p[13][k] = r18 + r20;
        p[5][k] = r18 - r20;
        p[14][k] = r3 + r5;
        p[6][k] = r3 - r5;
        p[7][k] = r23 + r25;
        p[8][k] = r23;
        p[9][k] = r25;
        p[10][k] = r17 - r19;
        p[11][k] = r2 - r4;
        p[12][k] = t4 - t12;
        p[15][k] = r22 + r24;
        p[16][k] = r22;
        p[17][k] = r24;
    }

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

    for (k = 0; k < n; k++)
    {
        t1 = p[1][k];
        t2 = p[2][k];
        t3 = p[3][k];
        t4 = p[4][k];
        t5 = p[5][k];
        t6 = p[6][k];
        t7 = p[7][k];
        t8 = p[8][k];
        t9 = p[9][k];
        t10 = p[10][k];
        t11 = p[11][k];
        t12 = p[12][k];
        t13 = p[13][k];
        t14 = p[14][k];
        t15 = p[15][k];
        t16 = p[16][k];
        t17 = p[17][k];

        r0 = t3 + t5;
        r1 = t3 - t5;
        r2 = t13 + t11;
        r3 = t13 - t11;
        r4 = t4 + t6;
        r5 = t4 - t6;
        r6 = t8 - t7;
        r7 = t9 - t7;
        r8 = r4 + r6;
        r9 = r4 - r6;
        r10 = r5 + r7;
        r11 = r5 - r7;
        r12 = t12 + t14;
        r13 = t12 - t14;
        r14 = t15 + t16;
        r15 = t15 - t17;
        r16 = r12 + r14;
        r17 = r12 - r14;
        r18 = r13 + r15;
        r19 = r13 - r15;

        p[8][k] = t1;
        p[1][k] = r8 + r16;
        p[15][k] = r8 - r16;
        p[2][k] = r0 + r2;
        p[14][k] = r0 - r2;
        p[13][k] = r11 + r19;
        p[3][k] = r11 - r19;
        p[4][k] = t2 + t10;
        p[12][k] = t2 - t10;
        p[5][k] = r10 + r18;
        p[11][k] = r10 - r18;
        p[6][k] = r1 + r3;
        p[10][k] = r1 - r3;
        p[9][k] = r9 + r17;
        p[7][k] = r9 - r17;
    }
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
