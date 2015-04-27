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
       lhs.get_parent()  == rhs.get_parent()
    && lhs.get_root() == rhs.get_root()
    && lhs.get_steps() == rhs.get_steps()
  ;
}

bool operator!=(const TreeNode& lhs, const TreeNode& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const TreeNode& node)
{
  os
    << node.get_root() << " "
    << node.get_parent() << " "
    << node.get_steps()
  ;
  return os;
}
