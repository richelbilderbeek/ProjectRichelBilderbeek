//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm
//---------------------------------------------------------------------------
#ifndef WTRICHELBILDERBEEKGALLERYMENUDIALOG_H
#define WTRICHELBILDERBEEKGALLERYMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtRichelBilderbeekGalleryMenuDialog : public Wt::WContainerWidget
{
  WtRichelBilderbeekGalleryMenuDialog();

  private:
  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};

} //~namespace ribi

#endif // WTRICHELBILDERBEEKGALLERYMENUDIALOG_H
