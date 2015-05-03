#ifndef TREENODE_H
#define TREENODE_H

#include <iosfwd>

struct TreeNode
// this is a data storage object for the coalescence tree
// an array of these objects is required to store the whole tree
// we include a few simple functions that prove useful later
{
  using Parent = TreeNode*;

  TreeNode(
    TreeNode * const kid_left = nullptr,
    TreeNode * const kid_right = nullptr
  );

  double GetBranchLength() const noexcept {
    return static_cast<double>(m_branch_length);
  }

  Parent GetParent() const noexcept { return m_parent; }
  double GetProbability() const noexcept { return m_p; }

  ///Does this node connect to the present,
  ///or is it created at a coalescent event?
  bool IsRootNode() const noexcept { return m_kid_left == nullptr; }

  void IncreaseBranchLength() noexcept { ++m_branch_length; }
  void SetParent(const Parent parent) noexcept { m_parent = parent; }
  void SetProbability(const double p) noexcept { m_p = p; }

private:

  ///Node connect to the present have no kids,
  ///Nodes created at a coalescent event have two kids:
  ///the lineages that coalesced
  TreeNode * const m_kid_left;
  TreeNode * const m_kid_right;

  /// this stores the parent of the individual
  /// 0 means there is no parent - we are at the end of the tree
  /// (as far as has been calculated)
  Parent m_parent;

  /// the number of generations (chances of speciation)
  /// between this individual and its parent in the tree
  int m_branch_length;

  //Probability
  //  1.0: free branch, because it is certain that the lineages have not encountered speciaiton// when they are at the very end and no pruning has so far taken place
  // -2.0: an internal node that has thus far not been pruned at all
  double m_p;
};

bool operator==(const TreeNode& lhs, const TreeNode& rhs) noexcept;
bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const TreeNode& node);

#endif // TREENODE_H
