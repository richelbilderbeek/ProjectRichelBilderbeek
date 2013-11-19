//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
/*

#include "codetohtmltechinfotype.h"

#include <cassert>
#include <stdexcept>


namespace c2h {

bool CanStrToTechInfoType(const std::string& s)
{
  try
  {
    StrToTechInfoType(s);
    return true;
  }
  catch (std::logic_error&)
  {
    return false;
  }
}

const std::string TechInfoTypeToStr(const TechInfoType t)
{
  switch (t)
  {
    case TechInfoType::automatic: return "automatic";
    case TechInfoType::no: return "no";
    case TechInfoType::yes: return "yes";
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::TechInfoTypeToStr");
}

const std::vector<TechInfoType> GetAllTechInfoTypes()
{
  return
  {
    TechInfoType::automatic,
    TechInfoType::no,
    TechInfoType::yes
  };
}

TechInfoType StrToTechInfoType(const std::string& s)
{
  if (s == "automatic") return TechInfoType::automatic;
  if (s == "no") return TechInfoType::no;
  if (s == "yes") return TechInfoType::yes;
  throw std::logic_error("Invalid string in StrToTechInfoType");
}

} //~namespace CodeToHtml

*/
