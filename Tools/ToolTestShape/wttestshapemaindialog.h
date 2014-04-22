//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestShape.htm
//---------------------------------------------------------------------------
#ifndef WTTESTSHAPEMAINDIALOG_H
#define WTTESTSHAPEMAINDIALOG_H

#include <vector>
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>

namespace Wt { struct WLabel; }

namespace ribi {

struct TestShapeMainDialog;
struct WtShapeWidget;

struct WtTestShapeMainDialog : public Wt::WContainerWidget
{
  WtTestShapeMainDialog();
  WtTestShapeMainDialog(const WtTestShapeMainDialog&) = delete;
  WtTestShapeMainDialog& operator=(const WtTestShapeMainDialog&) = delete;

  private:

  boost::scoped_ptr<TestShapeMainDialog> m_dialog;
  std::vector<WtShapeWidget*> m_dialogs;
  Wt::WLabel * m_label_score;
  void OnSubmit();
  void Show();
};

} //~namespace ribi

#endif // WTTESTQUESTIONMAINDIALOG_H
