#ifndef TREE_H
#define TREE_H

#include <vector>
#include "nrrand.h"
#include "treenode.h"
#include "rng.h"

class Tree
        // this object represents the output coalescence tree itself
        // and has all the useful functions - everything above this point is just a tool
        // that is required for this object
        // the end user should initialise one instance of "tree" and
        // use that object to do all their calculations
{
public:
    Tree(const long seed);
    //PRODUCING A COALESCENCE TREE IN CLASS TREE
    // this is the part of the code that actually creates the colescence tree
    // input variables are described in detail below
    // area1 = width of survey area (in trees)
    // area2 = length of survey area (int trees)
    // minspec = smallest speciation rate required
    // dispersal = dispersal distance (dispersal kernel width)
    // tol = tolerance in results (0.01 means 1% error - 0.5% either side)
    // typeflag deals with the type of dispersal in the model (true means normal)
    void maketree(int area1, int area2, double minspec, int dispersal , double tol, bool normflag);// this returns an interval within which the true mean richness must lie
    std::vector<double> get_richnessint(double spec);
    // this returns the midpoint between the maximum and minimum richness estimates
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
  Rng m_rnd;
  // this is a portable random number generator object
  // please see the separate file for indtructions on use
  // you may use any random number generator, but numerical recipes
  // solutions are highly recommended

  static const int sm_gridsize = 4000;
  friend class TreeDataPoint;
};
#endif // TREE_H
