//---------------------------------------------------------------------------
/*
TestTwoDigitNewick, tool to test the two-digit-Newick architecture
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#include "twodigitnewickderivative.h"

#include <cassert>

ribi::TwoDigitNewickDerivative::TwoDigitNewickDerivative(
  const int derived_index,
  const int value_changed,
  const int other_value_changed)
  : m_derived_index(derived_index),
    m_value_changed(value_changed),
    m_other_value_changed(other_value_changed)
{
  assert(m_derived_index > 0);
  assert(m_value_changed > 0);
  assert( (m_value_changed == 1 && m_other_value_changed  > 0)
       || (m_value_changed  > 1 && m_other_value_changed == 0) );
}
