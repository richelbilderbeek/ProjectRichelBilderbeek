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
