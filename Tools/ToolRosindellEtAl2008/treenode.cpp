#include "treenode.h"

#include <cassert>
#include <iostream>

TreeNode::TreeNode(
  TreeNode * const kid_left,
  TreeNode * const kid_right
)
  : //m_root{root},
    m_kid_left{kid_left},
    m_kid_right{kid_right},
    m_parent{nullptr},
    m_branch_length{0},
    m_p{0.0}
{

}

bool operator==(const TreeNode& lhs, const TreeNode& rhs) noexcept
{
  return
       lhs.GetParent()  == rhs.GetParent()
    && lhs.IsRootNode() == rhs.IsRootNode()
    && lhs.GetBranchLength() == rhs.GetBranchLength()
  ;
}

bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const TreeNode& node)
{
  os
    << node.IsRootNode() << " "
    << node.GetParent() << " "
    << node.GetBranchLength()
  ;
  return os;
}
