//---------------------------------------------------------------------------
/*
MultiVector, any-dimensional std::vector class
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppMultiVector.htm
//---------------------------------------------------------------------------
#include "multivector.h"

#ifndef NDEBUG
void ribi::TestMultiVector() noexcept
{
  {
    bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ribi::MultiVector<int> x;
  //1 dimensional
  x.Store( { 0 }, 0);
  x.Store( { 1 }, 1);
  x.Store( { 2 }, 2);
  x.Store( { 3 }, 3);
  x.Store( { 4 }, 4);
  assert(x.Retrieve( { 0 } ) ==  0);
  assert(x.Retrieve( { 1 } ) ==  1);
  assert(x.Retrieve( { 2 } ) ==  2);
  assert(x.Retrieve( { 3 } ) ==  3);
  assert(x.Retrieve( { 4 } ) ==  4);
  //2 dimensional;
  x.Store( { 0,0 },  0);
  x.Store( { 1,1 },  1);
  x.Store( { 2,2 },  4);
  x.Store( { 3,3 },  9);
  x.Store( { 4,4 }, 16);
  assert(x.Retrieve( { 0,0 } ) ==  0);
  assert(x.Retrieve( { 1,1 } ) ==  1);
  assert(x.Retrieve( { 2,2 } ) ==  4);
  assert(x.Retrieve( { 3,3 } ) ==  9);
  assert(x.Retrieve( { 4,4 } ) == 16);
  //3 dimensional;
  x.Store( { 0,0,0 },  0);
  x.Store( { 1,1,1 },  1);
  x.Store( { 2,2,2 },  8);
  x.Store( { 3,3,3 }, 27);
  x.Store( { 4,4,4 }, 54);
  assert(x.Retrieve( { 0,0,0 } ) ==   0);
  assert(x.Retrieve( { 1,1,1 } ) ==   1);
  assert(x.Retrieve( { 2,2,2 } ) ==   8);
  assert(x.Retrieve( { 3,3,3 } ) ==  27);
  assert(x.Retrieve( { 4,4,4 } ) ==  54);
  //4 dimensional;
  x.Store( { 0,0,0,0 },   0);
  x.Store( { 1,1,1,1 },   1);
  x.Store( { 2,2,2,2 },  16);
  x.Store( { 3,3,3,3 },  81);
  x.Store( { 4,4,4,4 }, 216);
  assert(x.Retrieve( { 0,0,0,0 } ) ==   0);
  assert(x.Retrieve( { 1,1,1,1 } ) ==   1);
  assert(x.Retrieve( { 2,2,2,2 } ) ==  16);
  assert(x.Retrieve( { 3,3,3,3 } ) ==  81);
  assert(x.Retrieve( { 4,4,4,4 } ) == 216);
  //5 dimensional;
  x.Store( { 0,0,0,0,0 },   0);
  x.Store( { 1,1,1,1,1 },   1);
  x.Store( { 2,2,2,2,2 },  32);
  x.Store( { 3,3,3,3,3 }, 243);
  x.Store( { 4,4,4,4,4 }, 864);
  assert(x.Retrieve( { 0,0,0,0,0 } ) ==    0);
  assert(x.Retrieve( { 1,1,1,1,1 } ) ==    1);
  assert(x.Retrieve( { 2,2,2,2,2 } ) ==   32);
  assert(x.Retrieve( { 3,3,3,3,3 } ) ==  243);
  assert(x.Retrieve( { 4,4,4,4,4 } ) ==  864);

}
#endif
