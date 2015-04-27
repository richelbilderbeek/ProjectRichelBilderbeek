#ifndef TREE_H
#define TREE_H

#include <vector>
#include "nrrand.h"
#include "array1d.h"

#include "rng.h"

class tree
        // this object represents the output coalescence tree itself
        // and has all the useful functions - everything above this point is just a tool
        // that is required for this object
        // the end user should initialise one instance of "tree" and
        // use that object to do all their calculations
{
public:
    tree(const long theseed);
    //PRODUCING A COALESCENCE TREE IN CLASS TREE
    // this is the part of the code that actually creates the colescence tree
    // input variables are described in detail below
    // area1 = width of survey area (in trees)
    // area2 = length of survey area (int trees)
    // minspec = smallest speciation rate required
    // dispersal = dispersal distance (dispersal kernel width)
    // tol = tolerance in results (0.01 means 1% error - 0.5% either side)
    // typeflag deals with the type of dispersal in the model (true means normal)
    void maketree(int area1 , int area2 , double minspec , int dispersal , double tol, bool normflag);// this returns an interval within which the true mean richness must lie
    array1D<double> get_richnessint(double spec);
    // this returns the midpoint between the maximum and minimum richness estimates
    double get_richness(double spec);
    class treenode
            // this is a data storage object for the coalescence tree
            // an array of these objects is required to store the whole tree
            // we include a few simple functions that prove useful later
    {
    public:
        treenode();
        void setup(bool root_);
        void set_root(bool root_);
        void set_parent(unsigned int x);
        void set_steps(unsigned int x);
        bool get_root();
        unsigned int get_parent();
        int get_steps();
        // increments the steps by one
        void inc_steps();
    private:
        bool root;
        // is this node at the end of the tree (true)
        // or just here to mark a coalescense (false)
        unsigned int parent;
        // this stores the parent of the individual
        // 0 means there is no parent - we are at the end of the tree
        // (as far as has been calculated)
        unsigned int steps;
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
        void set_pos(unsigned short x , unsigned short y);
        void set_index( short x , short y);
        void set_mpos(unsigned int z);
        void set_next(unsigned int x);
        void set_last(unsigned int x);
        void set_prob(double x);
        unsigned short get_xpos();
        unsigned short get_ypos();
        short get_xindex();
        short get_yindex();
        unsigned int get_mpos();
        unsigned int get_next();
        unsigned int get_last();
        double get_prob();
        // checks for coalescence with another datapoint
        bool match(datapoint x );
        // update the position of this datapoint
        // this implements the indexing system
        void move(short x , short y , double z);
    private:
        unsigned short xpos;// x position
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
    array1D<treenode> data;
    // stores the coalescence tree itself
    unsigned int enddata;
    // marks the end of the data array
    // this is so that size can be expanded and contracted easily up to a maximum size
    double minspecsetup;
    // when producing a coalescence tree, we do so with a minimal speciation rate
    // in mind (to save a lot of computational expense in growing the full tree)
    // when true some messages will be printed out for debub purposes
    //NRrand NR;
    Rng NR;
    // this is a portable random number generator object
    // please see the separate file for indtructions on use
    // you may use any random number generator, but numerical recipes
    // solutions are highly recommended
    bool seeded;
    // a variable that is true when the random number generator seed is set
    std::vector< std::vector<int> > children;
    // this vector stores the extra information needed for Newick outputs
    // it is left clear as standard and only used when needed


  static const int gridsize = 4000;
};
#endif // TREE_H
