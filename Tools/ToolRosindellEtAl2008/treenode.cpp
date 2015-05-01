#include "treenode.h"

#include <iostream>

TreeNode::TreeNode(const bool root)
  : m_root{root},
    m_parent{0},
    m_steps{0}
{

}

bool operator==(const TreeNode& lhs, const TreeNode& rhs) noexcept
{
  return
       lhs.GetParent()  == rhs.GetParent()
    && lhs.GetRoot() == rhs.GetRoot()
    && lhs.GetSteps() == rhs.GetSteps()
  ;
}

bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const TreeNode& node)
{
  os
    << node.GetRoot() << " "
    << node.GetParent() << " "
    << node.GetSteps()
  ;
  return os;
}
