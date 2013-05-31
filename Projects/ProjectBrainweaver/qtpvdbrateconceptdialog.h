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

private:
    Ui::QtPvdbRateConceptDialog *ui;

  ///The center concept, may be changed when the user clicks OK
  const boost::shared_ptr</* NO CONST */ pvdb::Concept> m_concept;

  ///Cannot be const, only used in calculating the suggestions
  const boost::shared_ptr<pvdb::ConceptMap> m_sub_concept_map;


  ///Test this class
  static void Test();
};


#endif // QTPVDBRATECONCEPTDIALOG_H
