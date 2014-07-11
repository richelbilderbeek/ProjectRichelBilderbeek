//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitExceptionsH
#define UnitExceptionsH
//---------------------------------------------------------------------------
#include <exception>
//---------------------------------------------------------------------------
class NoFemaleException : public std::exception
{
  public:
  NoFemaleException() {} //: mWhat("There was no female left") {}
  //const std::string mWhat;
};
//---------------------------------------------------------------------------
class NoMaleException : public std::exception
{
  public:
  NoMaleException() {} //: mWhat("There was no male left") {}
  //const std::string mWhat;
};
//---------------------------------------------------------------------------
class NoCouplesException : public std::exception
{
  public: NoCouplesException() {}
};
//---------------------------------------------------------------------------
class UnknownBirdTypeException : public std::exception
{
  public:
  UnknownBirdTypeException() {} //: mWhat("Unknown bird type") {}
  //const std::string mWhat;
};
//---------------------------------------------------------------------------

#endif
