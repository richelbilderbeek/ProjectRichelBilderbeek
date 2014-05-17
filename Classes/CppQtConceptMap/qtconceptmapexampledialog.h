//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPEXAMPLEDIALOG_H
#define QTCONCEPTMAPEXAMPLEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapExampleDialog; }

namespace ribi {
namespace cmap {

///Displays and modifies an Example
class QtConceptMapExampleDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtConceptMapExampleDialog(QWidget *parent = 0);
  QtConceptMapExampleDialog(const QtConceptMapExampleDialog&) = delete;
  QtConceptMapExampleDialog& operator=(const QtConceptMapExampleDialog&) = delete;
  ~QtConceptMapExampleDialog();

  void SetExample(const boost::shared_ptr<Example>& example);
  boost::shared_ptr<Example> GetExample() const noexcept { return m_example; }

private:
  Ui::QtConceptMapExampleDialog *ui;

  ///The Example to work on
  boost::shared_ptr<Example> m_example;

  void OnCompetencyChanged(const Example * const example);
  void OnIsComplexChanged(const Example * const example);
  void OnIsConcreteChanged(const Example * const example);
  void OnIsSpecificChanged(const Example * const example);
  void OnTextChanged(const Example * const example);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPEXAMPLEDIALOG_H
