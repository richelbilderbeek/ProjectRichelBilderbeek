#include "tree.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <boost/numeric/conversion/cast.hpp>

#include "grid.h"
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
    m_area_width{area_width},
    m_area_length{area_length},
    m_dispersal_distance{dispersal_distance},
    m_dispersal_kernel{dispersal_kernel},
    m_enddata{area_width * area_length},
    m_grid{},
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
  m_grid = CreateGrid(area_width,area_length,m_active);
}

std::vector<TreeDataPoint> Tree::CreateActive(const int area_width, const int area_length)
{
  std::vector<TreeDataPoint> v;
  assert(area_width > 0);
  assert(area_length > 0);
  //Index 0 is systematically avoided, unknown why
  v.push_back(TreeDataPoint(0,0,0));
  int i = 0;
  for (int x=0; x!=area_width; ++x)
  {
    for (int y=0; y!=area_length; ++y)
    {
      ++i;
      v.push_back(TreeDataPoint(x,y,i));
    }
  }
  return v;
}

Tree::Grid
  Tree::CreateGrid(
    const int width,
    const int height,
    std::vector<TreeDataPoint>& datapoints
)
{
  assert(width > 0);
  assert(height > 0);
  assert(!datapoints.empty());
  const int grid_size
    = sm_gridsize < width*2 ? width*2
    : (sm_gridsize < height*2 ? height*2 : sm_gridsize)
  ;
  assert(grid_size > 0);

  Grid v(
    grid_size,
    std::vector<GridType>(
      grid_size,
      0
    )
  );

  const int sz{static_cast<int>(datapoints.size())};
  //Skip 0, 0 denotes 'no-one here'
  for (int i=1; i!=sz; ++i)
  {
    const TreeDataPoint& p{datapoints[i]};
    v[p.GetXpos()][p.GetYpos()]
    //  = std::make_pair(i,&datapoints[i]);
      = i;
  }
  return v;
}

void Tree::DisplayActive(std::ostream& os) const noexcept
{
  const std::string seperator{" | "};
  std::ostringstream s;

  std::copy(
    std::begin(m_active) + 1,
    std::end(m_active),
    std::ostream_iterator<TreeDataPoint>(s,seperator.c_str())
  );

  std::string text{
    s.str().substr(0,s.str().size() - seperator.size())
  };
  os << text;
}

double Tree::GetError(
  //const std::vector<TreeDataPoint>& m_active
) const noexcept
{
  const int last_active_index{static_cast<int>(m_active.size()) - 1};
  double error = 0.0;
  for (int i = 1 ; i <= last_active_index ; ++i)
  {
    assert(i != 0 && "Skip zero");
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
  //NOTE: chosen_index cannot be 0, because 0 denotes 'no-one here' in the grid
  const int chosen_index{1 + m_rnd.GetRandomInt(m_active.size() - 1 - 1)};
  assert(chosen_index != 0 && "Skip zero");
  assert(IsValid(chosen_index,m_active));
  TreeDataPoint& chosen = m_active[chosen_index];

  assert(IsValid(chosen_index,m_active));
  const int from_x = chosen.GetXpos();
  const int from_y = chosen.GetYpos();

  //?
  m_richness += m_min_speciation_rate*(chosen.GetProbability());

  //Do the move, also tracks that the lineage did not speciate
  const std::pair<int,int> move{GetMove(m_dispersal_kernel,m_rnd,m_dispersal_distance)};
  chosen.Move(
    move.first,move.second,
    m_min_speciation_rate
  );

  //?
  assert(IsValid(chosen.GetMpos(),m_nodes));
  m_nodes[chosen.GetMpos()].IncSteps();

  const int to_x = chosen.GetXpos();
  const int to_y = chosen.GetYpos();
  assert(IsValid(to_x,to_y,m_grid));

  GridType& grid_spot_to{m_grid[to_x][to_y]};

  //If there an individual at the dispersed-to spot?
  if (grid_spot_to == 0)
  {
    //Remove active indidual from old spot
    m_grid[from_x][from_y] = 0;
    //Just move the individual
    grid_spot_to = chosen_index;
    //Nope, this timestep is done
    return;
  }

  //Remove active indidual from old spot
  m_grid[from_x][from_y] = 0;

  //There is an individual at the dispersed-to-spot

  //Let these two coalesce

  // check around the ring for coalescence

  // this is how far around the loop we have got checking for coalescence
  // we start at "start" and then move around methodically
  // the loops usually contain 1 individual but we must allow code for any number

  ++m_enddata;
  m_nodes[m_enddata] = TreeNode(false);
  m_nodes[chosen.GetMpos()].SetParent(m_enddata);

  assert(IsValid(grid_spot_to,m_active));
  assert(IsValid(m_active[grid_spot_to].GetMpos(),m_nodes));
  assert(grid_spot_to != 0 && "Skip zero");
  m_nodes[m_active[grid_spot_to].GetMpos()].SetParent(m_enddata);

  assert(IsValid(grid_spot_to,m_active));
  assert(grid_spot_to != 0 && "Skip zero");
  m_active[grid_spot_to].SetMpos(m_enddata);

  const double probability{
    chosen.GetProbability()
    + m_active[grid_spot_to].GetProbability()
    * (1.0-chosen.GetProbability())
  };

  assert(IsValid(grid_spot_to,m_active));
  assert(grid_spot_to != 0 && "Skip zero");

  m_active[grid_spot_to].SetProbability(probability);

  assert(m_active.size() - 1 != 0 && "Skip zero");

  TreeDataPoint& last_active = m_active.back();
  m_active[chosen_index] = last_active;

  const int last_active_x = last_active.GetXpos();
  const int last_active_y = last_active.GetYpos();

  assert(IsValid(last_active_x,last_active_y,m_grid));

  GridType& last_active_spot = m_grid[last_active_x][last_active_y];

  if (last_active_spot == static_cast<int>(m_active.size()) - 1)
  {
    last_active_spot = chosen_index;
  }
  m_active.pop_back();
}
