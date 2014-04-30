
#ifndef TESTNEWICKRESULT_H
#define TESTNEWICKRESULT_H

#include <iosfwd>
#include <string>

struct TestNewickResult
{
  std::string newick;
  double theta;
  double probability;
  std::string test_name;
  double time;
};

std::ostream& operator<<(std::ostream& os, const TestNewickResult& r);

#endif // TESTNEWICKRESULT_H
