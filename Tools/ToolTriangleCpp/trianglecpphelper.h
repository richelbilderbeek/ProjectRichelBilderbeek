#ifndef TRIANGLECPPHELPER_H
#define TRIANGLECPPHELPER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <string>
#include <vector>
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/// randomnation()   Generate a random number between 0 and `choices' - 1.
///
/// This is a simple linear congruential random number generator.  Hence, it
/// is a bad random number generator, but good enough for most randomized
/// geometric algorithms.
//int DumbRand(const unsigned int choices);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPHELPER_H
