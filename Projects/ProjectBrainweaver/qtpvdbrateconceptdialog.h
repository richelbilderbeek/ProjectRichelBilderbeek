#ifndef QTPVDBRATECONCEPTDIALOG_H
#define QTPVDBRATECONCEPTDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconceptmap.h"
#include "qtpvdbrateconceptitem.h"
#endif

namespace Ui { class QtPvdbRateConceptDialog; }

///Rate the focal concept of a sub-ConceptMap.
class QtPvdbRateConceptDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  ///concept is the center node
  ///sub_concept_map[0] is the same as concept and might be changed
  ///sub_concept_map is non-const, as GetRatedConcept will produce a new concept
  explicit QtPvdbRateConceptDialog(const boost::shared_ptr<pvdb::ConceptMap> sub_concept_map,
    QWidget* parent = 0);
  ~QtPvdbRateConceptDialog();

  ///Set suggested values for this concept
  //void MakeSuggestions(const boost::shared_ptr<const pvdb::ConceptMap> sub_concept_map);

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_ok_clicked();

  void on_button_tally_relevancies_clicked();

  void on_box_complexity_currentIndexChanged(int index);
  void on_box_concreteness_currentIndexChanged(int index);
  void on_box_specificity_currentIndexChanged(int index);

private:
  Ui::QtPvdbRateConceptDialog *ui;

  ///To distinguish between closing the dialog by clicking OK, or by ALT-F4
  bool m_button_ok_clicked;

  ///The center concept, may be changed when the user clicks OK
  const boost::shared_ptr</* NO CONST */ pvdb::Concept> m_concept;

  ///The complexity at this dialog its creation, stored so that the user can cancel the dialog
  const int m_initial_complexity;
  const int m_initial_concreteness;
  const int m_initial_specificity;

  ///Cannot be const, only used in calculating the suggestions
  const boost::shared_ptr<pvdb::ConceptMap> m_sub_concept_map;

  const boost::shared_ptr<QtPvdbConceptMapRateWidget> m_widget;
  //QtPvdbConceptMapRateWidget * const m_widget; //WHY DID I DO THIS???

  void OnRatingComplexityChanged(const pvdb::Concept* concept);
  void OnRatingConcretenessChanged(const pvdb::Concept* concept);
  void OnRatingSpecificityChanged(const pvdb::Concept* concept);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};


#endif // QTPVDBRATECONCEPTDIALOG_H
