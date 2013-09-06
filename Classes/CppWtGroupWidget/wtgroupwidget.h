//---------------------------------------------------------------------------
/*
WtGroupWidget, Wt widget for displaying groups
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtGroupWidget.htm
//---------------------------------------------------------------------------
#ifndef WTGROUPWIDGET_H
#define WTGROUPWIDGET_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------

namespace ribi {

///WtGroupWidget displays a collection of ID's
struct WtGroupWidget : public Wt::WPaintedWidget
{
  WtGroupWidget();

  void SetIds(const std::vector<std::vector<int> >& v);

  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:
  void DoRepaint();
  std::vector<std::vector<int> > m_v;

  static int GetMax(const std::vector<std::vector<int> >& v);
};

} //~namespace ribi

#endif // WTGROUPWIDGET_H
