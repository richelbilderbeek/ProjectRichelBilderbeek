#include "tree.h"

Tree::treenode::treenode()
{

}
void Tree::treenode::setup(bool root)
// sets up variables with initial conditions
{
  m_root = root;
  m_parent = 0;
  m_steps = 0;
}
