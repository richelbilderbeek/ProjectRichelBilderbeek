#ifndef TREE_H
#define TREE_H

#include <array>
#include <vector>
#include "nrrand.h"
#include "treenode.h"
#include "treedatapoint.h"
#include "dispersalkernel.h"
#include "rng.h"

// this object represents the output coalescence tree itself
// and has all the useful functions - everything above this point is just a tool
// that is required for this object
// the end user should initialise one instance of "tree" and
// use that object to do all their calculations
struct Tree
{
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
    const DispersalKernel dispersal_kernel,
    const bool verbose = false
  );

  double GetError() const noexcept;

  //this returns the midpoint between the maximum and minimum richness estimates
  double GetRichness(const double speciation_rate);

  bool IsDone() const noexcept;

  ///
  void Update();

private:

  // Store the coalescence tree itself
  // there can only be a maximum of twice as many nodes as there are
  // initially free branches so we can set the size of our data object
  std::vector<TreeDataPoint> m_active;

  const int m_dispersal_distance;
  const DispersalKernel m_dispersal_kernel;

  // marks the end of the data array
  // this is so that size can be expanded and contracted easily up to a maximum size
  int m_enddata;

  // grid - this is an internal variable
  // this is necessary for calculations - initialise it as all zeros
  // it will store integers that refer to places in datapoint array "active"
  std::vector<std::vector<int>> m_grid;

  // when producing a coalescence tree, we do so with a minimal speciation rate
  // in mind (to save a lot of computational expense in growing the full tree)
  double m_min_speciation_rate;

  ///The coalescence tree
  std::vector<TreeNode> m_nodes;

  ///Species richness
  double m_richness;

  Rng& m_rnd;

  const double m_tolerance;

  static std::vector<TreeDataPoint> CreateActive(const int area_width, const int area_length);

  static std::vector<std::vector<int>>
    CreateGrid(const int area_width, const int area_length
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
