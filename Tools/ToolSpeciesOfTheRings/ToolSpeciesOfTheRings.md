# Species Of The Rings

'Species Of The Rings' is a cellular automaton.

## Algorithm

Each pixel:

 * Is land or mountain
 * If a pixel is land, it is either empty or colonized
 * If a pixel is colonized, the species there has a distance value `d`.

Every timestep:

 * Go through all pixels
   * What is the state of the pixel?
     * If mountain, go to next pixel
     * If empty: 
       * If there are no neighbours (in 4 directions), go to the next pixel
       * Else, pick a random neightbour. The pixel will be occupied by the neighbour and have its distance value with a random mutation. Go to next pixel
     * If colonized: Pick a random neightbour. 
       * If the difference in distance values between focal pixel and neighbour is below a certain threshold, there is a mating: the pixel will be replaced by offspring with the mean distance value plus a random mutation. 
       * Else: add a random mutation to the focal pixel

The random mutation is a value drawn from a normal distribution with mean zero.

The colors denote the distance values, where red is the lowest and purple is the heighest value, following
the colors of the rainbow. This is rescaled every timestep.