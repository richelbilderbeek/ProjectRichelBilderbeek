#include "treenode.h"

TreeNode::TreeNode(const bool root)
  : m_root{root},
    m_parent{0},
    m_steps{0}
{

}
/*
void TreeNode::setup(bool root)
{
  m_root = root;
  m_parent = 0;
  m_steps = 0;
}
*/
