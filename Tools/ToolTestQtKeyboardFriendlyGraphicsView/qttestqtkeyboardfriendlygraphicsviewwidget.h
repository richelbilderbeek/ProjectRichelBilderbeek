//---------------------------------------------------------------------------
/*
TestKeyboardFriendlyGraphicsView, tests QtKeyboardFriendlyGraphicsView
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
#ifndef QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWWIDGET_H
#define QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include "qtkeyboardfriendlygraphicsview.h"

namespace ribi {

///QtTestKeyboardFriendlyGraphicsViewWidget displays my widgets and their relations
struct QtTestKeyboardFriendlyGraphicsViewWidget : public QtKeyboardFriendlyGraphicsView
{
  typedef QtTestKeyboardFriendlyGraphicsViewWidget This;

  QtTestKeyboardFriendlyGraphicsViewWidget();
  ~QtTestKeyboardFriendlyGraphicsViewWidget() noexcept {}

  ///Signal emitted when the user wants to see the about screen
  boost::signals2::signal<void()> m_signal_request_about;

  ///Signal emitted when the user wants to quit
  boost::signals2::signal<void()> m_signal_request_quit;

protected:

  void keyPressEvent(QKeyEvent *event) noexcept;

private:

  ///Update the view
  void DoUpdateScene();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTKEYBOARDFRIENDLYGRAPHICSVIEWWIDGET_H
