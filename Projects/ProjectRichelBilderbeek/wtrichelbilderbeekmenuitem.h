//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010 Richel Bilderbeek

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
#ifndef WTRICHELBILDERBEEKMENUITEM_H
#define WTRICHELBILDERBEEKMENUITEM_H

#include <cassert>
#include <string>
#include <boost/function.hpp>
namespace Wt { struct WStackedWidget; }
namespace Wt { struct WWidget; }

namespace ribi {

namespace RichelBilderbeek {

struct WtMenuDialog;

struct WtMenuItem
{
  explicit WtMenuItem(
    const std::string& caption,
    Wt::WStackedWidget * stack,
    const int index,
    const boost::function<Wt::WWidget * (WtMenuDialog*)> create_dialog_function
      )
    :  m_caption(caption),
       m_stack(stack),
       m_index(index),
       m_create_dialog_function(create_dialog_function)
  {
    assert(!m_caption.empty());
    assert(m_stack);
    assert(m_index >=0 );
    assert(m_create_dialog_function);
  }
  WtMenuItem(const WtMenuItem&) = delete;
  WtMenuItem& operator=(const WtMenuItem&) = delete;

  const std::string& GetCaption() const { return m_caption; }
  Wt::WStackedWidget * GetStack() const { return m_stack; }
  int GetIndex() const { return m_index; }
  const boost::function<Wt::WWidget * (WtMenuDialog*)> GetCreateDialogFunction() const { return m_create_dialog_function; }


  private:
  std::string m_caption;
  Wt::WStackedWidget * m_stack;
  int m_index;
  boost::function<Wt::WWidget * (WtMenuDialog*)> m_create_dialog_function;

};

} //~namespace RichelBilderbeek
} //~namespace ribi

#endif // WTRICHELBILDERBEEKMENUITEM_H
