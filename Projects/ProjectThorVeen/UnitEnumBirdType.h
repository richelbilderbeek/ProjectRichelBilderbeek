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
#ifndef UnitEnumBirdTypeH
#define UnitEnumBirdTypeH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <memory>
#include <map>
//---------------------------------------------------------------------------
enum EnumBirdType
{
  hawkDove
};
//---------------------------------------------------------------------------
//EnumBirdTypeConverter is a Singleton
class EnumBirdTypeConverter
{
  public:
    static EnumBirdTypeConverter * instance();
    EnumBirdType toEnum(const std::string&) const;
    std::string toString(const EnumBirdType&) const;
    void cout(const EnumBirdType&) const;

  private:
    friend std::auto_ptr<EnumBirdTypeConverter>;
    EnumBirdTypeConverter();
    ~EnumBirdTypeConverter(){};
    const static std::auto_ptr<EnumBirdTypeConverter> mpInstance;
    mutable std::map<EnumBirdType,std::string> mMap;
    mutable std::map<EnumBirdType,std::string>::const_iterator mIter;

};
//---------------------------------------------------------------------------

#endif
