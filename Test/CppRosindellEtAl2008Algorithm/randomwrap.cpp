#include "randomwrap.h"

#include "randomwrap.h"
#include <stdlib.h>
//#include "Rosindell_etal_2007.h"
using namespace std;
RandomWrap::RandomWrap()
{
}
void RandomWrap::set_seed(long seed)
{
    srand ( seed );
}
double RandomWrap::d01()
{
    return(double(rand())/double(RAND_MAX));
}
