//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#ifndef QTRICHELBILDERBEEKMENUITEMWIDGET_H
#define QTRICHELBILDERBEEKMENUITEMWIDGET_H

#include <boost/signals2.hpp>
#include "qtkeyboardfriendlygraphicsview.h"
#include "richelbilderbeekprogramtype.h"

namespace ribi {

///The widget holding the items
///Its purpose is:
/// - obtain and display all applications' names
/// - allow a user to select one
/// - emit m_signal_show with the name of the application the user selected
struct QtRichelBilderbeekMenuItemWidget : public QtKeyboardFriendlyGraphicsView
{
  QtRichelBilderbeekMenuItemWidget(
    QWidget *parent = 0);

  ~QtRichelBilderbeekMenuItemWidget() noexcept {}

  void keyPressEvent(QKeyEvent *event) noexcept;

  ///Emitted when the user wants to start an application
  ///The string passed is the text on the item
  //boost::signals2::signal<void(const std::string)> m_signal_show;
  boost::signals2::signal<void(const ribi::ProgramType)> m_signal_show;
};

} //~namespace ribi

#endif // QTRICHELBILDERBEEKMENUITEMWIDGET_H
