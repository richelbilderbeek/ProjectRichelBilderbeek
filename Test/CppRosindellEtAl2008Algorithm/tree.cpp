#include "tree.h"

#include <cassert>
#include <cmath>
#include <boost/numeric/conversion/cast.hpp>

#include "treedatapoint.h"

Tree::Tree(const int seed)
  :
    m_minspecsetup{2},
    m_rnd(seed)
{

}


//PRODUCING A COALESCENCE TREE IN CLASS TREE
void Tree::maketree(
  const int area1,
  const int area2,
  const double minspec,
  const int dispersal,
  const double tol,
  const bool normflag)
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
  m_minspecsetup = minspec;
  // data - this will store the coalescence tree itself
  // there can only be a maximum of twice as many nodes as there are
  // initially free branches so we can set the size of our data object
  m_nodes.resize(2*area1*area2+1,TreeNode(true));
  m_enddata = 0; // 0 is reserved as null
  // this means that data is empty and that data[1] is where the first
  // piece of data will be recorded
  for (int tx = 0 ; tx < area1 ; tx++)
  {
    for (int ty = 0 ; ty < area2 ; ty++)
    {
      // looping over the entire survey area
      // setup the data variable
      ++m_enddata;
      assert(m_enddata >= 0);
      assert(m_enddata < static_cast<int>(m_nodes.size()));
      m_nodes[m_enddata] = TreeNode(true); // generation number = 1
    }
  }
  // grid - this is an internal variable
  // this is necessary for calculations - initialise it as all zeros
  // it will store integers that refer to places in datapoint array "active"
  int thegridsize = sm_gridsize;
  if (thegridsize < area1*2)
  {
    thegridsize = area1*2;
  }
  if (thegridsize < area2*2)
  {
    thegridsize = area2*2;
  }


  std::vector<std::vector<int>> grid(thegridsize,std::vector<int>(thegridsize,0));
  // "active" stores all the required information for any
  // lineages that have not yet speciated, this is in the
  // form of an array of "datapoint" objects
  std::vector<TreeDataPoint> active;
  // again we know this array has the same maximum size as "data"
  active.resize(2*area1*area2+1);
  // this marks the end of the active vector
  int endactive = 0; // 0 is reserved as null
  for (int tx = 0 ; tx < area1 ; tx++)
  {
    for (int ty = 0 ; ty < area2 ; ty++)
    {
      // looping over the survey area, we initialise both grid and active
      ++endactive;
      //active[endactive].setup(tx,ty,endactive);
      active[endactive] = TreeDataPoint(tx,ty,endactive);
      assert(tx >= 0);
      assert(tx < static_cast<int>(grid.size()));
      grid[tx][ty] = endactive;
    }
  }
  // other variables to be initialised
  int steps = 0;
  double error = 1000.0;
  // these three variables store information for STRs
  // has a lineage in our survey moved?
  // now do the calculations required to set up the tree
  // loop while error is too large or not included the full time interval
  while (error > (richness*tol))
  {
    // increment steps
    ++steps;
    // choose a random lineage to die and be reborn out of those currently active
    const int chosen = m_rnd.GetRandomInt(endactive-1) + 1; // cannot be 0
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
        movex += int(floor((m_rnd.GetRandomNormal()*dispersal)+0.5));
        movey += int(floor((m_rnd.GetRandomNormal()*dispersal)+0.5));
      }
    }
    else
    {
      // square distribtion kernel
      while (movex == 0 && movey == 0)
      {
        // loop to ensure we don't pick a individual to be its own parent
        movex += (m_rnd.GetRandomInt(dispersal*2)-dispersal);
        movey += (m_rnd.GetRandomInt(dispersal*2)-dispersal);
      }
    }
    // note this piece of code can easily be edited for any dispersal kernel
    // record old position of lineage
    const int oldx = active[chosen].GetXpos();
    const int oldy = active[chosen].GetYpos();
    assert(oldx >= 0);
    assert(oldx < static_cast<int>(grid.size()));
    // update grid to reflect new data
    grid[oldx][oldy] = active[chosen].GetNext();
    // if current individual is the only one in the space then it will hold
    // 0 in its data for next and last and this will still be correct
    // the next and last variables indicate the next and last in a ring
    // the ring holds together every individual lineage in the same grid postion
    // of course they would have different indexes and so be in different
    // physical positions. The use of a ring in this way makes
    // it really easy to check if two individuals coalesce
    assert(oldx >= 0);
    assert(oldx < static_cast<int>(grid.size()));
    if (grid[oldx][oldy] > 0)
    {
      // then we have an individual to set its next and last variables correctly
      if ( grid[oldx][oldy] == active[chosen].GetLast() )
      {
        assert(oldx >= 0);
        assert(oldx < static_cast<int>(grid.size()));
        // the ring contained 2 individuals
        active[grid[oldx][oldy]].SetLast(0);
        active[grid[oldx][oldy]].SetNext(0);
      }
      else
      {
        // the ring contained 3 or more individuals
        assert(oldx >= 0);
        assert(oldx < static_cast<int>(grid.size()));
        active[grid[oldx][oldy]].SetLast(active[chosen].GetLast());
        active[active[chosen].GetLast()].SetNext(active[chosen].GetNext());
      }
    }// now we have completely purged the grid of the old position of our chosen lineage
    active[chosen].SetNext(0);
    active[chosen].SetLast(0);
    // now actually do the move
    richness += minspec*(active[chosen].GetProbability());
    active[chosen].Move(movex,movey,minspec);
    m_nodes[active[chosen].GetMpos()].inc_steps();
    // record the new position
    int activex = active[chosen].GetXpos();
    int activey = active[chosen].GetYpos();
    // check for coalescence
    assert(activex >= 0);
    assert(activex < static_cast<int>(grid.size()));
    if ( grid[activex][activey] == 0)
    {
      // no coalescence possible
      assert(activex >= 0);
      assert(activex < static_cast<int>(grid.size()));
      grid[activex][activey] = chosen;
    }
    else
    {
      //coalescence possible
      bool loop = true;
      // check around the ring for coalescence
      assert(activex >= 0);
      assert(activex < static_cast<int>(grid.size()));
      const int start = grid[activex][activey]; // starting here
      // this is how far around the loop we have got checking for coalescence
      // we start at "start" and then move around methodically
      // the loops usually contain 1 individual but we must allow code for any number
      int current = start;
      while(loop)
      {
        if (active[chosen].GetXindex() == active[current].GetXindex())
        {
          if (active[chosen].GetYindex() == active[current].GetYindex())
          {
            // we have coalescence, update variables// update data
            m_enddata++;

            m_nodes[m_enddata] = TreeNode(false);

            //m_nodes[m_enddata].setup(false);
            // update data
            m_nodes[active[chosen].GetMpos()].set_parent(m_enddata);
            m_nodes[active[current].GetMpos()].set_parent(m_enddata);
            // update active
            active[current].SetMpos(m_enddata);
            double tempprob = active[chosen].GetProbability();
            tempprob = tempprob + active[current].GetProbability()*(1.0-tempprob);
            active[current].SetProbability(tempprob);
            active[chosen] = active[endactive];
            int oldx = active[endactive].GetXpos();
            int oldy = active[endactive].GetYpos();
            assert(oldx >= 0);
            assert(oldx < static_cast<int>(grid.size()));
            if (boost::numeric_cast<int>(grid[oldx][oldy]) == endactive)
            {
              grid[oldx][oldy] = chosen;
            }
            if (active[endactive].GetNext() >0)
            {
              active[active[endactive].GetNext()].SetLast(chosen);
              active[active[endactive].GetLast()].SetNext(chosen);
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
          current = active[current].GetNext();
          if (current == 0){
            // the loop was only of size one and there was no coalescence
            // this is most likely
            assert(activex >= 0);
            assert(activex < static_cast<int>(grid.size()));
            active[grid[activex][activey]].SetNext(chosen);
            active[grid[activex][activey]].SetLast(chosen);
            active[chosen].SetNext(grid[activex][activey]);
            active[chosen].SetLast(grid[activex][activey]);
            loop = false;
          }
          else
          {
            if(current == start)
            {
              // we have made one complete check of the loop and found
              // there was no coalescence but we still have to add the new position in
              assert(activex >= 0);
              assert(activex < static_cast<int>(grid.size()));
              int addlast = active[grid[activex][activey]].GetLast();
              active[addlast].SetNext(chosen);
              active[chosen].SetLast(addlast);
              active[chosen].SetNext(grid[activex][activey]);
              active[grid[activex][activey]].SetLast(chosen);
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
      {
        assert(i >= 0);
        assert(i < static_cast<int>(active.size()));
        error += active[i].GetProbability();
      }
    }
  }
}






/************************************************************
CLASS TREE - THE MAIN CLASS
************************************************************/

/************************************************************
RICHNESS CALCULATION METHODS
************************************************************/
std::vector<double> Tree::get_richnessint(const double spec)
// this returns an interval within which the true mean ricness must lie
{
  std::vector<double> result(2,0.0);
  if (m_minspecsetup <= spec)
    // check that the tree was calculated for a small enough speciation rate
    // it is possible to override this check by commenting out if required
  {
    // probarray stores, for each node, a probability that is required in the calculation
    std::vector<double> probarray;
    probarray.resize(m_enddata+1);
    for (int i = 1 ; i <= boost::numeric_cast<int>(m_enddata) ; ++i)
      // loop over all nodes and initialise the relating element in probarray
    {
      if (m_nodes[i].get_root() == false)
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
      for (int i = 1 ; i <= boost::numeric_cast<int>(m_enddata) ; ++i)
      {
        // check to see if that part of the array is complete
        if (probarray[i] >= 0.0)
        {
          // it is complete so use it to complete the info on in its parents
          int theparent = m_nodes[i].get_parent();
          if ((probarray[theparent] < 0.0) && (theparent != 0))
          {
            // only do anything if the parents have not already been completed
            loop = true;
            // be sure to go round again if the parents have not been completed
            if (probarray[theparent] <= -1.5)
            {
              // parent not at all complete
              const double temprob = (pow(1-spec,double(m_nodes[i].get_steps())));
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
              double temprob = (pow(1.0-spec,double(m_nodes[i].get_steps())));// update Smin
              result[0] += probarray[i]*(1.0-temprob);
              // update the probability array
              temprob = temprob*probarray[i];
              const double temprob2 = probarray[theparent]*-1.0;
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
    for (int i = 1 ; i <= boost::numeric_cast<int>(m_enddata) ; ++i)
    {
      // here we are dealing with all the last branches after prooning all nodes
      if (m_nodes[i].get_parent() == 0)
      {
        result[0] += probarray[i]*(1-pow(1-spec,double(m_nodes[i].get_steps())));
        result[1] += probarray[i]*pow(1-spec,double(m_nodes[i].get_steps()));
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
double Tree::get_richness(double spec)
// this returns the midpoint between the maximum and minimum richness estimates
{
  std::vector<double> richnessresult = get_richnessint(spec);
  return (richnessresult[0]+richnessresult[1])/2.0;
}
