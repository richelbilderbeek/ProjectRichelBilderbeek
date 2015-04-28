#ifndef TREE_H
#define TREE_H

#include <vector>
#include "nrrand.h"
#include "treenode.h"
#include "dispersalkernel.h"
#include "rng.h"

// this object represents the output coalescence tree itself
// and has all the useful functions - everything above this point is just a tool
// that is required for this object
// the end user should initialise one instance of "tree" and
// use that object to do all their calculations
class Tree
{
public:
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

  // this returns an interval within which the true mean richness must lie
  std::vector<double> GetRichnessInterval(double spec);

  //this returns the midpoint between the maximum and minimum richness estimates
  double get_richness(double spec);

private:
  std::vector<TreeNode> m_nodes;
  // stores the coalescence tree itself
  int m_enddata;
  // marks the end of the data array
  // this is so that size can be expanded and contracted easily up to a maximum size
  double m_minspecsetup;
  // when producing a coalescence tree, we do so with a minimal speciation rate
  // in mind (to save a lot of computational expense in growing the full tree)
  // when true some messages will be printed out for debub purposes
  Rng& m_rnd;
  // this is a portable random number generator object
  // please see the separate file for indtructions on use
  // you may use any random number generator, but numerical recipes
  // solutions are highly recommended

  static std::pair<int,int> GetMove(
    const DispersalKernel kernel,
    Rng& rng,
    const int dispersal
  );

  static std::vector<std::vector<int>>
    CreateGrid(const int area_width, const int area_length
  );


  static const int sm_gridsize = 4000;
  friend class TreeDataPoint;
};
#endif // TREE_H
