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
#ifndef QTCONCEPTMAPEXAMPLESDIALOG_H
#define QTCONCEPTMAPEXAMPLESDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtExamplesDialog; }

namespace ribi {
namespace cmap {

///Displays and modifies Examples
class QtExamplesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtExamplesDialog(QWidget *parent = 0);
  QtExamplesDialog(const QtExamplesDialog&) = delete;
  QtExamplesDialog& operator=(const QtExamplesDialog&) = delete;
  ~QtExamplesDialog();

  void SetExamples(const boost::shared_ptr<Examples>& examples);
  boost::shared_ptr<Examples> GetExamples() const noexcept { return m_examples; }

  ///Something of one of the examples was changed
  mutable boost::signals2::signal<void(QtExamplesDialog*)> m_signal_qtexamplesdialog_changed;

  static int GetMinimumHeight(const Examples& examples) noexcept;

private:
  Ui::QtExamplesDialog *ui;
  std::vector<boost::shared_ptr<QtExampleDialog>> m_dialogs;
  boost::shared_ptr<Examples> m_examples;

  void OnExamplesChanged(Examples* const examples) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi
} //~namespace cmap

#endif // QTCONCEPTMAPEXAMPLESDIALOG_H
