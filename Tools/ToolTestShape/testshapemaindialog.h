//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
#ifndef TESTSHAPEMAINDIALOG_H
#define TESTSHAPEMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct MultipleChoiceShape;
struct MultipleChoiceShapeDialog;
struct OpenShape;
struct OpenShapeDialog;
struct ShapeWidget;

///The GUI independent TestShape main dialog
struct TestShapeMainDialog
{
  TestShapeMainDialog();

  std::vector<boost::shared_ptr<ShapeWidget> >& GetShapes() { return m_shapes; }

  private:
  std::vector<boost::shared_ptr<ShapeWidget> > m_shapes;

  void OnShapeAnswered();

  static std::vector<boost::shared_ptr<ShapeWidget> > CreateShapes();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTSHAPEMAINDIALOG_H
