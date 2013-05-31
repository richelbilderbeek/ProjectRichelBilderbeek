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
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WGridLayout>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WSlider>
//---------------------------------------------------------------------------
#include "shape.h"
#include "shapewidget.h"
#include "testshapemaindialog.h"
#include "wtaboutdialog.h"
#include "wtshapewidget.h"
#include "wttestshapemaindialog.h"
//---------------------------------------------------------------------------
WtTestShapeMainDialog::WtTestShapeMainDialog()
  : m_dialog(new TestShapeMainDialog),
    m_label_score(0)
{
  Show();
}
//---------------------------------------------------------------------------
void WtTestShapeMainDialog::Show()
{
  clear();
  setContentAlignment(Wt::AlignCenter);

  Wt::WGridLayout * const layout = new Wt::WGridLayout(this);

  int i=0;
  BOOST_FOREACH(boost::shared_ptr<ShapeWidget>& widget,
    m_dialog->GetShapes())
  {
    layout->addWidget(
      new WtShapeWidget(widget),
      i/8,
      i%8,1,1);
    ++i;
  }
}
//---------------------------------------------------------------------------
