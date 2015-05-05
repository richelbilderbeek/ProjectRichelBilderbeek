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
#ifndef TREE_H
#define TREE_H

#include <array>
#include <vector>
#include "nrrand.h"
#include "treenode.h"
#include "treedatapoint.h"
#include "dispersalkernel.h"
#include "rng.h"
//#include "grid.h"

// this object represents the output coalescence tree itself
// and has all the useful functions - everything above this point is just a tool
// that is required for this object
// the end user should initialise one instance of "tree" and
// use that object to do all their calculations
struct Tree
{
  using GridType = TreeDataPoint*;
  using Grid = std::vector<std::vector<GridType>>;
  using TreeNodes = std::vector<TreeNode>;

  // area_width = width of survey area (in number of trees)
  // area_length = length of survey area (in number of trees)
  // min_speciation_rate = smallest speciation rate required
  Tree(
    Rng& rng,
    const int area_width,
    const int area_length,
    const double min_speciation_rate,
    const int dispersal_distance,
    const double tolerance,
    const DispersalKernel dispersal_kernel
  );

  void DisplayActive(std::ostream& os) const noexcept;

  const std::vector<TreeDataPoint>& GetActive() const noexcept { return m_active; }

  double GetError() const noexcept;

  //this returns the midpoint between the maximum and minimum richness estimates
  double GetRichness(const double speciation_rate);

  bool IsDone() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///
  void Update();

private:

  // Store the coalescence tree itself
  // there can only be a maximum of twice as many nodes as there are
  // initially free branches so we can set the size of our data object
  std::vector<TreeDataPoint> m_active;

  const int m_area_width;
  const int m_area_length;

  const int m_dispersal_distance;
  const DispersalKernel m_dispersal_kernel;

  // grid - this is an internal variable
  // this is necessary for calculations - initialise it as all zeros
  // it will store integers that refer to places in datapoint array "active"
  Grid m_grid;

  // when producing a coalescence tree, we do so with a minimal speciation rate
  // in mind (to save a lot of computational expense in growing the full tree)
  double m_min_speciation_rate;

  ///The coalescence tree
  std::vector<TreeNode> m_nodes;

  ///Species richness
  double m_richness;

  Rng& m_rnd;

  const double m_tolerance;

  static std::vector<TreeDataPoint> CreateActive(
    const int area_width,
    const int area_length,
    TreeNodes& nodes
  );

  static Grid
    CreateGrid(
      const int area_width,
      const int area_length,
      std::vector<TreeDataPoint>& datapoints
  );

  ///Where will the next position be?
  static std::pair<int,int> GetMove(
    const DispersalKernel kernel,
    Rng& rng,
    const int dispersal
  );

  ///Interval within which the true mean richness must lie
  std::array<double,2> GetRichnessInterval(double spec);


  static const int sm_gridsize = 4000;
  friend class TreeDataPoint;
};
#endif // TREE_H

std::vector<TreeDataPoint> GetRelevantActive(const Tree& tree) noexcept;
