//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#include "tree.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
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
    m_active{},
    m_area_width{area_width},
    m_area_length{area_length},
    m_dispersal_distance{dispersal_distance},
    m_dispersal_kernel{dispersal_kernel},
    m_grid{},
    m_min_speciation_rate{min_speciation_rate},
    m_nodes{},
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
  //Reserving m_nodes is important: due to pointer,
  //we must prevent a copy of the nodes
  m_nodes.reserve(2*area_width*area_length+1); //These are reserved
  m_nodes.resize(area_width*area_length+1); //These are used
  m_active = CreateActive(area_width,area_length,m_nodes);
  m_grid = CreateGrid(area_width,area_length,m_active);
}

std::vector<TreeDataPoint> Tree::CreateActive(
  const int area_width,
  const int area_length,
  TreeNodes& nodes
)
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
      v.push_back(TreeDataPoint(x,y,&nodes[i]));
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
      nullptr
    )
  );

  const int sz{static_cast<int>(datapoints.size())};
  //Skip 0, 0 denotes 'no-one here'
  for (int i=1; i!=sz; ++i)
  {
    const TreeDataPoint& p{datapoints[i]};
    v[p.GetXpos()][p.GetYpos()]
      = &datapoints[i];
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

double Tree::GetError() const noexcept
{
  const int sz{static_cast<int>(m_active.size()) };
  double error = 0.0;
  for (int i = 1; i != sz; ++i)
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
  for (TreeNode& node: m_nodes)
  {
    //  1.0: free branch, because it is certain that the lineages have not encountered speciaiton// when they are at the very end and no pruning has so far taken place
    // -2.0: an internal node that has thus far not been pruned at all
    //assert(node.GetProbability() == (node.GetRoot() ? 1.0 : -2.0)); //FAILS, because this calculation repeats itself
    node.SetProbability(node.IsRootNode() ? 1.0 : -2.0);
  }

  while (1)
  {
    const int sz{static_cast<int>(m_nodes.size())};
    bool loop = false;
    for (int i = 1; i!=sz; ++i)
    {
      //check to see if that part of the array is complete
      assert(IsValid(i,m_nodes));
      const TreeNode& node{m_nodes[i]};
      if (node.GetProbability() >= 0.0)
      {
        // it is complete so use it to complete the info on in its parents
        TreeNode * const parent{node.GetParent()};
        //assert(IsValid(theparent,ps));
        if (parent && parent->GetProbability() < 0.0)
        {
          // only do anything if the parents have not already been completed
          loop = true;
          // be sure to go round again if the parents have not been completed
          if (parent->GetProbability() <= -1.5)
          {
            // parent not at all complete
            const double probability{
              std::pow(
                1.0-speciation_rate,
                node.GetBranchLength()
              )
            };
            result[0] += node.GetProbability()*(1.0-probability);
            // we store probabilities as negative in a node if they
            // refer only to one of the two branches of the node
            // we then wait until we have both branches of the node
            // before continuing to complete the full calculation
            parent->SetProbability(
              -1.0 * node.GetProbability() * probability
            );
          }
          else
          {
            //Parent partially complete
            double probability_1{
              std::pow(
                1.0-speciation_rate,
                node.GetBranchLength()
              )
            };
            result[0] += node.GetProbability()*(1.0-probability_1);
            probability_1 *= node.GetProbability();
            const double probability_2 = parent->GetProbability()*-1.0;
            parent->SetProbability(
               probability_1 + probability_2
             - probability_1 * probability_2
            );
          }
        }
      }
      else
      {
        // be sure to repeat the loop unless all calculations are fully compelted
        loop = true;
      }
    }
    if (loop == false) break;
  }

  {
    const int sz{static_cast<int>(m_nodes.size())};
    for (int i = 1; i!=sz; ++i)
    {
      // here we are dealing with all the last branches after prooning all nodes
      assert(IsValid(i,m_nodes));
      const TreeNode& node{m_nodes[i]};
      if (node.GetParent() == nullptr)
      {
        const double branch_length{node.GetBranchLength()};
        result[0] += node.GetProbability() * (1.0 - std::pow(1.0 - speciation_rate,branch_length) );
        result[1] += node.GetProbability() * (      std::pow(1.0 - speciation_rate,branch_length) );
      }
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
  assert(IsValid(chosen_index,m_active));
  TreeDataPoint& chosen = m_active[chosen_index];

   //Remove active indidual from old spot
   {
    const int x = chosen.GetXpos();
    const int y = chosen.GetYpos();
    m_grid[x][y] = nullptr;
  }

  //?
  m_richness += m_min_speciation_rate*(chosen.GetProbability());

  //Do the move, also tracks that the lineage did not speciate
  const std::pair<int,int> move{GetMove(m_dispersal_kernel,m_rnd,m_dispersal_distance)};
  chosen.Move(
    move.first,move.second,
    m_min_speciation_rate
  );

  //?
  //assert(IsValid(chosen.GetMpos(),m_nodes));
  chosen.GetNode()->IncreaseBranchLength();

  const int to_x = chosen.GetXpos();
  const int to_y = chosen.GetYpos();
  assert(IsValid(to_x,to_y,m_grid));

  GridType& grid_spot_to{m_grid[to_x][to_y]};

  //If there an individual at the dispersed-to spot?
  if (grid_spot_to == nullptr)
  {
    //Just move the individual
    grid_spot_to = &chosen;
    //Nope, this timestep is done
    return;
  }

  //Remove active indidual from old spot
  //m_grid[from_x][from_y] = nullptr;

  //There is an individual at the dispersed-to-spot

  //Let these two coalesce
  //Create a new node to celebrate this event

  m_nodes.push_back(
    TreeNode(
      chosen.GetNode(),
      grid_spot_to->GetNode()
    )
  );
  TreeNode * const new_node{&m_nodes.back()};

  chosen.GetNode()->SetParent(new_node);
  grid_spot_to->GetNode()->SetParent(new_node);
  grid_spot_to->SetNode(new_node);

  const double probability{
    chosen.GetProbability()
    + grid_spot_to->GetProbability()
    * (1.0-chosen.GetProbability())
  };

  grid_spot_to->SetProbability(probability);

  //Overwrite chosen by last
  TreeDataPoint& last = m_active.back();
  chosen = last;


  const int last_x = last.GetXpos();
  const int last_y = last.GetYpos();

  assert(IsValid(last_x,last_y,m_grid));
  GridType& last_active_spot = m_grid[last_x][last_y];

  if (last_active_spot == &last)
  {
    last_active_spot = &chosen;
  }
  m_active.pop_back();
}

std::vector<TreeDataPoint> GetRelevantActive(const Tree& tree) noexcept
{
  std::vector<TreeDataPoint> v(
    std::begin(tree.GetActive()) + 1,
    std::end(tree.GetActive())
  );
  return v;
}
