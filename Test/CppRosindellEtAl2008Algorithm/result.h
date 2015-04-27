#ifndef RESULT_H
#define RESULT_H

#include <iosfwd>

// results file will contain all the results in rows of 6 entries
struct Result
{
  Result(
    const int area1,
    const int area2,
    const double specset,
    const double L,
    const bool type,
    const double temprichness
  );

  double GetSpeciesRichness() const noexcept { return temprichness; }

  /// 1.) width of survey area
  int area1;
  /// 2.) length of survey area
  int area2;
  /// 3.) speciation rate
  double specset;
  /// 4.) dispersal distance
  double L;
  /// 5.) dispersal kernel type
  bool type;
  /// 6.) species richness result
  double temprichness;
};

std::ostream& operator<<(std::ostream& os,const Result& result);

#endif // RESULT_H
