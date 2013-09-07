//---------------------------------------------------------------------------
/*
TestMultiVector, tests the MultiVector class
Copyright (C) 2011  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestMultiVector.htm
//---------------------------------------------------------------------------
#include <cassert>
#include "multivector.h"

int main()
{
  ribi::MultiVector<int> x;
  //1 dimensional
  //C++11 initialization
  x.Store( { 0 }, 0);
  x.Store( { 1 }, 1);
  x.Store( { 2 }, 2);
  x.Store( { 3 }, 3);
  assert(x.Retrieve( { 0 } ) ==  0);
  assert(x.Retrieve( { 1 } ) ==  1);
  assert(x.Retrieve( { 2 } ) ==  2);
  assert(x.Retrieve( { 3 } ) ==  3);
  //2 dimensional;
  x.Store( { 0,0 }, 0);
  x.Store( { 1,1 }, 1);
  x.Store( { 2,2 }, 4);
  x.Store( { 3,3 }, 9);
  assert(x.Retrieve( { 0,0 } ) ==  0);
  assert(x.Retrieve( { 1,1 } ) ==  1);
  assert(x.Retrieve( { 2,2 } ) ==  4);
  assert(x.Retrieve( { 3,3 } ) ==  9);
  //3 dimensional;
  x.Store( { 0,0,0 },  0);
  x.Store( { 1,1,1 },  1);
  x.Store( { 2,2,2 },  8);
  x.Store( { 3,3,3 }, 27);
  assert(x.Retrieve( { 0,0,0 } ) ==   0);
  assert(x.Retrieve( { 1,1,1 } ) ==   1);
  assert(x.Retrieve( { 2,2,2 } ) ==   8);
  assert(x.Retrieve( { 3,3,3 } ) ==  27);
}
