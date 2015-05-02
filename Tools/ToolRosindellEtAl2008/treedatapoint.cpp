#include "treedatapoint.h"

#include <cassert>
#include <ostream>

#include "tree.h"

TreeDataPoint::TreeDataPoint(
  const int x,
  const int y,
  const int mpos
)
  :
  m_xpos{x},
  m_ypos{y},
  m_xindex{0},
  m_yindex{0},
  m_next{0},
  m_last{0},
  m_mpos{mpos},
  m_probability{1.0}
{
  static_assert(TreeDataPoint::sm_gridsize == Tree::sm_gridsize,"");
}

TreeDataPoint::TreeDataPoint(
  const TreeDataPoint& other
)
  :
  m_xpos{other.GetXpos()},
  m_ypos{other.GetYpos()},
  m_xindex{other.GetTileX()},
  m_yindex{other.GetTileY()},
  m_next{other.GetNext()},
  m_last{other.GetLast()},
  m_mpos{other.GetMpos()},
  m_probability{other.GetProbability()}
{
  static_assert(TreeDataPoint::sm_gridsize == Tree::sm_gridsize,"");
}

TreeDataPoint& TreeDataPoint::operator=(
  const TreeDataPoint& other
)
{
  this->m_xpos = other.GetXpos();
  this->m_ypos = other.GetYpos();
  this->m_xindex = other.GetTileX();
  this->m_yindex = other.GetTileY();
  this->m_next = other.GetNext();
  this->m_last = other.GetLast();
  this->m_mpos = other.GetMpos();
  this->m_probability = other.GetProbability();
  return *this;
}

// update the position of this datapoint
// this implements the indexing system
void TreeDataPoint::Move(
  const int dx,
  const int dy,
  const double p
)
{
  int newxpos = m_xpos + dx;
  int newypos = m_ypos + dy;
  while (newxpos < 0)
  {
    newxpos += sm_gridsize;
    --m_xindex;
  }
  while (newxpos >= sm_gridsize)
  {
    newxpos -= sm_gridsize;
    ++m_xindex;
  }
  while (newypos < 0)
  {
    newypos += sm_gridsize;
    --m_yindex;
  }
  while (newypos >= sm_gridsize)
  {
    newypos -= sm_gridsize;
    ++m_yindex;
  }
  m_xpos = newxpos;
  m_ypos = newypos;
  //1.0-p : chance not to speciate
  m_probability = m_probability*(1.0-p);

  assert(m_xpos >= 0);
  assert(m_xpos < sm_gridsize);
  assert(m_ypos >= 0);
  assert(m_ypos < sm_gridsize);
  assert(m_probability >= 0.0);
  assert(m_probability <= 1.0);
}

bool operator==(const TreeDataPoint& lhs, const TreeDataPoint& rhs) noexcept
{
  return
       lhs.GetXpos() == rhs.GetXpos()
    && lhs.GetYpos() == rhs.GetYpos()
    && lhs.GetTileX() == rhs.GetTileX()
    && lhs.GetTileY() == rhs.GetTileY()
    && lhs.GetMpos() == rhs.GetMpos()
    && lhs.GetNext() == rhs.GetNext()
    && lhs.GetLast() == rhs.GetLast()
    && lhs.GetProbability() == rhs.GetProbability()
  ;
}

std::ostream& operator<<(std::ostream& os, const TreeDataPoint& point) noexcept
{
  os
    << point.GetXpos() << " "
    << point.GetYpos() << " "
    << point.GetTileX() << " "
    << point.GetTileY() << " "
    << point.GetMpos() << " "
    << point.GetNext() << " "
    << point.GetLast() << " "
    << point.GetProbability()
  ;
  return os;
}
