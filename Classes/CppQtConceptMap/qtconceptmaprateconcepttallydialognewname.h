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
#ifndef QTCONCEPTMAPRATECONCEPTTALLYDIALOG_H
#define QTCONCEPTMAPRATECONCEPTTALLYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtRateConceptTallyDialogNewName; }

namespace ribi {
namespace cmap {

class QtRateConceptTallyDialogNewName : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///Sub concept map is modified by this dialog
  explicit QtRateConceptTallyDialogNewName(
    const boost::shared_ptr</* const */ ConceptMap> sub_concept_map,
    QWidget *parent = 0);
  QtRateConceptTallyDialogNewName(const QtRateConceptTallyDialogNewName&) = delete;
  QtRateConceptTallyDialogNewName& operator=(const QtRateConceptTallyDialogNewName&) = delete;
  ~QtRateConceptTallyDialogNewName() noexcept;

  static const boost::shared_ptr<ConceptMap> CreateTestConceptMap();

  ///Obtain the suggested complexity, calculated from this dialog
  int GetSuggestedComplexity() const;

  ///Obtain the suggested concreteness, calculated from this dialog
  int GetSuggestedConcreteness() const;

  ///Obtain the suggested specificity, calculated from this dialog
  int GetSuggestedSpecificity() const;

protected:
  void keyPressEvent(QKeyEvent *);
  void resizeEvent(QResizeEvent *);
private slots:
  void on_button_ok_clicked();
  void OnCellChanged(int row, int col);

private:
  Ui::QtRateConceptTallyDialogNewName *ui;
  //const boost::shared_ptr</* const */ ConceptMap> m_map;

  ///The concept map is converted to this data type
  ///The std::vector index equals the row
  ///Every row is a pair of a boost::shared_ptr<Concept> and an integer
  ///The boost::shared_ptr<Concept> is the concept being judged,
  ///  which might be the concept on the focal node and the concept on the egdes connected to the focal node
  ///The index is the index of the example being judged, or -1, denoting it is the concept name being judged
  //typedef std::pair<boost::shared_ptr<Concept>,int> Row;
  typedef std::tuple<boost::shared_ptr<const Edge>,boost::shared_ptr<Concept>,int> Row;
  const std::vector<Row> m_data;

  ///The name of this concept, for example 'my own development'
  const std::string m_focus_name;

  static std::vector<Row>
    CreateData(const boost::shared_ptr</* const */ ConceptMap> map);

  static std::string
    GetFocusName(const boost::shared_ptr<const ConceptMap> sub_concept_map) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPRATECONCEPTTALLYDIALOG_H
