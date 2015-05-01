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
  m_xindex{other.GetXindex()},
  m_yindex{other.GetYindex()},
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
  this->m_xindex = other.GetXindex();
  this->m_yindex = other.GetYindex();
  this->m_next = other.GetNext();
  this->m_last = other.GetLast();
  this->m_mpos = other.GetMpos();
  this->m_probability = other.GetProbability();
  return *this;
}

// update the position of this datapoint
// this implements the indexing system
void TreeDataPoint::Move(
  const int x,
  const int y,
  const double z
)
{
  int newxpos = m_xpos + x;
  int newypos = m_ypos + y;
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
  // update prob using z = minspec
  m_probability = m_probability*(1.0-z);

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
    && lhs.GetXindex() == rhs.GetXindex()
    && lhs.GetYindex() == rhs.GetYindex()
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
    << point.GetXindex() << " "
    << point.GetYindex() << " "
    << point.GetMpos() << " "
    << point.GetNext() << " "
    << point.GetLast() << " "
    << point.GetProbability()
  ;
  return os;
}
