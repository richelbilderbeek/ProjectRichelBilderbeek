//---------------------------------------------------------------------------
/*
QtSprites, class to create images by hand
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtSprites.htm
//---------------------------------------------------------------------------
#ifndef QTSPRITES_H
#define QTSPRITES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QPixmap>
#pragma GCC diagnostic pop

namespace ribi {

///QtSprites creates images by hand
struct QtSprites
{
  static QPixmap DrawR();
};

} //~namespace ribi

#endif // QTSPRITES_H
