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
#ifndef UnitEnumPedigreeCharterH
#define UnitEnumPedigreeCharterH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <memory>
#include <map>
//---------------------------------------------------------------------------
enum EnumPedigreeCharter
{
  pedigreeCharterNone,
  pedigreeCharterAll
};
//---------------------------------------------------------------------------
//EnumPedigreeCharterConverter is a Singleton
class EnumPedigreeCharterConverter
{
  public:
    static EnumPedigreeCharterConverter * instance();
    EnumPedigreeCharter toEnum(const std::string&) const;
    std::string toString(const EnumPedigreeCharter&) const;
    void cout(const EnumPedigreeCharter&) const;

  private:
    friend std::auto_ptr<EnumPedigreeCharterConverter>;
    EnumPedigreeCharterConverter();
    ~EnumPedigreeCharterConverter(){};
    const static std::auto_ptr<EnumPedigreeCharterConverter> mpInstance;
    mutable std::map<EnumPedigreeCharter,std::string> mMap;
    mutable std::map<EnumPedigreeCharter,std::string>::const_iterator mIter;

};
//---------------------------------------------------------------------------

#endif
 