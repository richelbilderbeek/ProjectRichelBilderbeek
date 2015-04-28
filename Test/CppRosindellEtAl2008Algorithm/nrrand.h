#ifndef NRRAND_H
#define NRRAND_H

class NRrand
{
public:
  NRrand(const int seed) noexcept;
  // returns a uniform random number in (0,1)
  double GetRandomFraction() noexcept;
  // returns an integer between 0 and max
  int GetRandomInt(const int max) noexcept;
  // returns normal deviates
  double GetRandomNormal() noexcept;
private:
  // the last result (for normal deviates)
  double m_lastresult;
  // when doing normal deviates and values are in pairs
  // true when a new pair is needed, false when lastresult can be used
  bool m_normflag;
};

#endif // NRRAND_H
