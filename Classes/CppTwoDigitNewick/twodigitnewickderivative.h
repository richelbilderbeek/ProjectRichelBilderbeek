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
#ifndef TWODIGITDERIVATIVE_H
#define TWODIGITDERIVATIVE_H

namespace ribi {

///TwoDigitNewickDerivative contains
///the index of the derived phylogeny
///and the value that must be changed
///to get there. For example, if for a
///complex phylogeny (of unknown index)
///a '3' must be changed to a '2' to get
///to the phylogeny with index 42,
///TwoDigitNewickDerivatives has an
///m_derived_index of 42 and an
///m_value_changed of 3.
///For calculations it is important to know which value
///has changed, sometimes with another.
///If no other value changes, set m_other_value_changed to zero.
///Some examples of using m_value_changed and m_other_value_changed:\n
///(1,1) ->   (2), then m_value_changed == 1 && m_other_value_changed == 1\n
///(1,2) ->   (3), then m_value_changed == 1 && m_other_value_changed == 2\n
///(1,2) -> (1,1), then m_value_changed == 2 && m_other_value_changed == 0\n
///(1,3) ->   (4), then m_value_changed == 1 && m_other_value_changed == 3\n
///(1,3) -> (1,2), then m_value_changed == 3 && m_other_value_changed == 0\n
///(2,3) -> (1,3), then m_value_changed == 2 && m_other_value_changed == 0\n
///(2,3) -> (2,2), then m_value_changed == 3 && m_other_value_changed == 0\n
///A valid TwoDigitNewickDerivative has either:\n
///- m_value_changed == 1 && m_other_value_changed  > 0\n
///- m_value_changed  > 1 && m_other_value_changed == 0\n
///This is checked at the constructor
struct TwoDigitNewickDerivative
{
  TwoDigitNewickDerivative(
    const int derived_index,
    const int value_changed,
    const int other_value);

  int m_derived_index;
  int m_value_changed;
  int m_other_value_changed;
};

} //~namespace ribi

#endif // TWODIGITDERIVATIVE_H
