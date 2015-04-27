#ifndef TREENODE_H
#define TREENODE_H

struct TreeNode
// this is a data storage object for the coalescence tree
// an array of these objects is required to store the whole tree
// we include a few simple functions that prove useful later
{
  TreeNode(const bool root);
  //void setup(const bool root);
  void set_root(const bool root) { m_root = root; }
  void set_parent(const int parent) { m_parent = parent; }
  void set_steps(const int steps) noexcept { m_steps = steps; }
  bool get_root() const noexcept { return m_root; }
  int get_parent() const noexcept { return m_parent; }
  int get_steps() const noexcept { return m_steps; }
  // increments the steps by one
  void inc_steps() noexcept { ++m_steps; }
private:
  bool m_root;
  // is this node at the end of the tree (true)
  // or just here to mark a coalescense (false)
  int m_parent;
  // this stores the parent of the individual
  // 0 means there is no parent - we are at the end of the tree
  // (as far as has been calculated)
  int m_steps;
  // the number of generations (chances of speciation)
  // between this individual and its parent in the tree
};

#endif // TREENODE_H
