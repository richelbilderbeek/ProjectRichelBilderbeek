#ifndef TREENODE_H
#define TREENODE_H

#include <iosfwd>

struct TreeNode
// this is a data storage object for the coalescence tree
// an array of these objects is required to store the whole tree
// we include a few simple functions that prove useful later
{
  using Parent = TreeNode*;

  TreeNode(const bool root = true);
  void SetParent(const Parent parent) { m_parent = parent; }
  bool GetRoot() const noexcept { return m_root; }
  double GetProbability() const noexcept { return m_p; }
  Parent GetParent() const noexcept { return m_parent; }
  int GetSteps() const noexcept { return m_steps; }
  void IncSteps() noexcept { ++m_steps; }
  void SetProbability(const double p) { m_p = p; }
private:

  /// is this node at the end of the tree (true)
  /// or just here to mark a coalescense (false)
  bool m_root;

  /// this stores the parent of the individual
  /// 0 means there is no parent - we are at the end of the tree
  /// (as far as has been calculated)
  Parent m_parent;

  /// the number of generations (chances of speciation)
  /// between this individual and its parent in the tree
  int m_steps;

  //Probability
  double m_p;
};

bool operator==(const TreeNode& lhs, const TreeNode& rhs) noexcept;
bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const TreeNode& node);

#endif // TREENODE_H
