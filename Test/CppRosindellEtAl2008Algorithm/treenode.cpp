#include "treenode.h"

TreeNode::TreeNode()
{

}
void TreeNode::setup(bool root)
// sets up variables with initial conditions
{
  m_root = root;
  m_parent = 0;
  m_steps = 0;
}
