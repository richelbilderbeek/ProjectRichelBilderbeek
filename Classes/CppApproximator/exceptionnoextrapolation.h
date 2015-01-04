//---------------------------------------------------------------------------
/*
Approximator, class for approximating values by interpolation
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppApproximator.htm
//---------------------------------------------------------------------------
#ifndef RIBI_EXCEPTIONNOEXTRAPOLATION_H
#define RIBI_EXCEPTIONNOEXTRAPOLATION_H

#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace ribi {

template <class T>
struct ExceptionNoExtrapolation : public std::exception
{
  ExceptionNoExtrapolation(
    const T& value)
    : m_is_above_max{false},
      m_is_below_min{false},
      m_what{
        "Value of "
      + boost::lexical_cast<std::string>(value)
      + " out of range [unknown]"
    }
  {

  }

  ExceptionNoExtrapolation(
    const T& value, const T& lowest, const T& highest)
    : m_is_above_max{value > highest},
      m_is_below_min{value < lowest},
      m_what{
        "Value of "
      + boost::lexical_cast<std::string>(value)
      + " out of range ["
      + boost::lexical_cast<std::string>(lowest)
      + " , "
      + boost::lexical_cast<std::string>(highest)
      + "]"
    }
  {

  }
  bool IsAboveMax() const noexcept { return m_is_above_max; }
  bool IsBelowMin() const noexcept { return m_is_below_min; }
  const char * what() const throw() override { return m_what.c_str(); }
  private:

  const bool m_is_above_max;
  const bool m_is_below_min;
  ///The error message
  const std::string m_what;
};

} //~namespace ribi


#endif // RIBI_EXCEPTIONNOEXTRAPOLATION_H
