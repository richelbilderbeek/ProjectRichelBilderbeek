#ifndef TREE_H
#define TREE_H

#include <vector>
#include "nrrand.h"

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
    class treenode
    // this is a data storage object for the coalescence tree
    // an array of these objects is required to store the whole tree
    // we include a few simple functions that prove useful later
    {
    public:
        treenode();
        void setup(bool root);
        void set_root(bool root) { m_root = root; }
        void set_parent(unsigned int x) { m_parent = x; }
        void set_steps(unsigned int x) noexcept { m_steps = x; }
        bool get_root() const noexcept { return m_root; }
        unsigned int get_parent() const noexcept { return m_parent; }
        int get_steps() const noexcept { return m_steps; }
        // increments the steps by one
        void inc_steps() noexcept { ++m_steps; }
    private:
        bool m_root;
        // is this node at the end of the tree (true)
        // or just here to mark a coalescense (false)
        unsigned int m_parent;
        // this stores the parent of the individual
        // 0 means there is no parent - we are at the end of the tree
        // (as far as has been calculated)
        unsigned int m_steps;
        // the number of generations (chances of speciation)
        // between this individual and its parent in the tree
    };

    class datapoint
            // this is a data object used in the routine for caluating the coalescence tree
            // but does not form part of the output itself
            // it is meant as a tool for performing the coalescence itself
            // this object includes all the mechanism required for the indexing system
            // indexing is what allows infinite areas to be simulated efficiently
    {
    public:
        datapoint();
        void setup(unsigned short x , unsigned short y , unsigned int z);
        void setup(datapoint datin);
        void set_pos(unsigned short any_xpos, unsigned short any_ypos) noexcept { xpos = any_xpos; ypos = any_ypos; }
        void set_index( short x , short y) noexcept { xindex = x; yindex = y; }
        void set_mpos(unsigned int z) { mpos = z; }
        void set_next(unsigned int x) { next = x; }
        void set_last(unsigned int x) { last = x; }
        void set_prob(double x) { prob = x; }
        unsigned short get_xpos() const noexcept { return xpos; }
        unsigned short get_ypos() const noexcept { return ypos; }
        short get_xindex() const noexcept { return xindex; }
        short get_yindex() const noexcept { return yindex; }
        unsigned int get_mpos() const noexcept { return mpos; }
        unsigned int get_next() const noexcept { return next; }
        unsigned int get_last() const noexcept { return last; }
        double get_prob() const noexcept { return prob; }
        // checks for coalescence with another datapoint
        bool match(datapoint x );
        // update the position of this datapoint
        // this implements the indexing system
        void move(short x , short y , double z);
    private:
        unsigned short xpos;
        unsigned short ypos;
        // y position
        short xindex;
        // number of wraps of x around the torus
        short yindex;
        // number of wraps of y around the torus
        unsigned int next;
        // the next individual in the loop of those that have the same xypos
        unsigned int last;
        // the last individual in the loop 0 means the only one
        unsigned int mpos;
        // points to the position in output of this lineage
        double prob;
        // the probability of not having speciated yet
        // this is to allow the coalescence tree calculation to be stopped
        // prematurely - saving many calculations with minimal loss in accuracy
    };
private:
  std::vector<treenode> m_nodes;
  // stores the coalescence tree itself
  unsigned int m_enddata;
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
};
#endif // TREE_H
