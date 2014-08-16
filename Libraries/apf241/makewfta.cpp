#include <iostream>
#include <iomanip>
#include <fstream>
#include "ap.h"


using namespace std;


// Program for creating the WFTA tables

// CEXT should be defined in the makefile
#ifndef CEXT
#define CEXT ".cpp"
#endif

const int NALGS = 41;

// W factor tables for prime WFTA components
modint w2[2], w3[3], w4[4], w5[6], w7[9], w8[8], w9[11], w16[18];
modint iw2[2], iw3[3], iw4[4], iw5[6], iw7[9], iw8[8], iw9[11], iw16[18];

modint *wt[] = {0, 0, w2, w3, w4, w5, 0, w7, w8, w9, 0, 0, 0, 0, 0, 0, w16};
modint *iwt[] = {0, 0, iw2, iw3, iw4, iw5, 0, iw7, iw8, iw9, 0, 0, 0, 0, 0, 0, iw16};

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

// Optimized multiplication counts
int mo[] = {0, 2, 1, 5, 6, 4, 10, 12, 12, 13,
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

// Permutation tables
int p6[6], p10[12], p12[12], p18[18], p20[20],
    p24[24], p30[30], p36[36], p40[40], p48[48],
    p60[60], p72[72], p80[80], p84[84], p90[90],
    p120[120], p144[144], p168[168], p180[180], p240[240],
    p252[252], p280[280], p336[336], p360[360], p420[420],
    p504[504], p560[560], p720[720], p840[840], p1008[1008],
    p1260[1260], p1680[1680], p2520[2520], p5040[5040];

int ip6[6], ip10[12], ip12[12], ip18[18], ip20[20],
    ip24[24], ip30[30], ip36[36], ip40[40], ip48[48],
    ip60[60], ip72[72], ip80[80], ip84[84], ip90[90],
    ip120[120], ip144[144], ip168[168], ip180[180], ip240[240],
    ip252[252], ip280[280], ip336[336], ip360[360], ip420[420],
    ip504[504], ip560[560], ip720[720], ip840[840], ip1008[1008],
    ip1260[1260], ip1680[1680], ip2520[2520], ip5040[5040];

int *p[] = {0, 0, 0, 0, p6, 0, 0, p10, p12, 0,
            p18, p20, p24, p30, p36, p40, p48, p60, p72, p80,
            p84, p90, p120, p144, p168, p180, p240, p252, p280, p336,
            p360, p420, p504, p560, p720, p840, p1008, p1260, p1680, p2520,
            p5040};

int *ip[] = {0, 0, 0, 0, ip6, 0, 0, ip10, ip12, 0,
             ip18, ip20, ip24, ip30, ip36, ip40, ip48, ip60, ip72, ip80,
             ip84, ip90, ip120, ip144, ip168, ip180, ip240, ip252, ip280, ip336,
             ip360, ip420, ip504, ip560, ip720, ip840, ip1008, ip1260, ip1680, ip2520,
             ip5040};

// W tables for composite WFTA lengths
modint w6[6], w10[12], w12[12], w18[22], w20[24],
       w24[24], w30[36], w36[44], w40[48], w48[54],
       w60[72], w72[88], w80[108], w84[108], w90[132],
       w120[144], w144[198], w168[216], w180[264], w240[324],
       w252[396], w280[432], w336[486], w360[528], w420[648],
       w504[792], w560[972], w720[1188], w840[1296], w1008[1782],
       w1260[2376], w1680[2916], w2520[4752], w5040[10692];

modint iw6[6], iw10[12], iw12[12], iw18[22], iw20[24],
       iw24[24], iw30[36], iw36[44], iw40[48], iw48[54],
       iw60[72], iw72[88], iw80[108], iw84[108], iw90[132],
       iw120[144], iw144[198], iw168[216], iw180[264], iw240[324],
       iw252[396], iw280[432], iw336[486], iw360[528], iw420[648],
       iw504[792], iw560[972], iw720[1188], iw840[1296], iw1008[1782],
       iw1260[2376], iw1680[2916], iw2520[4752], iw5040[10692];

modint *w[] = {w2, w3, w4, w5, w6, w8, w9, w10, w12, w16,
               w18, w20, w24, w30, w36, w40, w48, w60, w72, w80,
               w84, w90, w120, w144, w168, w180, w240, w252, w280, w336,
               w360, w420, w504, w560, w720, w840, w1008, w1260, w1680, w2520,
               w5040};

modint *iw[] = {iw2, iw3, iw4, iw5, iw6, iw8, iw9, iw10, iw12, iw16,
                iw18, iw20, iw24, iw30, iw36, iw40, iw48, iw60, iw72, iw80,
                iw84, iw90, iw120, iw144, iw168, iw180, iw240, iw252, iw280, iw336,
                iw360, iw420, iw504, iw560, iw720, iw840, iw1008, iw1260, iw1680, iw2520,
                iw5040};

void createpermutetable (int p[], int ip[], int s[], int n)
{
    int k, t, u, v, m[4] = {1, 1, 1, 1}, r[4], j[4];

    for (t = n, k = 0; t > 1; t /= s[k], k++);

    for (t = 0; t < k; t++)
        for (u = 0; u < k; u++)
            if (u != t) m[t] *= s[u];

    for (t = 0; t < k; t++)
        for (u = 1; u < s[t]; u++)
            if (u * m[t] % s[t] == 1)
            {
                r[t] = u;
                break;
            }

    for (t = 0; t < n; t++)
    {
        v = t;
        for (u = k - 1; u >= 0; u--)
        {
            j[u] = v % s[u];
            v /= s[u];
        }

        v = 0;
        for (u = 0; u < k; u++)
            v += r[u] * j[u] * m[u];

        p[t] = v % n;

        v = 0;
        for (u = 0; u < k; u++)
            v += j[u] * m[u];

        ip[t] = v % n;
    }
}

void createpermutetables (void)
{
    int t;

    for (t = 0; t < NALGS; t++)
        if (p[t]) createpermutetable (p[t], ip[t], s[t], n[t]);
}

modint rcos (modint w)
{
    return (w * w + modint (1)) / (w + w);
}

modint isin (modint w)
{
    return (w * w - modint (1)) / (w + w);
}

modint root (modint pr, int n)
{
    // return pow (pr, modint::modulus - 1 - (modint::modulus - 1) / n);
    return pow (pr, (modint::modulus - 1) / n);
}

void createw2table (modint pr, modint w2[], modint iw2[])
{
    w2[0] = iw2[0] = w2[1] = iw2[1] = 1;
}

void createw3table (modint pr, modint w3[], modint iw3[])
{
    modint w, c, s;

    w = root (pr, 3);

    c = rcos (w);
    s = isin (w);

    w3[0] = iw3[0] = 1;
    w3[1] = iw3[1] = c - modint (1);
    w3[2] = -(iw3[2] = s);
}

void createw4table (modint pr, modint w4[], modint iw4[])
{
    modint i;

    i = root (pr, 4);

    w4[0] = iw4[0] = w4[1] = iw4[1] = w4[2] = iw4[2] = 1;
    w4[3] = -(iw4[3] = i);
}

void createw5table (modint pr, modint w5[], modint iw5[])
{
    modint w, c1, c2, s1, s2;

    w = root (pr, 5);

    c1 = rcos (w);
    s1 = isin (w);

    w *= w;

    c2 = rcos (w);
    s2 = isin (w);

    w5[0] = iw5[0] = 1;
    w5[1] = iw5[1] = (c1 + c2) / modint (2) - modint (1);
    w5[2] = iw5[2] = (c1 - c2) / modint (2);
    w5[3] = -(iw5[3] = s1);
    w5[4] = -(iw5[4] = s2 + s1);
    w5[5] = -(iw5[5] = s2 - s1);
}

void createw7table (modint pr, modint w7[], modint iw7[])
{
    modint w, c1, c2, c3, s1, s2, s3;

    w = root (pr, 7);

    c1 = rcos (w);
    s1 = isin (w);

    c2 = rcos (w * w);
    s2 = isin (w * w);

    c3 = rcos (w * w * w);
    s3 = isin (w * w * w);

    w7[0] = iw7[0] = 1;
    w7[1] = iw7[1] = (c1 + c2 + c3) / modint (3) - modint (1);
    w7[2] = iw7[2] = (modint (2) * c1 - c2 - c3) / modint (3);
    w7[3] = iw7[3] = (c1 - modint (2) * c2 + c3) / modint (3);
    w7[4] = iw7[4] = (c1 + c2 - modint (2) * c3) / modint (3);
    w7[5] = -(iw7[5] = (s1 + s2 - s3) / modint (3));
    w7[6] = -(iw7[6] = (modint (2) * s1 - s2 + s3) / modint (3));
    w7[7] = -(iw7[7] = (s1 - modint (2) * s2 - s3) / modint (3));
    w7[8] = -(iw7[8] = (s1 + s2 + modint (2) * s3) / modint (3));
}

void createw8table (modint pr, modint w8[], modint iw8[])
{
    modint w, c, s, i;

    w = root (pr, 8);

    c = rcos (w);
    s = isin (w);

    i = w * w;

    w8[0] = iw8[0] = w8[1] = iw8[1] = w8[2] = iw8[2] = w8[3] = iw8[3] = 1;
    w8[4] = iw8[4] = c;
    w8[5] = -(iw8[5] = i);
    w8[6] = -(iw8[6] = i);
    w8[7] = -(iw8[7] = s);
}

void createw9table (modint pr, modint w9[], modint iw9[])
{
    modint w, c1, c2, c4, s1, s2, s3, s4;

    w = root (pr, 9);

    c1 = rcos (w);
    s1 = isin (w);

    s3 = isin (w * w * w);

    w *= w;

    c2 = rcos (w);
    s2 = isin (w);

    w *= w;

    c4 = rcos (w);
    s4 = isin (w);

    w9[0] = iw9[0] = 1;
    w9[1] = iw9[1] = w9[2] = iw9[2] = modint (1) / modint (2);
    w9[3] = iw9[3] = (c1 - modint (2) * c2 + c4) / modint (3);
    w9[4] = iw9[4] = (c1 + c2 - modint (2) * c4) / modint (3);
    w9[5] = iw9[5] = (modint (2) * c1 - c2 - c4) / modint (3);
    w9[6] = -(iw9[6] = s3);
    w9[7] = -(iw9[7] = s3);
    w9[8] = -(iw9[8] = (s1 + modint (2) * s2 + s4) / modint (3));
    w9[9] = -(iw9[9] = (s2 - s1 + modint (2) * s4) / modint (3));
    w9[10] = -(iw9[10] = (modint (2) * s1 + s2 - s4) / modint (3));
}

void createw16table (modint pr, modint w16[], modint iw16[])
{
    modint w, c1, c2, c3, s1, s2, s3, i;

    w = root (pr, 16);

    c1 = rcos (w);
    s1 = isin (w);

    c2 = rcos (w * w);
    s2 = isin (w * w);

    c3 = rcos (w * w * w);
    s3 = isin (w * w * w);

    w *= w;
    i = w * w;

    w16[0] = iw16[0] = w16[1] = iw16[1] = w16[2] = iw16[2] =
    w16[3] = iw16[3] = w16[4] = iw16[4] = 1;
    w16[5] = iw16[5] = w16[6] = iw16[6] = c2;
    w16[7] = iw16[7] = c3;
    w16[8] = iw16[8] = c3 + c1;
    w16[9] = iw16[9] = c3 - c1;
    w16[10] = -(iw16[10] = i);
    w16[11] = -(iw16[11] = i);
    w16[12] = -(iw16[12] = i);
    w16[13] = -(iw16[13] = s2);
    w16[14] = -(iw16[14] = s2);
    w16[15] = -(iw16[15] = s3);
    w16[16] = -(iw16[16] = s1 - s3);
    w16[17] = -(iw16[17] = s1 + s3);
}

void createswtables (modint pr, modint *wt[], modint *iwt[])
{
    createw2table (pr, wt[2], iwt[2]);
    createw3table (pr, wt[3], iwt[3]);
    createw4table (pr, wt[4], iwt[4]);
    createw5table (pr, wt[5], iwt[5]);
    createw7table (pr, wt[7], iwt[7]);
    createw8table (pr, wt[8], iwt[8]);
    createw9table (pr, wt[9], iwt[9]);
    createw16table (pr, wt[16], iwt[16]);
}

void createwtable (modint d[], modint id[], int i)
{
    int t, k, b, p, q, r;
    modint *c, *ic;

    for (t = n[i], k = 0; t > 1; t /= s[i][k], k++);

    for (t = 0; t < m[i]; t++)
        d[t] = id[t] = 1;

    b = m[i];

    for (t = 0; t < k; t++)
    {
        c = wt[s[i][t]];
        ic = iwt[s[i][t]];

        b /= ms[i][t];

        for (p = 0; p < m[i];)
            for (q = 0; q < ms[i][t]; q++)
                for (r = 0; r < b; r++, p++)
                {
                    d[p] *= c[q];
                    id[p] *= ic[q];
                }
    }
}

void createwtables (modint pr, modint *wt[], modint *iwt[], modint *w[], modint *iw[])
{
    int t, u;

    createswtables (pr, wt, iwt);

    for (t = 0; t < NALGS; t++)
        if (p[t]) createwtable (w[t], iw[t], t);

    // Scale already the values of the inverse transform
    for (t = 0; t < NALGS; t++)
        for (u = 0; u < m[t]; u++) iw[t][u] /= n[t];
}

int main (void)
{
    int l, t, u;

    ofstream o ("wftatab1"CEXT);

    if (o.fail ())
    {
        cerr << "Unable to open file wftatab1"CEXT << endl;
        return 1;
    }

    createpermutetables ();

    o << "// Permutation tables" << endl << "int ";

    for (t = 0; t < NALGS; t++)
        if (p[t])
        {
            o << "p" << n[t] << "[] = {";
            for (u = 0; u < n[t]; u++)
            {
                o << p[t][u] << (u == n[t] - 1 ? "}" : ", ");
                if ((u & 15) == 15 && u != n[t] - 1) o << endl << "    ";
            }
            o << (t == NALGS - 1 ? ";" : ", ") << endl << "    ";
        }

    o << endl << "int ";

    for (t = 0; t < NALGS; t++)
        if (ip[t])
        {
            o << "ip" << n[t] << "[] = {";
            for (u = 0; u < n[t]; u++)
            {
                o << ip[t][u] << (u == n[t] - 1 ? "}" : ", ");
                if ((u & 15) == 15 && u != n[t] - 1) o << endl << "    ";
            }
            o << (t == NALGS - 1 ? ";" : ", ") << endl << "    ";
        }

    o << endl << "int *p" << "[] = {";

    for (t = 0; t < NALGS; t++)
        if (p[t])
            o << "p" << n[t] << (t == NALGS - 1 ? "}" : ", ");
        else
            o << 0 << (t == NALGS - 1 ? "}" : ", ");

    o << ";" << endl;

    o << endl << "int *ip" << "[] = {";

    for (t = 0; t < NALGS; t++)
        if (ip[t])
            o << "ip" << n[t] << (t == NALGS - 1 ? "}" : ", ");
        else
            o << 0 << (t == NALGS - 1 ? "}" : ", ");

    o << ";" << endl;

    for (l = 0; l < 3; l++)
    {
        o.close ();

        switch (l)
        {
            case 0: o.open ("wftatab2"CEXT); break;
            case 1: o.open ("wftatab4"CEXT); break;
            case 2: o.open ("wftatab6"CEXT); break;
        }

        if (o.fail ())
        {
            cerr << "Unable to open file wftatab" << 2 * l + 2 << CEXT << endl;
            return 1;
        }

        o << "#include \"ap.h\"" << endl << endl;

        setmodulus (wftamoduli[l]);
        createwtables (wftaprimitiveroots[l], wt, iwt, w, iw);

        o << endl << "// W factor tables for WFTA for modulus " << l << endl << "rawtype ";

        for (t = 0; t < NALGS; t++)
        {
            o << "w" << n[t] << "_" << l << "[] = {";
            for (u = 0; u < m[t]; u++)
            {
                o << w[t][u] << (u == m[t] - 1 ? "}" : ", ");
                if ((u & 15) == 15 && u != m[t] - 1) o << endl << "         ";
            }
            o << (t == NALGS - 1 ? ";" : ", ") << endl << "         ";
        }

        o << endl << "modint *w_" << l << "[] = {";

        for (t = 0; t < NALGS; t++)
            o << "(modint *) w" << n[t] << "_" << l << (t == NALGS - 1 ? "}" : ", ");

        o << ";" << endl;

        o.close ();

        switch (l)
        {
            case 0: o.open ("wftatab3"CEXT); break;
            case 1: o.open ("wftatab5"CEXT); break;
            case 2: o.open ("wftatab7"CEXT); break;
        }

        if (o.fail ())
        {
            cerr << "Unable to open file wftatab" << 2 * l + 3 << CEXT << endl;
            return 1;
        }

        o << "#include \"ap.h\"" << endl << endl;

        o << endl << "// Inverse W factor tables for WFTA for modulus " << l << endl << "rawtype ";

        for (t = 0; t < NALGS; t++)
        {
            o << "iw" << n[t] << "_" << l << "[] = {";
            for (u = 0; u < m[t]; u++)
            {
                o << iw[t][u] << (u == m[t] - 1 ? "}" : ", ");
                if ((u & 15) == 15 && u != m[t] - 1) o << endl << "         ";
            }
            o << (t == NALGS - 1 ? ";" : ", ") << endl << "         ";
        }

        o << endl << "modint *iw_" << l << "[] = {";

        for (t = 0; t < NALGS; t++)
            o << "(modint *) iw" << n[t] << "_" << l << (t == NALGS - 1 ? "}" : ", ");

        o << ";" << endl;
    }

    clearmodulus ();

    return 0;
}
