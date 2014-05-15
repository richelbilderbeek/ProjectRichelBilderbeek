#ifndef TRIANGLECPPHELPER_H
#define TRIANGLECPPHELPER_H

#include <string>
#include <vector>

namespace ribi {
namespace tricpp {

/// randomnation()   Generate a random number between 0 and `choices' - 1.
///
/// This is a simple linear congruential random number generator.  Hence, it
/// is a bad random number generator, but good enough for most randomized
/// geometric algorithms.
int DumbRand(const unsigned int choices);

std::vector<std::string> SeperateString(
  const std::string& input,
  const char seperator
);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPHELPER_H
