#include "randomwrap.h"

#include "randomwrap.h"
#include <cstdlib>

RandomWrap::RandomWrap()
{

}
void RandomWrap::set_seed(long seed)
{
  std::srand (seed);
}
double RandomWrap::d01()
{
  return(
    static_cast<double>(std::rand())
    /static_cast<double>(RAND_MAX)
  );
}
