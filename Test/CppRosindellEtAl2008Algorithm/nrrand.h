#ifndef NRRAND_H
#define NRRAND_H

class NRrand
{
public:
    // constructor
    NRrand(const long seed);
    // returns a uniform random number in (0,1)
    double d01();
    // returns an integer between 0 and max
    long i0(long max);
    // returns normal deviates
    double norm();
private:
    // the last result (for normal deviates)
    double lastresult;
    // when doing normal deviates and values are in pairs
    // true when a new pair is needed, false when lastresult can be used
    bool normflag;
};

#endif // NRRAND_H
