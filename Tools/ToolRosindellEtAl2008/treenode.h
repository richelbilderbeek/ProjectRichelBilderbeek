#ifndef TREENODE_H
#define TREENODE_H

#include <iosfwd>

struct TreeNode
// this is a data storage object for the coalescence tree
// an array of these objects is required to store the whole tree
// we include a few simple functions that prove useful later
{
  TreeNode(const bool root);
  void SetParent(const int parent) { m_parent = parent; }
  bool GetRoot() const noexcept { return m_root; }
  int GetParent() const noexcept { return m_parent; }
  int GetSteps() const noexcept { return m_steps; }
  void IncSteps() noexcept { ++m_steps; }
private:

  /// is this node at the end of the tree (true)
  /// or just here to mark a coalescense (false)
  bool m_root;

  /// this stores the parent of the individual
  /// 0 means there is no parent - we are at the end of the tree
  /// (as far as has been calculated)
  int m_parent;

  /// the number of generations (chances of speciation)
  /// between this individual and its parent in the tree
  int m_steps;
};

bool operator==(const TreeNode& lhs, const TreeNode& rhs) noexcept;
bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const TreeNode& node);

#endif // TREENODE_H
