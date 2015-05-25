//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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
#ifndef QTCONCEPTMAPCONCEPTEDITDIALOG_H
#define QTCONCEPTMAPCONCEPTEDITDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

struct QListWidgetItem;

namespace Ui { class QtConceptMapConceptEditDialog; }

namespace ribi {
namespace cmap {

class QtConceptMapConceptEditDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///concept is not const as user might want to modify it
  ///concept is only modified if user clicks OK
  explicit QtConceptMapConceptEditDialog(
    const boost::shared_ptr<Concept> concept,
    QWidget* parent = 0);
  QtConceptMapConceptEditDialog(const QtConceptMapConceptEditDialog&) = delete;
  QtConceptMapConceptEditDialog& operator=(const QtConceptMapConceptEditDialog&) = delete;
  ~QtConceptMapConceptEditDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void RemoveEmptyItem(QListWidgetItem * item);

  void on_button_add_clicked();

  ///Finally convert what the GUI displays to a Concept
  void on_button_ok_clicked();

private:
  Ui::QtConceptMapConceptEditDialog *ui;


#ifdef CONCEPTMAP_WRITE_TO_CONCEPT
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specificity;
#else
  ///The concept being modified, cannot be const
  const boost::shared_ptr<Concept> m_concept;

#endif

  ///Test this class
  static void Test() noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTEDITDIALOG_H
