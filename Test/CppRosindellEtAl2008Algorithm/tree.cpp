#include "tree.h"

#include "array2d.h"
#include "globals.h"
#include <cmath>
#include <boost/numeric/conversion/cast.hpp>

tree::tree()
// initialisor
{
  minspecsetup = 2;
  seeded = false;
  children.clear();
}
void tree::setseed(long theseed)
// set the seed manually (only works once)
// the seed, once set is marked indelibly in the object
// this prevents repeated simulations of the same seed
{
  if (!seeded)
  {
    NR.set_seed(theseed);
    seeded = true;
  }
}
//PRODUCING A COALESCENCE TREE IN CLASS TREE
void tree::maketree(int area1 , int area2 , double minspec , int dispersal , double tol, bool normflag)
{
  // this is the part of the code that actually creates the colescence tree
  // input variables are described in detail below
  // area1 = width of survey area (in trees)
  // area2 = length of survey area (int trees)
  // minspec = smallest speciation rate required
  // dispersal = dispersal distance (dispersal kernel width)
  // tol = tolerance in results (0.01 means 1% error - 0.5% either side)
  // typeflag deals with the type of dispersal in the model (true means normal){
  // setup the internal variables first
  // richness needs to be initialised
  double richness = 0.0;
  // the time interval - ensure this is at least 0
  // a value of 0 gives a basic SAR only for maxintsetup
  // the minimal speciation rate that we are preparing the tree for
  minspecsetup = minspec;
  // data - this will store the coalescence tree itself
  // there can only be a maximum of twice as many nodes as there are
  // initially free branches so we can set the size of our data object
  data.SetSize(2*area1*area2+1);
  enddata = 0; // 0 is reserved as null
  // this means that data is empty and that data[1] is where the first
  // piece of data will be recorded
  for (int tx = 0 ; tx < area1 ; tx++)
  {
    for (int ty = 0 ; ty < area2 ; ty++)
    {
      // looping over the entire survey area
      // setup the data variable
      enddata ++;
      data[enddata].setup(true); // generation number = 1
    }
  }
  // grid - this is an internal variable
  // this is necessary for calculations - initialise it as all zeros
  // it will store integers that refer to places in datapoint array "active"
  int thegridsize = gridsize;
  if (thegridsize < area1*2)
  {
    thegridsize = area1*2;
  }if (thegridsize < area2*2)
  {
    thegridsize = area2*2;
  }
  array2D_Rosindell<unsigned int> grid;
  grid.SetSize(thegridsize,thegridsize);
  for (int i = 0 ; i < thegridsize ; ++i)
  {
    for (int j = 0 ; j < thegridsize ; j++)
    {
      grid[i][j] = 0;
    }
  }
  // "active" stores all the required information for any
  // lineages that have not yet speciated, this is in the
  // form of an array of "datapoint" objects
  array1D<datapoint> active;
  // again we know this array has the same maximum size as "data"
  active.SetSize(2*area1*area2+1);
  // this marks the end of the active vector
  int endactive = 0; // 0 is reserved as null
  for (int tx = 0 ; tx < area1 ; tx++)
  {
    for (int ty = 0 ; ty < area2 ; ty++)
    {
      // looping over the survey area, we initialise both grid and active
      endactive ++;
      active[endactive].setup(tx,ty,endactive);
      grid[tx][ty] = endactive;
      // mpos = endactive - points to the corresponding place in data
    }
  }
  // other variables to be initialised
  //int time = 0;
  int steps = 0;double error = 1000.0;
  // these three variables store information for STRs
  // has a lineage in our survey moved?
  // now do the calculations required to set up the tree
  // loop while error is too large or not included the full time interval
  while (error > (richness*tol))
  {
    // increment steps
    ++steps;
    // choose a random lineage to die and be reborn out of those currently active
    int chosen = NR.i0(endactive-1) + 1; // cannot be 0
    // remember there is no speciation included in this part of the programme
    // choose movement of chosen lineage
    int movex = 0; // will store x direction movement
    int movey = 0; // will store y direction movement
    // typeflag = false square
    // typeflag = true normal
    if (normflag)
    {
      // normally distributed dispersal kernel
      while ((movex == 0)&&(movey == 0))
      {
        // loop to ensure we don't pick a individual to be its own parent
        movex += int(floor((NR.norm()*dispersal)+0.5));
        movey += int(floor((NR.norm()*dispersal)+0.5));
      }
    }
    else
    {
      // square distribtion kernel
      while ((movex == 0)&&(movey == 0)){
        // loop to ensure we don't pick a individual to be its own parent
        movex += (NR.i0(dispersal*2)-dispersal);
        movey += (NR.i0(dispersal*2)-dispersal);
      }
    }
    // note this piece of code can easily be edited for any dispersal kernel
    // record old position of lineage
    int oldx = active[chosen].get_xpos();
    int oldy = active[chosen].get_ypos();
    // update grid to reflect new data
    grid[oldx][oldy] = active[chosen].get_next();
    // if current individual is the only one in the space then it will hold
    // 0 in its data for next and last and this will still be correct
    // the next and last variables indicate the next and last in a ring
    // the ring holds together every individual lineage in the same grid postion
    // of course they would have different indexes and so be in different
    // physical positions. The use of a ring in this way makes
    // it really easy to check if two individuals coalesce
    if (grid[oldx][oldy] > 0)
    {
      // then we have an individual to set its next and last variables correctly
      if ( grid[oldx][oldy] == active[chosen].get_last() )
      {
        // the ring contained 2 individuals
        active[grid[oldx][oldy]].set_last(0);
        active[grid[oldx][oldy]].set_next(0);
      }
      else
      {
        // the ring contained 3 or more individuals
        active[grid[oldx][oldy]].set_last(active[chosen].get_last());
        active[active[chosen].get_last()].set_next(active[chosen].get_next());
      }
    }// now we have completely purged the grid of the old position of our chosen lineage
    active[chosen].set_next(0);
    active[chosen].set_last(0);
    // now actually do the move
    richness += minspec*(active[chosen].get_prob());
    active[chosen].move(movex,movey,minspec);
    data[active[chosen].get_mpos()].inc_steps();
    // record the new position
    int activex = active[chosen].get_xpos();
    int activey = active[chosen].get_ypos();
    // check for coalescence
    if ( grid[activex][activey] == 0)
    {
      // no coalescence possible
      grid[activex][activey] = chosen;
    }
    else
    {
      //coalescence possible
      bool loop = true;
      // check around the ring for coalescence
      int start = grid[activex][activey]; // starting here
      // this is how far around the loop we have got checking for coalescence
      // we start at "start" and then move around methodically
      // the loops usually contain 1 individual but we must allow code for any number
      int current = start;
      while(loop)
      {
        if (active[chosen].get_xindex() == active[current].get_xindex())
        {
          if (active[chosen].get_yindex() == active[current].get_yindex())
          {
            // we have coalescence, update variables// update data
            enddata++;
            data[enddata].setup(false);
            // update data
            data[active[chosen].get_mpos()].set_parent(enddata);
            data[active[current].get_mpos()].set_parent(enddata);
            // update active
            active[current].set_mpos(enddata);
            double tempprob = active[chosen].get_prob();
            tempprob = tempprob + active[current].get_prob()*(1.0-tempprob);
            active[current].set_prob(tempprob);
            active[chosen].setup(active[endactive]);
            int oldx = active[endactive].get_xpos();
            int oldy = active[endactive].get_ypos();
            if (boost::numeric_cast<int>(grid[oldx][oldy]) == endactive)
            {
              grid[oldx][oldy] = chosen;
            }
            if (active[endactive].get_next() >0)
            {
              active[active[endactive].get_next()].set_last(chosen);
              active[active[endactive].get_last()].set_next(chosen);
            }
            endactive --;
            // update grid not necessary as
            // we already purged the old lineage from the grid and loops
            loop = false;
          }
        }
        if (loop)
        {
          // move to the next place in the loop ready for another check
          current = active[current].get_next();
          if (current == 0){
            // the loop was only of size one and there was no coalescence
            // this is most likely
            active[grid[activex][activey]].set_next(chosen);
            active[grid[activex][activey]].set_last(chosen);
            active[chosen].set_next(grid[activex][activey]);
            active[chosen].set_last(grid[activex][activey]);
            loop = false;
          }
          else
          {
            if(current == start)
            {
              // we have made one complete check of the loop and found
              // there was no coalescence but we still have to add the new position in
              int addlast = active[grid[activex][activey]].get_last();
              active[addlast].set_next(chosen);
              active[chosen].set_last(addlast);
              active[chosen].set_next(grid[activex][activey]);
              active[grid[activex][activey]].set_last(chosen);
              loop = false;
            }
          }
        }
      }
    }
    // this peice of code updates the error
    // but only does so every community turnover
    // this is so that not too long is spent on this
    if (steps%(area1*area2*250) == 0)
    {
      // check errors and update
      error = 0.0;
      for (int i = 1 ; i <= endactive ; ++i)
      {error += active[i].get_prob();
      }
    }
  }
}





/************************************************************
TREE OBJECT
************************************************************/
tree::treenode::treenode()
{
}
void tree::treenode::setup(bool root_)
// sets up variables with initial conditions
{
  root = root_;
  parent = 0;
  steps = 0;
}// standard setters
void tree::treenode::set_root(bool root_)
{
  root = root_;
}
void tree::treenode::set_parent(unsigned int x)
{
  parent = x;
}
void tree::treenode::set_steps(unsigned int x)
{
  steps = x;
}
// standard getters
bool tree::treenode::get_root()
{
  return root;
}
unsigned int tree::treenode::get_parent()
{
  return parent;
}
int tree::treenode::get_steps()
{
  return (steps);
}
// increments the steps by one
void tree::treenode::inc_steps()
{
  steps++;
}/************************************************************
DATA POINT (data structure)
************************************************************/
tree::datapoint::datapoint()
{
}
// setup all varibles
void tree::datapoint::setup(unsigned short x , unsigned short y , unsigned int z)
{
  xpos = x;
  ypos = y;
  xindex = 0;
  yindex = 0;
  next = 0;
  last = 0;
  mpos = z;
  prob = 1.0;
}
// setup all varibles from another datapoint
void tree::datapoint::setup(datapoint datin)
{
  xpos = datin.get_xpos();
  ypos = datin.get_ypos();
  xindex = datin.get_xindex();
  yindex = datin.get_yindex();
  next = datin.get_next();
  last = datin.get_last();
  mpos = datin.get_mpos();
  prob = datin.get_prob();
}
// standard setters
void tree::datapoint::set_pos(unsigned short x , unsigned short y){
  xpos = x;
  ypos = y;
}
void tree::datapoint::set_index( short x , short y)
{
  xindex = x;
  yindex = y;
}
void tree::datapoint::set_mpos(unsigned int z)
{
  mpos = z;
}
void tree::datapoint::set_next(unsigned int x)
{
  next = x;
}
void tree::datapoint::set_last(unsigned int x)
{
  last = x;
}
void tree::datapoint::set_prob(double x)
{
  prob = x;
}
// standard getters
unsigned short tree::datapoint::get_xpos()
{
  return xpos;
}unsigned short tree::datapoint::get_ypos()
{
  return ypos;
}
short tree::datapoint::get_xindex()
{
  return xindex;
}
short tree::datapoint::get_yindex()
{
  return yindex;
}
unsigned int tree::datapoint::get_mpos()
{
  return mpos;
}
unsigned int tree::datapoint::get_next()
{
  return next;
}
unsigned int tree::datapoint::get_last()
{
  return last;
}
double tree::datapoint::get_prob()
{
  return prob;
}
// checks for coalescence with another datapoint
bool tree::datapoint::match(datapoint x ){
  bool result = true;
  if (xpos != x.get_xpos()) result = false;
  if (ypos != x.get_ypos()) result = false;
  return result;
}
// update the position of this datapoint
// this implements the indexing system
void tree::datapoint::move(short x , short y , double z)
{
  int newxpos = xpos + x;
  int newypos = ypos + y;
  while (newxpos < 0)
  {
    newxpos += gridsize;
    xindex --;
  }
  while (newxpos >= gridsize)
  {
    newxpos -= gridsize;
    xindex ++;
  }
  while (newypos < 0)
  {
    newypos += gridsize;
    yindex --;
  }
  while (newypos >= gridsize)
  {
    newypos -= gridsize;
    yindex ++;
  }
  xpos = newxpos;
  ypos = newypos;
  // update prob using z = minspec
  prob = prob*(1.0-z);}
/************************************************************
CLASS TREE - THE MAIN CLASS
************************************************************/

/************************************************************
RICHNESS CALCULATION METHODS
************************************************************/
array1D<double> tree::get_richnessint(double spec)
// this returns an interval within which the true mean ricness must lie
{
  array1D<double> result;
  result.SetSize(2);
  result[0] = 0.0;
  result[1] = 0.0;
  if (minspecsetup <= spec)
    // check that the tree was calculated for a small enough speciation rate
    // it is possible to override this check by commenting out if required
  {
    // probarray stores, for each node, a probability that is required in the calculation
    array1D<double> probarray;
    probarray.SetSize(enddata+1);
    for (int i = 1 ; i <= boost::numeric_cast<int>(enddata) ; ++i)
      // loop over all nodes and initialise the relating element in probarray
    {
      if (data[i].get_root() == false)
        // a value of -2.0 indicates an internal node
        // that has thus far not been pruned at all
      {
        probarray[i] = -2.0;
      }
      else
        // a value of 1.0 is assigned to every free branch
        // this is because it is certain that the lineages have not encountered speciaiton// when they are at the very end and no pruning has so far taken place
      {
        probarray[i] = 1.0;
      }
    }
    bool loop = true;
    while (loop)
      // continue looping until we have completed our calculations
    {
      loop = false;
      for (int i = 1 ; i <= boost::numeric_cast<int>(enddata) ; ++i)
      {
        // check to see if that part of the array is complete
        if (probarray[i] >= 0.0)
        {
          // it is complete so use it to complete the info on in its parents
          int theparent = data[i].get_parent();
          if ((probarray[theparent] < 0.0) && (theparent != 0))
          {
            // only do anything if the parents have not already been completed
            loop = true;
            // be sure to go round again if the parents have not been completed
            if (probarray[theparent] <= -1.5)
            {
              // parent not at all complete
              double temprob = (pow(1-spec,double(data[i].get_steps())));
              result[0] += probarray[i]*(1-temprob);
              // we store probabilities as negative in a node if they
              // refer only to one of the two branches of the node
              // we then wait until we have both branches of the node
              // before continuing to complete the full calculation
              probarray[theparent]= -1.0*probarray[i]*temprob;
            }
            else
            {
              // parent partailly complete
              double temprob = (pow(1-spec,double(data[i].get_steps())));// update Smin
              result[0] += probarray[i]*(1-temprob);
              // update the probability array
              temprob = temprob*probarray[i];
              double temprob2 = probarray[theparent]*-1.0;
              probarray[theparent]=(temprob+temprob2-temprob*temprob2);
            }
          }
        }
        else
        {
          // be sure to repeat the loop unless all calculations are fully compelted
          loop = true;
        }
      }
    }
    for (int i = 1 ; i <= boost::numeric_cast<int>(enddata) ; ++i)
    {
      // here we are dealing with all the last branches after prooning all nodes
      if (data[i].get_parent() == 0)
      {
        result[0] += probarray[i]*(1-pow(1-spec,double(data[i].get_steps())));
        result[1] += probarray[i]*pow(1-spec,double(data[i].get_steps()));
      }
    }
    // return the result
    result[1] += result[0];
    return result;
  }
  else
  {
    // return a default error result to indicate
    // the tree was unsutable for the requested calculations
    result[0] = -1.0;
    result[1] = -1.0;
    return result;
  }
}
double tree::get_richness(double spec)
// this returns the midpoint between the maximum and minimum richness estimates
{
  array1D<double> richnessresult = get_richnessint(spec);
  return (richnessresult[0]+richnessresult[1])/2.0;
}
