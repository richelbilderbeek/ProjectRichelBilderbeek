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
#ifndef QTCONCEPTMAPRATECONCEPTDIALOG_H
#define QTCONCEPTMAPRATECONCEPTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtRateConceptDialogNewName; }

namespace ribi {
namespace cmap {

///Rate the focal concept of a sub-ConceptMap.
class QtRateConceptDialogNewName : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  ///concept is the center node
  ///sub_concept_map[0] is the same as concept and might be changed
  ///sub_concept_map is non-const, as GetRatedConcept will produce a new concept
  explicit QtRateConceptDialogNewName(const boost::shared_ptr<ConceptMap> sub_concept_map,
    QWidget* parent = 0);
  QtRateConceptDialogNewName(const QtRateConceptDialogNewName&) = delete;
  QtRateConceptDialogNewName& operator=(const QtRateConceptDialogNewName&) = delete;
  ~QtRateConceptDialogNewName() noexcept;

  ///Set suggested values for this concept
  //void MakeSuggestions(const boost::shared_ptr<const ConceptMap> sub_concept_map);

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_ok_clicked();

  void on_button_tally_relevancies_clicked();

  void on_box_complexity_currentIndexChanged(int index);
  void on_box_concreteness_currentIndexChanged(int index);
  void on_box_specificity_currentIndexChanged(int index);

private:
  Ui::QtRateConceptDialogNewName *ui;

  ///To distinguish between closing the dialog by clicking OK, or by ALT-F4
  bool m_button_ok_clicked;

  ///The center concept, may be changed when the user clicks OK
  const boost::shared_ptr</* NO CONST */ Concept> m_concept;

  ///The complexity at this dialog its creation, stored so that the user can cancel the dialog
  const int m_initial_complexity;
  const int m_initial_concreteness;
  const int m_initial_specificity;

  ///Cannot be const, only used in calculating the suggestions
  const boost::shared_ptr<ConceptMap> m_sub_concept_map;

  const boost::shared_ptr<QtRateConceptMap> m_widget;
  //QtConceptMapRateWidget * const m_widget; //WHY DID I DO THIS???

  void OnRatingComplexityChanged(const Concept* concept);
  void OnRatingConcretenessChanged(const Concept* concept);
  void OnRatingSpecificityChanged(const Concept* concept);

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTCONCEPTMAPRATECONCEPTDIALOG_H
