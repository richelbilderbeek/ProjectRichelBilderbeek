#ifndef RANDOMWRAP_H
#define RANDOMWRAP_H

// separate file that contains the random number generator
// it includes instructions for substituting with your own choice
class RandomWrap
{
public:
    RandomWrap();
    void set_seed(long seed);
    double d01();
};
#endif // RANDOMWRAP_H
