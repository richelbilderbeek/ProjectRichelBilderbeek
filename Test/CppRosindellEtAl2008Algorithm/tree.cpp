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
    m_min_speciation_rate{min_speciation_rate},
    m_rnd{rng}
{
  double richness = 0.0;

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

  while (error > richness * tolerance)
  {
    ++steps;

    // choose a random lineage to die and be reborn out of those currently active
    const int chosen_index = m_rnd.GetRandomInt(endactive-1) + 1; // cannot be 0
    assert(chosen_index != 0 && "Skip zero?");
    assert(IsValid(chosen_index,active));
    TreeDataPoint& chosen = active[chosen_index];

    //Note: there is no speciation included in this part of the program

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
        assert(from != 0 && "Skip zero?");
        assert(IsValid(from,active));
        //The ring contained 2 individuals
        active[from].SetLast(0);
        active[from].SetNext(0);
      }
      else
      {
        //The ring contained 3 or more individuals
        assert(IsValid(from,active));
        assert(from != 0 && "Skip zero?");
        active[from].SetLast(chosen.GetLast());
        assert(IsValid(chosen.GetLast(),active));
        assert(chosen.GetLast() != 0 && "Skip zero?");
        active[chosen.GetLast()].SetNext(chosen.GetNext());
      }
    }

    //Done purging the grid of the old position of our chosen lineage
    chosen.SetNext(0);
    chosen.SetLast(0);
    richness += min_speciation_rate*(chosen.GetProbability());

    //Do the move
    const std::pair<int,int> move{GetMove(dispersal_kernel,m_rnd,dispersal_distance)};
    chosen.Move(move.first,move.second,min_speciation_rate);

    assert(IsValid(chosen.GetMpos(),m_nodes));
    m_nodes[chosen.GetMpos()].inc_steps();

    //New position
    const int active_x = chosen.GetXpos();
    const int active_y = chosen.GetYpos();
    assert(IsValid(active_x,active_y,grid));
    int& grid_active{grid[active_x][active_y]};
    // check for coalescence
    if (grid_active == 0)
    {
      // no coalescence possible
      grid_active = chosen_index;
    }
    else
    {
      //coalescence possible
      bool loop = true;
      // check around the ring for coalescence
      const int start = grid_active; // starting here
      // this is how far around the loop we have got checking for coalescence
      // we start at "start" and then move around methodically
      // the loops usually contain 1 individual but we must allow code for any number
      int current = start;
      while(loop)
      {
        assert(IsValid(current,active));
        assert(current != 0 && "Skip zero?");
        if (chosen.GetXindex() == active[current].GetXindex())
        {
          assert(IsValid(current,active));
          assert(current != 0 && "Skip zero?");
          if (chosen.GetYindex() == active[current].GetYindex())
          {
            // we have coalescence
            ++m_enddata;
            m_nodes[m_enddata] = TreeNode(false);

            m_nodes[chosen.GetMpos()].set_parent(m_enddata);
            assert(IsValid(current,active));
            assert(IsValid(active[current].GetMpos(),m_nodes));
            assert(current != 0 && "Skip zero?");
            m_nodes[active[current].GetMpos()].set_parent(m_enddata);

            // update active
            assert(IsValid(current,active));
            assert(current != 0 && "Skip zero?");
            active[current].SetMpos(m_enddata);

            const double probability{
              chosen.GetProbability()
              + active[current].GetProbability()
              * (1.0-chosen.GetProbability())
            };

            assert(IsValid(current,active));
            assert(current != 0 && "Skip zero?");
            active[current].SetProbability(probability);

            assert(IsValid(endactive,active));
            assert(endactive != 0 && "Skip zero?");
            chosen = active[endactive];

            assert(IsValid(endactive,active));
            assert(endactive != 0 && "Skip zero?");
            const int newx = active[endactive].GetXpos();
            const int newy = active[endactive].GetYpos();

            assert(IsValid(newx,newy,grid));
            int& to = grid[newx][newy];
            if (to == endactive)
            {
              to = chosen_index;
            }
            assert(IsValid(endactive,active));
            assert(endactive != 0 && "Skip zero?");
            if (active[endactive].GetNext() > 0)
            {
              assert(IsValid(endactive,active));
              assert(IsValid(active[endactive].GetNext(),active));
              assert(endactive != 0 && "Skip zero?");
              assert(active[endactive].GetNext() != 0 && "Skip zero?");
              active[active[endactive].GetNext()].SetLast(chosen_index);

              assert(IsValid(endactive,active));
              assert(IsValid(active[endactive].GetNext(),active));
              assert(endactive != 0 && "Skip zero?");
              assert(active[endactive].GetLast() != 0 && "Skip zero?");
              active[active[endactive].GetLast()].SetNext(chosen_index);
            }
            --endactive;
            assert(endactive >= 0);
            // update grid not necessary as
            // we already purged the old lineage from the grid and loops
            loop = false;
          }
        }
        if (loop)
        {
          // move to the next place in the loop ready for another check
          assert(current != 0 && "Skip zero?");
          current = active[current].GetNext();
          if (current == 0)
          {
            // the loop was only of size one and there was no coalescence
            // this is most likely
            assert(IsValid(grid_active,active));
            assert(grid_active != 0 && "Skip zero?");
            active[grid_active].SetNext(chosen_index);
            assert(IsValid(grid_active,active));
            assert(grid_active != 0 && "Skip zero?");
            active[grid_active].SetLast(chosen_index);
            assert(IsValid(chosen_index,active));
            chosen.SetNext(grid_active);
            chosen.SetLast(grid_active);
            loop = false;
          }
          else
          {
            if(current == start)
            {
              // we have made one complete check of the loop and found
              // there was no coalescence but we still have to add the new position in
              assert(IsValid(grid_active,active));
              const int addlast = active[grid_active].GetLast();
              assert(IsValid(addlast,active));
              assert(addlast != 0 && "Skip zero?");
              active[addlast].SetNext(chosen_index);
              assert(IsValid(chosen_index,active));
              chosen.SetLast(addlast);
              chosen.SetNext(grid_active);
              assert(IsValid(grid_active,active));
              assert(grid_active != 0 && "Skip zero?");
              active[grid_active].SetLast(chosen_index);
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
        assert(i != 0 && "Skip zero?");
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

  v.resize(2*area_width*area_length+1);

  int i = 0;
  for (int x=0; x!=area_width; ++x)
  {
    for (int y=0; y!=area_length; ++y)
    {
      ++i;
      v[i] = TreeDataPoint(x,y,i);
      //v.push_back(TreeDataPoint(tx,ty,i)); //NOT YET
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

  const int sz
    = sm_gridsize < area_width*2 ? area_width*2
    : (sm_gridsize < area_length*2 ? area_length*2 : sm_gridsize)
  ;

  std::vector<std::vector<int>> v(sz,std::vector<int>(sz,0));

  int i=0;
  for (int tx = 0 ; tx != area_width ; ++tx)
  {
    for (int ty = 0 ; ty != area_length ; ++ty)
    {
      ++i;
      v[tx][ty] = i;
    }
  }

  return v;
}

// this returns an interval within which the true mean ricness must lie
std::array<double,2> Tree::GetRichnessInterval(const double speciation_rate)
{
  // check that the tree was calculated for a small enough speciation rate
  // it is possible to override this check by commenting out if required
  if (m_min_speciation_rate > speciation_rate)
  {
    throw std::logic_error("Tree::GetRichnessInterval: could not calculate result");
  }

  std::array<double,2> result = {0.0,0.0};

  //The probabilities at each node
  const int sz{m_enddata};
  std::vector<double> ps(sz+1);
  for (int i = 1; i<=sz; ++i)
  {
    //  1.0: free branch, because it is certain that the lineages have not encountered speciaiton// when they are at the very end and no pruning has so far taken place
    // -2.0: an internal node that has thus far not been pruned at all
    assert(IsValid(i,m_nodes));
    assert(IsValid(i,ps));
    ps[i] = m_nodes[i].get_root() ? 1.0 : -2.0;
  }

  bool loop = true;
  while (loop)
  {
    loop = false;
    for (int i = 1; i<=sz; ++i)
    {
      // check to see if that part of the array is complete
      assert(IsValid(i,ps));
      if (ps[i] >= 0.0)
      {
        // it is complete so use it to complete the info on in its parents
        const int theparent = m_nodes[i].get_parent();
        assert(IsValid(theparent,ps));
        if (ps[theparent] < 0.0 && theparent != 0)
        {
          // only do anything if the parents have not already been completed
          loop = true;
          // be sure to go round again if the parents have not been completed
          if (ps[theparent] <= -1.5)
          {
            // parent not at all complete
            const double temprob = (pow(1-speciation_rate,double(m_nodes[i].get_steps())));
            result[0] += ps[i]*(1-temprob);
            // we store probabilities as negative in a node if they
            // refer only to one of the two branches of the node
            // we then wait until we have both branches of the node
            // before continuing to complete the full calculation
            ps[theparent]= -1.0*ps[i]*temprob;
          }
          else
          {
            // parent partailly complete
            double temprob = (pow(1.0-speciation_rate,double(m_nodes[i].get_steps())));// update Smin
            result[0] += ps[i]*(1.0-temprob);
            // update the probability array
            temprob = temprob*ps[i];
            const double temprob2 = ps[theparent]*-1.0;
            ps[theparent]=(temprob+temprob2-temprob*temprob2);
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
  for (int i = 1; i<=sz; ++i)
  {
    // here we are dealing with all the last branches after prooning all nodes
    assert(IsValid(i,m_nodes));
    if (m_nodes[i].get_parent() == 0)
    {
      result[0] += ps[i]*(1-pow(1-speciation_rate,double(m_nodes[i].get_steps())));
      result[1] += ps[i]*pow(1-speciation_rate,double(m_nodes[i].get_steps()));
    }
  }
  result[1] += result[0];
  return result;
}

std::pair<int,int> Tree::GetMove(
  const DispersalKernel dispersal_kernel,
  Rng& rnd,
  const int dispersal
)
{
  if (dispersal_kernel == DispersalKernel::normal)
  {
    while (1)
    {
      const int x{
        static_cast<int>(
          std::floor((rnd.GetRandomNormal()*dispersal)+0.5)
        )
      };
      const int y{
        static_cast<int>(
          std::floor((rnd.GetRandomNormal()*dispersal)+0.5)
        )
      };
      if (x != 0 || y != 0)
      {
        return std::make_pair(x,y);
      }
    }
  }
  else
  {
    while (1)
    {
      const int x{rnd.GetRandomInt(dispersal*2)-dispersal};
      const int y{rnd.GetRandomInt(dispersal*2)-dispersal};
      if (x != 0 || y != 0)
      {
        return std::make_pair(x,y);
      }
    }
  }
}

double Tree::GetRichness(const double speciation_rate)
{
  const auto& v = GetRichnessInterval(speciation_rate);
  return (v[0]+v[1])/2.0;
}
