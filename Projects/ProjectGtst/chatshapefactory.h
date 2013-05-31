//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#ifndef PROJECTGTSTCHATSHAPEFACTORY_H
#define PROJECTGTSTCHATSHAPEFACTORY_H
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------
////brief
///ChatShapeFactory creates WtShapeWidgets used as chat shapes
struct ChatShapeFactory : public boost::noncopyable
{
  ///Obtain the instance of the ChatShapeFactory
  static ChatShapeFactory * Get();

  ///Obtain the next ShapeWidget
  const boost::shared_ptr<ShapeWidget> GetNextWidget();

  ///Let the Factory produce the first shape again
  void Reset();

  private:
  ///A Singleton has a private constructor
  ChatShapeFactory();

  ///Only allow a Boost smart pointer to delete ChatShapeFactory
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ChatShapeFactory() {}
  ///Only allow a Boost smart pointer to delete ChatShapeFactory
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ChatShapeFactory*);

  ///The instance
  static boost::scoped_ptr<ChatShapeFactory> m_instance;

  ///All the ShapeWidgets
  const std::vector<boost::shared_ptr<ShapeWidget> > m_widgets;

  ///The index in m_widgets
  int m_i;

  static const std::vector<boost::shared_ptr<ShapeWidget> > CreateWidgets(const int n);
};
//---------------------------------------------------------------------------
#endif // CHATSHAPEFACTORY_H
