#include "tree.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <boost/numeric/conversion/cast.hpp>

#include "treedatapoint.h"

template <class Container>
bool IsValid(const int index, const Container& container)
{
  return index >= 0 && index < static_cast<int>(container.size());
}

template <class Container>
bool IsValid(const int index1, const int index2, const Container& container)
{
  if (!IsValid(index1,container)) return false;
  assert(!container.empty());
  return IsValid(index2,container[0]);
}

Tree::Tree(
  Rng& rng,
  const int area_width,
  const int area_length,
  const double min_speciation_rate,
  const int dispersal_distance,
  const double tolerance,
  const DispersalKernel dispersal_kernel
  )
  :
    m_nodes{std::vector<TreeNode>(2*area_width*area_length+1,TreeNode(true))},
    m_enddata{area_width * area_length},
    m_minspecsetup{2},
    m_rnd{rng}
{
  double richness = 0.0;

  // the time interval - ensure this is at least 0
  // a value of 0 gives a basic SAR only for maxintsetup
  // the minimal speciation rate that we are preparing the tree for
  m_minspecsetup = min_speciation_rate;

  // grid - this is an internal variable
  // this is necessary for calculations - initialise it as all zeros
  // it will store integers that refer to places in datapoint array "active"
  std::vector<std::vector<int>> grid{
    CreateGrid(area_width,area_length)
  };

  // Store the coalescence tree itself
  // there can only be a maximum of twice as many nodes as there are
  // initially free branches so we can set the size of our data object
  std::vector<TreeDataPoint> active{
    CreateActive(area_width,area_length)
  };

  int endactive = area_width * area_length;
  assert(endactive == area_width * area_length);


  int steps = 0;
  double error = 1000.0;

  // these three variables store information for STRs
  // has a lineage in our survey moved?
  // now do the calculations required to set up the tree
  // loop while error is too large or not included the full time interval
  while (error > richness * tolerance)
  {
    ++steps;

    // choose a random lineage to die and be reborn out of those currently active
    const int chosen_index = m_rnd.GetRandomInt(endactive-1) + 1; // cannot be 0
    assert(IsValid(chosen_index,active));
    TreeDataPoint& chosen = active[chosen_index];

    // remember there is no speciation included in this part of the programme
    // choose movement of chosen lineage
    const std::pair<int,int> move{GetMove(dispersal_kernel,m_rnd,dispersal_distance)};
    const int movex = move.first; // will store x direction movement
    const int movey = move.second; // will store y direction movement
    assert(movex != 0 || movey != 0);

    // record old position of lineage
    assert(IsValid(chosen_index,active));
    const int from_x = chosen.GetXpos();
    const int from_y = chosen.GetYpos();
    assert(IsValid(from_x,from_y,grid));
    int& from = grid[from_x][from_y];
    // update grid to reflect new data
    from = chosen.GetNext();
    // if current individual is the only one in the space then it will hold
    // 0 in its data for next and last and this will still be correct
    // the next and last variables indicate the next and last in a ring
    // the ring holds together every individual lineage in the same grid postion
    // of course they would have different indexes and so be in different
    // physical positions. The use of a ring in this way makes
    // it really easy to check if two individuals coalesce
    if (from > 0)
    {
      // then we have an individual to set its next and last variables correctly
      if (from == chosen.GetLast() )
      {
        assert(IsValid(from,active));
        // the ring contained 2 individuals
        active[from].SetLast(0);
        active[from].SetNext(0);
      }
      else
      {
        // the ring contained 3 or more individuals
        assert(IsValid(from_x,from_y,grid));
        active[from].SetLast(chosen.GetLast());
        active[chosen.GetLast()].SetNext(chosen.GetNext());
      }
    }

    // now we have completely purged the grid of the old position of our chosen lineage
    chosen.SetNext(0);
    chosen.SetLast(0);
    // now actually do the move
    richness += min_speciation_rate*(chosen.GetProbability());
    chosen.Move(movex,movey,min_speciation_rate);
    m_nodes[chosen.GetMpos()].inc_steps();
    // record the new position
    const int activex = chosen.GetXpos();
    const int activey = chosen.GetYpos();
    // check for coalescence
    assert(IsValid(activex,activey,grid));
    if ( grid[activex][activey] == 0)
    {
      // no coalescence possible
      grid[activex][activey] = chosen_index;
    }
    else
    {
      //coalescence possible
      bool loop = true;
      // check around the ring for coalescence
      assert(IsValid(activex,activey,grid));
      const int start = grid[activex][activey]; // starting here
      // this is how far around the loop we have got checking for coalescence
      // we start at "start" and then move around methodically
      // the loops usually contain 1 individual but we must allow code for any number
      int current = start;
      while(loop)
      {
        if (chosen.GetXindex() == active[current].GetXindex())
        {
          if (chosen.GetYindex() == active[current].GetYindex())
          {
            // we have coalescence
            ++m_enddata;

            m_nodes[m_enddata] = TreeNode(false);

            m_nodes[chosen.GetMpos()].set_parent(m_enddata);
            m_nodes[active[current].GetMpos()].set_parent(m_enddata);

            // update active
            active[current].SetMpos(m_enddata);


            const double tempprob = chosen.GetProbability() + active[current].GetProbability()*(1.0- chosen.GetProbability() );

            active[current].SetProbability(tempprob);
            chosen = active[endactive];
            const int newx = active[endactive].GetXpos();
            const int newy = active[endactive].GetYpos();
            int& to = grid[newx][newy];
            assert(IsValid(newx,newy,grid));
            if (to == endactive)
            {
              to = chosen_index;
            }
            if (active[endactive].GetNext() >0)
            {
              active[active[endactive].GetNext()].SetLast(chosen_index);
              active[active[endactive].GetLast()].SetNext(chosen_index);
            }
            --endactive;
            // update grid not necessary as
            // we already purged the old lineage from the grid and loops
            loop = false;
          }
        }
        if (loop)
        {
          // move to the next place in the loop ready for another check
          current = active[current].GetNext();
          if (current == 0)
          {
            // the loop was only of size one and there was no coalescence
            // this is most likely
            assert(IsValid(activex,activey,grid));
            assert(IsValid(grid[activex][activey],active));
            active[grid[activex][activey]].SetNext(chosen_index);
            active[grid[activex][activey]].SetLast(chosen_index);
            assert(IsValid(chosen_index,active));
            chosen.SetNext(grid[activex][activey]);
            chosen.SetLast(grid[activex][activey]);
            loop = false;
          }
          else
          {
            if(current == start)
            {
              // we have made one complete check of the loop and found
              // there was no coalescence but we still have to add the new position in
              assert(IsValid(activex,activey,grid));
              assert(IsValid(grid[activex][activey],active));
              const int addlast = active[grid[activex][activey]].GetLast();
              assert(IsValid(addlast,active));
              active[addlast].SetNext(chosen_index);
              assert(IsValid(chosen_index,active));
              chosen.SetLast(addlast);
              chosen.SetNext(grid[activex][activey]);
              active[grid[activex][activey]].SetLast(chosen_index);
              loop = false;
            }
          }
        }
      }
    }
    // this piece of code updates the error
    // but only does so every community turnover
    // this is so that not too long is spent on this
    if (steps%(area_width*area_length*250) == 0)
    {
      // check errors and update
      error = 0.0;
      for (int i = 1 ; i <= endactive ; ++i)
      {
        assert(IsValid(i,active));
        error += active[i].GetProbability();
      }
    }
  }
}

std::vector<TreeDataPoint> Tree::CreateActive(const int area_width, const int area_length)
{
  std::vector<TreeDataPoint> v;
  assert(area_width > 0);
  assert(area_length > 0);

  // again we know this array has the same maximum size as "data"
  v.resize(2*area_width*area_length+1);

  // this marks the end of the active vector
  int i = 0;
  for (int tx = 0 ; tx != area_width ; ++tx)
  {
    for (int ty = 0 ; ty != area_length ; ++ty)
    {
      ++i;
      v[i] = TreeDataPoint(tx,ty,i);
    }
  }
  return v;
}

std::vector<std::vector<int>>
  Tree::CreateGrid(const int area_width, const int area_length
)
{
  assert(area_width > 0);
  assert(area_length > 0);

  const int thegridsize
    = sm_gridsize < area_width*2 ? area_width*2
    : (sm_gridsize < area_length*2 ? area_length*2 : sm_gridsize)
  ;

  std::vector<std::vector<int>> v(thegridsize,std::vector<int>(thegridsize,0));

  int i=0;
  for (int tx = 0 ; tx != area_width ; ++tx)
  {
    for (int ty = 0 ; ty != area_length ; ++ty)
    {
      // looping over the survey area, we initialise both grid and active
      ++i;
      v[tx][ty] = i;
    }
  }

  return v;
}

// this returns an interval within which the true mean ricness must lie
std::vector<double> Tree::GetRichnessInterval(const double spec)
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

std::pair<int,int> Tree::GetMove(
  const DispersalKernel dispersal_kernel,
  Rng& rnd,
  const int dispersal
)
{
  int x = 0;
  int y = 0;
  if (dispersal_kernel == DispersalKernel::normal)
  {
    while (x == 0 && y == 0)
    {
      // loop to ensure we don't pick a individual to be its own parent
      x = int(floor((rnd.GetRandomNormal()*dispersal)+0.5));
      y = int(floor((rnd.GetRandomNormal()*dispersal)+0.5));
    }
  }
  else
  {
    while (x == 0 && y == 0)
    {
      // loop to ensure we don't pick a individual to be its own parent
      x = (rnd.GetRandomInt(dispersal*2)-dispersal);
      y = (rnd.GetRandomInt(dispersal*2)-dispersal);
    }
  }
  return std::make_pair(x,y);
}

double Tree::get_richness(double spec)
{
  // this returns the midpoint between the maximum and minimum richness estimates
  std::vector<double> richnessresult = GetRichnessInterval(spec);
  return (richnessresult[0]+richnessresult[1])/2.0;
}
