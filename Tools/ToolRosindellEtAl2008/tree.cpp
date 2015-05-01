#include "tree.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <boost/numeric/conversion/cast.hpp>

#include "treedatapoint.h"
#include "treenode.h"
#include "trace.h"

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
    m_active{CreateActive(area_width,area_length)},
    m_dispersal_distance{dispersal_distance},
    m_dispersal_kernel{dispersal_kernel},
    m_enddata{area_width * area_length},
    m_grid{CreateGrid(area_width,area_length)},
    m_min_speciation_rate{min_speciation_rate},
    m_nodes{std::vector<TreeNode>(2*area_width*area_length+1,TreeNode(true))},
    m_richness{0.0},
    m_rnd{rng},
    m_tolerance{tolerance}
{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_dispersal_distance == 0)
  {
    throw std::logic_error("Tree::Tree: dispersal distance must be non-zero");
  }
  if (m_dispersal_distance < 0)
  {
    throw std::logic_error("Tree::Tree: dispersal distance must be positive");
  }
}

std::vector<TreeDataPoint> Tree::CreateActive(const int area_width, const int area_length)
{
  std::vector<TreeDataPoint> v;
  assert(area_width > 0);
  assert(area_length > 0);
  //Index 0 is systematically avoided, unknown why
  //v.push_back(TreeDataPoint(-123,-234,-345));
  int i = 0;
  for (int x=0; x!=area_width; ++x)
  {
    for (int y=0; y!=area_length; ++y)
    {
      v.push_back(TreeDataPoint(x,y,i));
      ++i;
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
  assert(sz > 0);

  //FAILS std::vector<std::vector<int>> v(area_width,std::vector<int>(area_length,0));
  //FAILS std::vector<std::vector<int>> v(area_width * 2,std::vector<int>(area_length * 2,0));
  std::vector<std::vector<int>> v(sz,std::vector<int>(sz,0));

  int i=0;
  for (int x = 0 ; x != area_width ; ++x)
  {
    for (int y = 0 ; y != area_length ; ++y)
    {
      v[x][y] = i;
      ++i;
    }
  }
  return v;
}

void Tree::DisplayActive(std::ostream& os) const noexcept
{
  std::copy(
    std::begin(m_active),
    std::end(m_active),
    std::ostream_iterator<TreeDataPoint>(os," - ")
  );
}

void Tree::DisplayGrid(std::ostream& os) const noexcept
{
  for (const auto line: m_grid)
  {
    std::copy(
      std::begin(line),
      std::end(line),
      std::ostream_iterator<int>(os," ")
    );
    os << '\n';
  }
}



double Tree::GetError(
  //const std::vector<TreeDataPoint>& m_active
) const noexcept
{
  const int last_active_index{static_cast<int>(m_active.size()) - 1};
  double error = 0.0;
  for (int i = 0 ; i != last_active_index ; ++i)
  {
    assert(IsValid(i,m_active));
    error += m_active[i].GetProbability();
  }
  return error;
}

std::pair<int,int> Tree::GetMove(
  const DispersalKernel dispersal_kernel,
  Rng& rnd,
  const int dispersal
)
{
  assert(dispersal > 0);
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
    ps[i] = m_nodes[i].GetRoot() ? 1.0 : -2.0;
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
        const int theparent{m_nodes[i].GetParent()};
        assert(IsValid(theparent,ps));
        if (ps[theparent] < 0.0 && theparent != 0)
        {
          // only do anything if the parents have not already been completed
          loop = true;
          // be sure to go round again if the parents have not been completed
          if (ps[theparent] <= -1.5)
          {
            // parent not at all complete
            const double steps{static_cast<double>(m_nodes[i].GetSteps())};
            const double temprob{
              std::pow(
                1-speciation_rate,
                steps//static_cast<double>(m_nodes[i].GetSteps())
              )
            };
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
            // update Smin
            const double steps{static_cast<double>(m_nodes[i].GetSteps())};
            double temprob{
              std::pow(
                1.0-speciation_rate,
                steps //static_cast<double>(m_nodes[i].GetSteps())
              )
            };
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
    if (m_nodes[i].GetParent() == 0)
    {
      const double steps{static_cast<double>(m_nodes[i].GetSteps())};
      result[0] += ps[i] * (1.0 - std::pow(1.0 - speciation_rate,steps) );
      result[1] += ps[i] * (      std::pow(1.0 - speciation_rate,steps) );
    }
  }
  result[1] += result[0];
  return result;
}

bool Tree::IsDone() const noexcept
{
  const double error{GetError()};
  return error < m_richness * m_tolerance;
}

void Tree::Update()
{
  //NOTE: chosen_index be 0, WHY?
  const int chosen_index{0 + m_rnd.GetRandomInt(m_active.size() - 1)};
  assert(IsValid(chosen_index,m_active));
  TreeDataPoint& chosen = m_active[chosen_index];

  //Note: there is no speciation included in this part of the program

  // record old position of lineage
  assert(IsValid(chosen_index,m_active));
  const int from_x = chosen.GetXpos();
  const int from_y = chosen.GetYpos();
  assert(IsValid(from_x,from_y,m_grid));
  int& from = m_grid[from_x][from_y];
  // update grid to reflect new data
  from = chosen.GetNext();
  assert(from >= 0);
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
      assert(IsValid(from,m_active));
      //The ring contained 2 individuals
      m_active[from].SetLast(0);
      m_active[from].SetNext(0);
    }
    else
    {
      //The ring contained 3 or more individuals
      assert(IsValid(from,m_active));
      m_active[from].SetLast(chosen.GetLast());
      assert(IsValid(chosen.GetLast(),m_active));
      m_active[chosen.GetLast()].SetNext(chosen.GetNext());
    }
  }

  //Done purging the grid of the old position of our chosen lineage
  chosen.SetNext(0);
  chosen.SetLast(0);
  m_richness += m_min_speciation_rate*(chosen.GetProbability());

  //Do the move
  const std::pair<int,int> move{GetMove(m_dispersal_kernel,m_rnd,m_dispersal_distance)};
  chosen.Move(
    move.first,move.second,
    m_min_speciation_rate
  );

  assert(IsValid(chosen.GetMpos(),m_nodes));
  m_nodes[chosen.GetMpos()].IncSteps();

  //New position
  const int active_x = chosen.GetXpos();
  const int active_y = chosen.GetYpos();
  assert(IsValid(active_x,active_y,m_grid));
  int& grid_active{m_grid[active_x][active_y]};
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
      assert(IsValid(current,m_active));
      if (chosen.GetXindex() == m_active[current].GetXindex())
      {
        assert(IsValid(current,m_active));
        if (chosen.GetYindex() == m_active[current].GetYindex())
        {
          // we have coalescence
          ++m_enddata;
          m_nodes[m_enddata] = TreeNode(false);

          m_nodes[chosen.GetMpos()].SetParent(m_enddata);

          assert(IsValid(current,m_active));
          assert(IsValid(m_active[current].GetMpos(),m_nodes));
          m_nodes[m_active[current].GetMpos()].SetParent(m_enddata);

          // update active
          assert(IsValid(current,m_active));
          m_active[current].SetMpos(m_enddata);

          const double probability{
            chosen.GetProbability()
            + m_active[current].GetProbability()
            * (1.0-chosen.GetProbability())
          };

          assert(IsValid(current,m_active));
          m_active[current].SetProbability(probability);

          assert(IsValid(m_active.size() - 1,m_active));
          chosen = m_active[m_active.size() - 1];
          //chosen = m_active[last_active_index];


          assert(IsValid(m_active.size() - 1,m_active));

          const int newx = m_active[m_active.size() - 1].GetXpos();
          //const int newx = m_active[last_active_index].GetXpos();
          const int newy = m_active[m_active.size() - 1].GetYpos();
          //const int newy = m_active[last_active_index].GetYpos();

          assert(IsValid(newx,newy,m_grid));
          int& to = m_grid[newx][newy];

          if (to == static_cast<int>(m_active.size()) - 1)
          //if (to == last_active_index)
          {
            to = chosen_index;
          }
          assert(IsValid(m_active.size() - 1,m_active));

          if (m_active[m_active.size() - 1].GetNext() > 0)
          //if (m_active[last_active_index].GetNext() > 0)
          {
            assert(IsValid(m_active.size() - 1,m_active));
            assert(IsValid(m_active[m_active.size() - 1].GetNext(),m_active));

            m_active[m_active[m_active.size() - 1].GetNext()].SetLast(chosen_index);
            //m_active[m_active[last_active_index].GetNext()].SetLast(chosen_index);

            assert(IsValid(m_active.size() - 1,m_active));
            assert(IsValid(m_active[m_active.size() - 1].GetNext(),m_active));
            m_active[m_active[m_active.size() - 1].GetLast()].SetNext(chosen_index);
            //m_active[m_active[last_active_index].GetLast()].SetNext(chosen_index);
          }

          assert(m_active.back().GetNext() == 0);
          assert(m_active.back().GetLast() == 0);
          m_active.pop_back();

          // update grid not necessary as
          // we already purged the old lineage from the grid and loops
          loop = false;
        }
      }
      if (loop)
      {
        // move to the next place in the loop ready for another check
        current = m_active[current].GetNext();
        if (current == 0)
        {
          // the loop was only of size one and there was no coalescence
          // this is most likely
          assert(IsValid(grid_active,m_active));
          m_active[grid_active].SetNext(chosen_index);
          assert(IsValid(grid_active,m_active));
          m_active[grid_active].SetLast(chosen_index);
          assert(IsValid(chosen_index,m_active));
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
            assert(IsValid(grid_active,m_active));
            const int addlast = m_active[grid_active].GetLast();
            assert(IsValid(addlast,m_active));
            m_active[addlast].SetNext(chosen_index);
            assert(IsValid(chosen_index,m_active));
            chosen.SetLast(addlast);
            chosen.SetNext(grid_active);
            assert(IsValid(grid_active,m_active));
            m_active[grid_active].SetLast(chosen_index);
            loop = false;
          }
        }
      }
    }
  }

}
