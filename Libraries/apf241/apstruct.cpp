#include <cmath>
#include "ap.h"


using namespace std;


// Round up to the nearest power of two or three times a power of two
size_t rnd23up (size_t x)
{
    size_t r = 1;

    if (!x) return 0;

    while (r < x)
    {
        if (r == 1)
            r = 2;
        else if (r == (r & -r))
            r = r / 2 * 3;
        else
            r = r / 3 * 4;
    }

    return r;
}

inline size_t min (size_t a, size_t b)
{
    return (a < b ? a : b);
}

inline size_t max (size_t a, size_t b)
{
    return (a > b ? a : b);
}

// Simply move data from one mantissa to another
void moveblock (apstruct *d, apstruct *s, size_t dpos, size_t spos, size_t len)
{
    size_t l;
    modint *src, *dest;

    while (len)
    {
        l = min (len, Blocksize);
        len -= l;
        src = s->getdata (spos, l);
        dest = d->readydata (dpos, l);
        spos += l;
        dpos += l;

        moveraw (dest, src, l);

        d->putdata ();
        s->cleardata ();
    }
}

// Add data from one mantissa to another
// Return carry
rawtype addblock (apstruct *d, apstruct *s1, apstruct *s2, size_t dpos, size_t s1pos, size_t s2pos, size_t len, rawtype carry)
{
    size_t l;
    modint *src1, *src2, *dest;

    s1pos += len;
    s2pos += len;
    dpos += len;

    while (len)
    {
        l = min (len, Blocksize);
        len -= l;
        s1pos -= l;
        s2pos -= l;
        dpos -= l;
        src1 = s1->getdata (s1pos, l);
        src2 = s2->getdata (s2pos, l);
        dest = d->readydata (dpos, l);

        carry = baseadd ((rawtype *) dest, (rawtype *) src1, (rawtype *) src2, l, carry);

        d->putdata ();
        s2->cleardata ();
        s1->cleardata ();
    }

    return carry;
}

// Subtract data from one mantissa to another
// Return carry
rawtype subblock (apstruct *d, apstruct *s1, apstruct *s2, size_t dpos, size_t s1pos, size_t s2pos, size_t len, rawtype carry)
{
    size_t l;
    modint *src1, *src2, *dest;

    s1pos += len;
    s2pos += len;
    dpos += len;

    while (len)
    {
        l = min (len, Blocksize);
        len -= l;
        s1pos -= l;
        s2pos -= l;
        dpos -= l;
        src1 = s1->getdata (s1pos, l);
        src2 = s2->getdata (s2pos, l);
        dest = d->readydata (dpos, l);

        carry = basesub ((rawtype *) dest, (rawtype *) src1, (rawtype *) src2, l, carry);

        d->putdata ();
        s2->cleardata ();
        s1->cleardata ();
    }

    return carry;
}

// Negate data from one mantissa to another
// Return carry
rawtype negblock (apstruct *d, apstruct *s, size_t dpos, size_t spos, size_t len, rawtype carry)
{
    size_t l;
    modint *src, *dest;

    spos += len;
    dpos += len;

    while (len)
    {
        l = min (len, Blocksize);
        len -= l;
        spos -= l;
        dpos -= l;
        src = s->getdata (spos, l);
        dest = d->readydata (dpos, l);

        carry = basesub ((rawtype *) dest, 0, (rawtype *) src, l, carry);

        d->putdata ();
        s->cleardata ();
    }

    return carry;
}

// Shift data right one modint
void shrblock (apstruct *d, apstruct *s, size_t len, rawtype carry)
{
    modint *dest;

    dest = d->readydata (0, 1);
    dest[0] = carry;
    d->putdata ();

    moveblock (d, s, 1, 0, len);
}

// Shift data left one modint
void shlblock (apstruct *d, apstruct *s, size_t len, rawtype carry)
{
    modint *dest;

    moveblock (d, s, 0, 1, len);

    dest = d->readydata (len, 1);
    dest[0] = carry;
    d->putdata ();
}

// Propagate carries from subtract
// Return carry
rawtype subcarry (apstruct *d, apstruct *s, size_t dpos, size_t spos, size_t len, rawtype carry)
{
    size_t l;
    modint *src, *dest;

    spos += len;
    dpos += len;

    while (len && carry != 0)
    {
        l = min (len, Blocksize);
        len -= l;
        spos -= l;
        dpos -= l;
        src = s->getdata (spos, l);
        dest = d->readydata (dpos, l);

        carry = basesub ((rawtype *) dest, (rawtype *) src, 0, l, carry);

        d->putdata ();
        s->cleardata ();
    }

    if (len) moveblock (d, s, 0, 0, len);

    return carry;
}

// Propagate carries from negation
// Return carry
rawtype negcarry (apstruct *ds, size_t pos, size_t len, rawtype carry)
{
    size_t t, l;
    modint *src;

    pos += len;

    while (len && carry != 0)
    {
        l = min (len, Maxblocksize);
        len -= l;
        pos -= l;
        src = ds->getdata (pos, l);
        for (t = l; t--;)
        {
            if (bigsub ((rawtype *) src + t, &carry, 1) != 0)
            {
                bigadd ((rawtype *) src + t, &Base, 1);
                carry = 1;
            }
            else
            {
                carry = 0;
                break;
            }
        }
        ds->putdata ();
    }

    return carry;
}

// Propagate carries from addition
// Return carry
rawtype addcarry (apstruct *d, apstruct *s, size_t dpos, size_t spos, size_t len, rawtype carry)
{
    size_t l;
    modint *src, *dest;

    spos += len;
    dpos += len;

    while (len && carry != 0)
    {
        l = min (len, Blocksize);
        len -= l;
        spos -= l;
        dpos -= l;
        src = s->getdata (spos, l);
        dest = d->readydata (dpos, l);

        carry = baseadd ((rawtype *) dest, (rawtype *) src, 0, l, carry);

        d->putdata ();
        s->cleardata ();
    }

    if (len) moveblock (d, s, 0, 0, len);

    return carry;
}

// Propagate carries from adding zeros
// Return carry
rawtype poscarry (apstruct *ds, size_t pos, size_t len, rawtype carry)
{
    size_t t, l;
    modint *src;

    pos += len;

    while (len && carry != 0)
    {
        l = min (len, Maxblocksize);
        len -= l;
        pos -= l;
        src = ds->getdata (pos, l);
        for (t = l; t--;)
        {
            if (bigadd ((rawtype *) src + t, &carry, 1) != 0 ||
                bigcmp ((rawtype *) src + t, &Base, 1) >= 0)
            {
                bigsub ((rawtype *) src + t, &Base, 1);
                carry = 1;
            }
            else
            {
                carry = 0;
                break;
            }
        }
        ds->putdata ();
    }

    return carry;
}

// Returns number of trailing zeros
// len is optional number length
size_t lastzeros (apstruct *s, size_t len)
{
    size_t t, l, r = 0;
    modint *src;

    if (len == (size_t) DEFAULT) len = s->size;

    while (len)
    {
        l = min (len, Blocksize);
        len -= l;
        src = s->getdata (len, l);
        t = l;
        while (t-- && (rawtype) src[t] == 0) r++;
        s->cleardata ();
        if (t != (size_t) -1) break;
    }

    return r;
}

// The core of the apfloat addition and subtraction
// Return a new apstruct
apstruct *apaddsub (apstruct *a, apstruct *b, int sub)
{
    size_t t, p, l, r;
    apstruct *ap;
    modint *src, *dest;
    rawtype carry = 0;
    int truebsign, truefunc;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    if (!b->sign)
    {
        a->nlinks++;
        return a;
    }

    if (!a->sign)
    {
        if (sub)
        {
            ap = new apstruct (*b);
            ap->sign = -ap->sign;
            return ap;
        }
        else
        {
            b->nlinks++;
            return b;
        }
    }

    // Now neither a or b is zero

    truebsign = (sub ? -b->sign : b->sign);
    truefunc = (a->sign * truebsign < 0 ? 1 : 0);

    if (a == b)
    {
        if (truefunc)
        {
            // Result is zero
            return new apstruct;
        }
        else
        {
            // Result is 2 * a
            size_t size = a->size;

            p = size;
            ap = new apstruct (a->sign, a->exp, a->prec, p, 0, (p > Maxblocksize ? DISK : MEMORY));

            while (p)
            {
                l = min (p, Blocksize);
                p -= l;
                src = a->getdata (p, l);
                dest = ap->readydata (p, l);

                carry = baseadd ((rawtype *) dest, (rawtype *) src, (rawtype *) src, l, carry);

                ap->putdata ();
                a->cleardata ();
            }

            size -= lastzeros (ap);

            if (carry != 0)
            {
                size++;                         // Precision increases always
                // Avoid unnecessary disk I/O
                apstruct *aptmp = new apstruct (ap->sign, ap->exp + 1, (ap->prec == INFINITE ? INFINITE : ap->prec + 1), size, 0, DEFAULT, 0);  // No fill

                // Shift mantissa
                shrblock (aptmp, ap, size - 1, carry);

                delete ap;
                ap = aptmp;
            }
            else ap->relocate (DEFAULT, size);

            return ap;
        }
    }
    else
    {
        int sign;
        size_t worklen, prec, done;
        long expdiff;
        apstruct *bigger, *smaller;

        if (truefunc)       // True subtract
        {
            int c;
            size_t shift;

            c = apcmp (a, b, 1);    // This *might* do a lot of unnecessary work

            switch (c)
            {
                case 1: bigger = a; smaller = b; sign = a->sign; break;
                case -1: bigger = b; smaller = a; sign = truebsign; break;
                default: return new apstruct;           // Zero
            }

            expdiff = bigger->exp - smaller->exp;
            worklen = max (bigger->size, expdiff + smaller->size);
            prec = min (bigger->prec, (smaller->prec == INFINITE ? INFINITE : expdiff + smaller->prec));

            ap = new apstruct (sign, bigger->exp, prec, worklen, 0, (worklen > Maxblocksize ? DISK : MEMORY));

            done = worklen;

            if (done > (p = expdiff + smaller->size))       // Copy block
            {
                p = done - p;
                done -= p;
                moveblock (ap, bigger, done, done, p);
            }
            else if (done > (p = bigger->size))             // Copy negated block
            {
                p = done - p;
                if (p > done - expdiff)
                    p = done - expdiff;
                done -= p;
                carry = negblock (ap, smaller, done, done - expdiff, p, carry);
            }

            // Subtract
            if (done > (p = expdiff))
            {
                p = done - p;
                done -= p;
                carry = subblock (ap, bigger, smaller, done, done, done - expdiff, p, carry);
            }

            // Propagate last carries
            if (done > (p = bigger->size))
            {
                p = done - p;
                done -= p;
                carry = negcarry (ap, done, p, carry);
            }

            p = done;
            done -= p;
            subcarry (ap, bigger, done, done, p, carry);

            p = worklen;        // Normalize
            r = 0;
            shift = 0;

            while (p)           // Get denormalization
            {
                l = min (p, Blocksize);
                p -= l;
                src = ap->getdata (r, l);
                r += l;
                for (t = 0; t < l; t++, shift++)
                    if ((rawtype) src[t] != 0)
                    {
                        p = 0;
                        break;
                    }
                ap->cleardata ();
            }

            if (shift == worklen || shift >= prec)
            {
                delete ap;
                return new apstruct;            // Zero
            }

            worklen = min (worklen, prec);      // This is bad to do here

            worklen -= lastzeros (ap, worklen);

            if (shift)
            {
                // Avoid unnecessary disk I/O
                apstruct *aptmp = new apstruct (ap->sign, ap->exp - shift, (prec == INFINITE ? INFINITE : prec - shift), worklen - shift, 0, DEFAULT, 0);   // No fill

                // Shift mantissa
                moveblock (aptmp, ap, 0, shift, worklen - shift);

                delete ap;
                ap = aptmp;
            }
            else ap->relocate (DEFAULT, worklen);

            return ap;
        }
        else        // Add the mantissas
        {
            if (a->exp >= b->exp)
            {
                bigger = a;
                smaller = b;
                sign = a->sign;
            }
            else
            {
                bigger = b;
                smaller = a;
                sign = truebsign;
            }

            expdiff = bigger->exp - smaller->exp;
            worklen = max (bigger->size, expdiff + smaller->size);
            prec = min (bigger->prec, (smaller->prec == INFINITE ? INFINITE : expdiff + smaller->prec));

            ap = new apstruct (sign, bigger->exp, prec, worklen, 0, (worklen > Maxblocksize ? DISK : MEMORY));

            done = worklen;

            if (done > (p = expdiff + smaller->size))       // Copy block
            {
                p = done - p;
                done -= p;
                moveblock (ap, bigger, done, done, p);
            }
            else if (done > (p = bigger->size))             // Copy block
            {
                p = done - p;
                if (p > done - expdiff)
                    p = done - expdiff;
                done -= p;
                moveblock (ap, smaller, done, done - expdiff, p);
            }

            // Add
            if (done > (p = expdiff))
            {
                p = done - p;
                done -= p;
                carry = addblock (ap, bigger, smaller, done, done, done - expdiff, p, carry);
            }

            // Propagate last carries
            if (done > (p = bigger->size))
            {
                p = done - p;
                done -= p;
                carry = poscarry (ap, done, p, carry);
            }

            p = done;
            done -= p;
            carry = addcarry (ap, bigger, done, done, p, carry);

            worklen = min (worklen, prec);      // This is bad to do here

            worklen -= lastzeros (ap, worklen);

            if (carry != 0)                     // Shift if overflow
            {
                worklen++;                      // Precision increases always
                // Avoid unnecessary disk I/O
                apstruct *aptmp = new apstruct (ap->sign, ap->exp + 1, (prec == INFINITE ? INFINITE : prec + 1), worklen, 0, DEFAULT, 0);       // No fill

                // Shift mantissa
                shrblock (aptmp, ap, worklen - 1, carry);

                delete ap;
                ap = aptmp;
            } else ap->relocate (DEFAULT, worklen);

            return ap;
        }
    }
}

// The core of the apfloat multiplication
// Return a new apstruct
apstruct *apmul (apstruct *a, apstruct *b)
{
    int i, sign;
    size_t n, prec, size, rsize;
    apstruct *ap;
    size_t trueasize, truebsize;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    sign = a->sign * b->sign;
    if (!sign) return new apstruct;             // Zero

    prec = min (a->prec, b->prec);
    size = min (prec, a->size + b->size);

    trueasize = min (a->size, prec);
    truebsize = min (b->size, prec);

    n = rnd23up (trueasize + truebsize);

    rsize = min (n, size + 2);

    if (a == b)
        ap = autoconvolution (a, rsize, trueasize, n, &i);
    else
        ap = convolution (a, b, rsize, trueasize, truebsize, n, &i);

    size -= lastzeros (ap, size);

    ap->relocate (DEFAULT, size);

    ap->sign = sign;
    ap->prec = prec;
    ap->exp = a->exp + b->exp - 1 + i;

    return ap;
}

// "Medium size" apfloat multiplication, size of b is <= USE_N2_MUL and <= size of a
// Uses the "schoolboy" multiplication scheme, which has n^2 complexity
// Return a new apstruct
apstruct *apmulmedium (apstruct *a, apstruct *b)
{
    int sign;
    size_t t, s, p, l, prec, size, ssize;
    apstruct *ap;
    modint *f, *src, *dest;
    rawtype carry, tmpdest[USE_N2_MUL];
    modint tmpf[USE_N2_MUL];

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    sign = a->sign * b->sign;
    if (!sign) return new apstruct;             // Zero

    for (s = 0; s < b->size; s++)
        tmpdest[s] = 0;

    if (b->location == MEMORY)
    {
        f = b->getdata (0, b->size);            // Pointer to a persistent memory address
        b->cleardata ();                        // Now we know that f is not invalidated
    }
    else
    {
        src = b->getdata (0, b->size);

        for (s = 0; s < b->size; s++)           // Create a copy of b in case a and b are the same
            tmpf[s] = src[s];

        f = tmpf;

        b->cleardata ();
    }

    prec = min (a->prec, b->prec);
    size = min (prec, a->size + b->size - 1);

    ssize = min (prec + b->size - 1, a->size + b->size - 1);

    ap = new apstruct (sign, a->exp + b->exp - 1, prec, ssize, 0, (ssize > Maxblocksize ? DISK : MEMORY));

    p = ssize - b->size + 1;

    while (p)
    {
        l = min (p, Blocksize);
        p -= l;
        src = a->getdata (p, l);
        dest = ap->readydata (p + b->size - 1, l);
        for (t = l; t--;)
        {
            carry = basemuladd (tmpdest, (rawtype *) f, tmpdest, (rawtype) src[t], b->size, 0);

            dest[t] = tmpdest[b->size - 1];
            for (s = b->size - 1; s--;)
                tmpdest[s + 1] = tmpdest[s];
            tmpdest[0] = carry;
        }
        ap->putdata ();
        a->cleardata ();
    }

    dest = ap->readydata (0, b->size - 1);

    for (s = b->size - 1; s--;)
        dest[s] = tmpdest[s + 1];

    ap->putdata ();

    size -= lastzeros (ap, size);

    if (carry != 0)                 // Shift if overflow
    {
        if (prec > size) size++;
        // Avoid unnecessary disk I/O
        apstruct *aptmp = new apstruct (sign, ap->exp + 1, prec, size, 0, DEFAULT, 0);  // No fill

        // Shift mantissa
        shrblock (aptmp, ap, size - 1, carry);

        delete ap;
        ap = aptmp;

        size -= lastzeros (ap);
    }

    ap->relocate (DEFAULT, size);

    return ap;
}

// "Short" apfloat multiplication, size of b is 1
// Return a new apstruct
apstruct *apmulshort (apstruct *a, apstruct *b)
{
    int sign;
    size_t p, l, prec, size;
    rawtype f;
    apstruct *ap;
    modint *src, *dest;
    rawtype carry = 0;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    sign = a->sign * b->sign;
    if (!sign) return new apstruct;             // Zero

    assert (b->size == 1);                      // For trapping bugs

    src = b->getdata (0, 1);
    f = src[0];
    b->cleardata ();

    prec = min (a->prec, b->prec);
    size = min (prec, a->size);

    p = size;

    ap = new apstruct (sign, a->exp + b->exp - 1, prec, p, 0, (p > Maxblocksize ? DISK : MEMORY));

    if (f != 1)
    {
        while (p)
        {
            l = min (p, Blocksize);
            p -= l;
            src = a->getdata (p, l);
            dest = ap->readydata (p, l);

            carry = basemuladd ((rawtype *) dest, (rawtype *) src, 0, f, l, carry);

            ap->putdata ();
            a->cleardata ();
        }

        size -= lastzeros (ap);

        if (carry != 0)                 // Shift if overflow
        {
            if (prec > size) size++;
            // Avoid unnecessary disk I/O
            apstruct *aptmp = new apstruct (sign, ap->exp + 1, prec, size, 0, DEFAULT, 0);  // No fill

            // Shift mantissa
            shrblock (aptmp, ap, size - 1, carry);

            delete ap;
            ap = aptmp;

            size -= lastzeros (ap);
        }
    }
    else
    {
        moveblock (ap, a, 0, 0, p);
    }

    ap->relocate (DEFAULT, size);

    return ap;
}

// "Short" apfloat division, size of b is 1
// Return a new apstruct
apstruct *apdivshort (apstruct *a, apstruct *b)
{
    int sign;
    size_t t, p, l, r, prec, getsize, ressize;
    rawtype f;
    apstruct *ap;
    modint *src, *dest;
    rawtype tmp, tmp1[2] = {0}, tmp2[2] = {0}, carry = 0;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    assert (b->sign);                           // Infinity

    sign = a->sign * b->sign;
    if (!sign) return new apstruct;             // Zero

    assert (b->size == 1);

    src = b->getdata (0, 1);
    f = src[0];
    b->cleardata ();

    prec = min (a->prec, b->prec);
    getsize = min (prec, a->size);

    if (f != 1)
    {
        // Check for finite or infinite result sequence
        tmp1[0] = f;
        for (t = 0; t < NBasefactors; t++)
            while (bigdiv (tmp2, tmp1, Basefactors[t], 1) == 0) tmp1[0] = tmp2[0];
        if (tmp1[0] != 1)
        {
            // Infinite nonzero sequence
            ressize = prec;
        }
        else
        {
            // Calculate maximum sequence length
            carry = 1;
            for (t = 0; carry != 0; t++)
            {
                tmp1[1] = bigmul (tmp1, &carry, Base, 1);
                carry = bigdiv (tmp1, tmp1, f, 2);
            }
            ressize = min (prec, getsize + t);
        }

        ap = new apstruct (sign, a->exp - b->exp + 1, prec, ressize, 0, (ressize > Maxblocksize ? DISK : MEMORY), 0);   // No fill

        p = getsize;
        r = 0;

        while (p)
        {
            l = min (p, Blocksize);
            p -= l;
            src = a->getdata (r, l);
            dest = ap->readydata (r, l);
            r += l;

            carry = basediv ((rawtype *) dest, (rawtype *) src, f, l, carry);

            ap->putdata ();
            a->cleardata ();
        }

        p = ressize - getsize;

        src = a->getdata (0, 1);
        tmp = src[0];
        a->cleardata ();

        if (tmp < f)
        {
            // Avoid unnecessary disk I/O
            apstruct *aptmp = new apstruct (sign, ap->exp - 1, prec, ressize, 0, DEFAULT, 0);   // No fill

            tmp1[1] = bigmul (tmp1, &carry, Base, 1);
            carry = bigdiv (tmp1, tmp1, f, 2);

            // Shift mantissa
            shlblock (aptmp, ap, getsize - 1, tmp1[0]);

            delete ap;
            ap = aptmp;
        }

        while (p)
        {
            l = min (p, Maxblocksize);
            p -= l;
            dest = ap->readydata (r, l);
            r += l;

            carry = basediv ((rawtype *) dest, 0, f, l, carry);

            ap->putdata ();
        }
    }
    else
    {
        ap = new apstruct (sign, a->exp - b->exp + 1, prec, getsize, 0, (getsize > Maxblocksize ? DISK : MEMORY), 0);   // No fill

        moveblock (ap, a, 0, 0, getsize);
    }

    ap->relocate (DEFAULT, ap->size - lastzeros (ap));

    return ap;
}

// Apfloat comparison
// Return 1 if a > b
//       -1 if a < b
//        0 if a == b
int apcmp (apstruct *a, apstruct *b, int absolute)
{
    size_t m, t, p, l, r;
    modint *da, *db;
    int trueasign, truebsign;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    if (a == b) return 0;       // Same number

    if (absolute)
    {
        trueasign = abs (a->sign);
        truebsign = abs (b->sign);
    }
    else
    {
        trueasign = a->sign;
        truebsign = b->sign;
    }

    if (trueasign < truebsign) return -1;
    else if (trueasign > truebsign) return 1;

    if (trueasign < 0)
    {
        if (a->exp < b->exp) return 1;
        else if (a->exp > b->exp) return -1;
    }
    else if (trueasign > 0)
    {
        if (a->exp < b->exp) return -1;
        else if (a->exp > b->exp) return 1;
    }

    p = m = min (a->size, b->size);
    r = 0;

    while (p)
    {
        l = min (p, Blocksize);
        p -= l;
        da = a->getdata (r, l);
        db = b->getdata (r, l);
        r += l;
        for (t = 0; t < l; t++)
        {
            if ((rawtype) da[t] < (rawtype) db[t])
            {
                a->cleardata ();
                b->cleardata ();
                return -trueasign;
            }
            else if ((rawtype) da[t] > (rawtype) db[t])
            {
                a->cleardata ();
                b->cleardata ();
                return trueasign;
            }
        }
        a->cleardata ();
        b->cleardata ();
    }

    if (a->size > m)
        return trueasign;
    else if (b->size > m)
        return -trueasign;

    return 0;
}

// Convert apfloat to double
double ap2double (apstruct *a)
{
    size_t doubledigits = (size_t) (log (MAX_PRECISE_DOUBLE) / log ((double) Basedigit)),     // Approximate accuracy of a double
           size = (doubledigits + 2 * Basedigits - 2) / Basedigits;
    modint *data;
    double i = 0.0;

    assert (a);                 // Won't work on uninitialized apfloats

    if (!a->sign) return 0.0;

    size = min (size, a->size);

    data = a->getdata (0, size);

    while (size--)
    {
        i += (double) (rawtype) data[size];
        i /= Base;
    }

    a->cleardata ();

    return a->sign * i * pow ((double) Base, (double) a->exp);
}

// Convert apfloat to rawtype
// The apfloat must be integer with size one
rawtype ap2rawtype (apstruct *a)
{
    rawtype r;

    assert (a);                 // Won't work on uninitialized apfloats

    if (a->sign)
    {
        assert (a->size == 1);
        assert (a->exp == 1);

        modint *data = a->getdata (0, 1);
        r = (rawtype) data[0];
        a->cleardata ();
    }
    else
    {
        r = 0;
    }

    return r;
}

// Rounds down in _absolute value_ an apfloat to the nearest integer
// Returns a new apstruct
apstruct *apabsfloor (apstruct *a)
{
    size_t size;
    apstruct *ap;

    assert (a);                 // Won't work on uninitialized apfloats

    if (!a->sign || a->exp <= 0)
        return new apstruct;                            // Zero

    size = min (a->exp, a->size);                       // Size of integer part

    size -= lastzeros (a, size);

    ap = new apstruct (a->sign, a->exp, INFINITE, size, 0, DEFAULT, 0);         // No fill

    moveblock (ap, a, 0, 0, size);

    return ap;
}

// Rounds up in _absolute value_ an apfloat to the nearest integer
// Assumes that the input is normalized and has nonzero last digit (=base unit)
// Returns a new apstruct
apstruct *apabsceil (apstruct *a)
{
    size_t size;
    rawtype carry;
    apstruct *ap;

    assert (a);                 // Won't work on uninitialized apfloats

    if (!a->sign)
        return new apstruct;                            // Zero

    if (a->exp <= 0)                                    // Result is 1 (or -1)
    {
        modint *data = new modint[1];

        data[0] = (rawtype) 1;

        return new apstruct (a->sign, 1, INFINITE, 1, data, DEFAULT);
    }

    // Check if the fractional part is nonzero
    if (a->size > a->exp)
        carry = 1;
    else
        carry = 0;

    size = min (a->exp, a->size);                       // Size of integer part

    if (carry == 0)                                     // Simply truncate
    {
        size -= lastzeros (a, size);

        ap = new apstruct (a->sign, a->exp, INFINITE, size, 0, DEFAULT, 0);     // No fill

        moveblock (ap, a, 0, 0, size);

        return ap;
    }

    ap = new apstruct (a->sign, a->exp, INFINITE, size, 0, (size > Maxblocksize ? DISK : MEMORY));

    // Add 1 to the integer part
    carry = addcarry (ap, a, 0, 0, size, carry);

    size -= lastzeros (ap);

    if (carry != 0)
    {
        size++;

        // Avoid unnecessary disk I/O
        apstruct *aptmp = new apstruct (ap->sign, ap->exp + 1, ap->prec, size, 0, DEFAULT, 0);  // No fill

        // Shift mantissa
        shrblock (aptmp, ap, size - 1, carry);

        delete ap;
        ap = aptmp;
    }
    else ap->relocate (DEFAULT, size);

    return ap;
}

// Apfloat comparison (for AGM)
// Return the number of matching _base units_
size_t apeq (apstruct *a, apstruct *b)
{
    size_t t, p, l, r;
    modint *da, *db;

    assert (a);                 // Won't work on uninitialized apfloats
    assert (b);

    if (a->sign != b->sign) return 0;           // No match

    if (!a->sign) return INFINITE;              // Both zero

    if (a->exp != b->exp) return 0;             // No match

    if (a == b) return a->prec;                 // Same number

    p = min (a->size, b->size);
    r = 0;

    while (p)
    {
        l = min (p, Blocksize);
        p -= l;
        da = a->getdata (r, l);
        db = b->getdata (r, l);

        for (t = 0; t < l; t++, r++)
            if ((rawtype) da[t] != (rawtype) db[t])
            {
                a->cleardata ();
                b->cleardata ();
                return r;
            }

        a->cleardata ();
        b->cleardata ();
    }

    p = max (min (a->size, b->prec), min (a->prec, b->size));

    if (a->size > r)
    {
        p = min (a->size, p) - r;

        while (p)
        {
            l = min (p, Blocksize);
            p -= l;
            da = a->getdata (r, l);

            for (t = 0; t < l; t++, r++)
                if ((rawtype) da[t] != 0)
                {
                    a->cleardata ();
                    return r;
                }

            a->cleardata ();
        }
    }
    else if (b->size > r)
    {
        p = min (b->size, p) - r;

        while (p)
        {
            l = min (p, Blocksize);
            p -= l;
            db = b->getdata (r, l);

            for (t = 0; t < l; t++, r++)
                if ((rawtype) db[t] != 0)
                {
                    b->cleardata ();
                    return r;
                }

            b->cleardata ();
        }
    }

    return min (a->prec, b->prec);
}

typedef struct
{
    size_t size;
    size_t prec;
    long exp;
    int sign;
} apdiskheader;

// Read apstruct from file
// Returns a new apstruct
apstruct *apswapfrom (const char *filename)
{
    apstruct *ap = new apstruct ();
    apdiskheader h;

    ap->capture (filename);

    fstream &fs = ap->openstream ();
    fs.seekg (- (int) sizeof (h), ios::end);
    fs.read ((char *) &h, sizeof (h));
    assert (fs.good ());
    ap->closestream ();

    ap->prec = h.prec;
    ap->exp = h.exp;
    ap->sign = h.sign;
    ap->relocate (DEFAULT, h.size);

    return ap;
}

// Writes apstruct to file
// Deletes a
void apswapto (apstruct *a, const char *filename)
{
    apdiskheader h;

    assert (a);

    h.prec = a->prec;
    h.exp = a->exp;
    h.sign = a->sign;
    h.size = a->size;

    a->relocate (DISK);

    fstream &fs = a->openstream ();
    fs.seekp (0, ios::end);
    fs.write ((char *) &h, sizeof (h));
    assert (fs.good ());
    a->closestream ();

    a->release (filename);

    delete a;
}
