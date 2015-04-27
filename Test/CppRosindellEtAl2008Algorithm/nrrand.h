#ifndef NRRAND_H
#define NRRAND_H

class NRrand
{
public:
    // constructor
    NRrand(const long seed);
    // returns a uniform random number in (0,1)
    double GetRandomFraction();
    // returns an integer between 0 and max
    long GetRandomInt(long max);
    // returns normal deviates
    double GetRandomNormal();
private:
    // the last result (for normal deviates)
    double m_lastresult;
    // when doing normal deviates and values are in pairs
    // true when a new pair is needed, false when lastresult can be used
    bool m_normflag;
};

#endif // NRRAND_H
