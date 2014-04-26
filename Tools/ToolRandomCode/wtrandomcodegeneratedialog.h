//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#ifndef WTRANDOMCODEGENERATEDIALOG_H
#define WTRANDOMCODEGENERATEDIALOG_H

#include <Wt/WContainerWidget>

namespace Wt
{
  struct WPushButton;
  struct WTextArea;
}
<<<<<<< HEAD

=======
//---------------------------------------------------------------------------
<<<<<<< HEAD
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
=======
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf

namespace ribi {

struct WtRandomCodeGenerateDialog : public Wt::WContainerWidget
{
  WtRandomCodeGenerateDialog();
  WtRandomCodeGenerateDialog(const WtRandomCodeGenerateDialog&) = delete;
  WtRandomCodeGenerateDialog& operator=(const WtRandomCodeGenerateDialog&) = delete;
  private:
  Wt::WPushButton * const m_button_generate;
  Wt::WTextArea * const m_text_area;
  void OnGenerateClick();
};

} //~namespace ribi

#endif // WTRANDOMCODEGENERATEDIALOG_H
