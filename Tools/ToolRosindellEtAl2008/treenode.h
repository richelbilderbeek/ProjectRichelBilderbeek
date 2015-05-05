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
#ifndef TREENODE_H
#define TREENODE_H

#include <iosfwd>

///Nodes in a tree
struct TreeNode
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

  ///The parent of this Node
  ///If m_parent == nullptr, this Node has no Parent, i.e. it is a the root of the tree
  Parent m_parent;

  ////The number of generations
  ////between this individual and its parent in the tree
  int m_branch_length;

  ///Probability
  ///  1.0: free branch, because it is certain that the lineages have not encountered speciaiton
  ///       when they are at the very end and no pruning has so far taken place
  /// -2.0: an internal node that has thus far not been pruned at all
  double m_p;
};

bool operator==(const TreeNode& lhs, const TreeNode& rhs) noexcept;
bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const TreeNode& node);

#endif // TREENODE_H
