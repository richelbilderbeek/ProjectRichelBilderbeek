//---------------------------------------------------------------------------
/*
TestQtRoundedTextRectItem, tool to test QtRoundedTextRectItem
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQTROUNDEDTEXTRECTITEMWIDGETWIDGET_H
#define QTTESTQTROUNDEDTEXTRECTITEMWIDGETWIDGET_H

#include "qtkeyboardfriendlygraphicsview.h"

struct QFont;

namespace ribi {

///The widget holding the items
struct QtTestQtRoundedTextRectItemWidget : public QtKeyboardFriendlyGraphicsView
{
  QtTestQtRoundedTextRectItemWidget(QWidget *parent = 0);

  void keyPressEvent(QKeyEvent *event) noexcept;

private:
  ///Display a font
  void Display(const QFont& font);
};

} //~namespace ribi

#endif // QTTESTQTROUNDEDTEXTRECTITEMWIDGETWIDGET_H
