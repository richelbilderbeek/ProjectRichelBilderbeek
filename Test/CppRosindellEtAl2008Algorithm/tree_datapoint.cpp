#include "tree.h"

tree::datapoint::datapoint()
{

}

// setup all varibles
void tree::datapoint::setup(
  unsigned short x ,
  unsigned short y ,
  unsigned int z)
{
  xpos = x;
  ypos = y;
  xindex = 0;
  yindex = 0;
  next = 0;
  last = 0;
  mpos = z;
  prob = 1.0;
}
// setup all varibles from another datapoint

void tree::datapoint::setup(datapoint datin)
{
  xpos = datin.get_xpos();
  ypos = datin.get_ypos();
  xindex = datin.get_xindex();
  yindex = datin.get_yindex();
  next = datin.get_next();
  last = datin.get_last();
  mpos = datin.get_mpos();
  prob = datin.get_prob();
}

// checks for coalescence with another datapoint
bool tree::datapoint::match(datapoint x ){
  bool result = true;
  if (xpos != x.get_xpos()) result = false;
  if (ypos != x.get_ypos()) result = false;
  return result;
}
// update the position of this datapoint
// this implements the indexing system
void tree::datapoint::move(short x , short y , double z)
{
  int newxpos = xpos + x;
  int newypos = ypos + y;
  while (newxpos < 0)
  {
    newxpos += sm_gridsize;
    xindex --;
  }
  while (newxpos >= sm_gridsize)
  {
    newxpos -= sm_gridsize;
    xindex ++;
  }
  while (newypos < 0)
  {
    newypos += sm_gridsize;
    yindex --;
  }
  while (newypos >= sm_gridsize)
  {
    newypos -= sm_gridsize;
    yindex ++;
  }
  xpos = newxpos;
  ypos = newypos;
  // update prob using z = minspec
  prob = prob*(1.0-z);}

