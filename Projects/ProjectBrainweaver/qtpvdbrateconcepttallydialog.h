#ifndef QTPVDBRATECONCEPTTALLYDIALOG_H
#define QTPVDBRATECONCEPTTALLYDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "pvdbfwd.h"

namespace Ui {
  class QtPvdbRateConceptTallyDialog;
}

class QtPvdbRateConceptTallyDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  ///Sub concept map is modified by this dialog
  explicit QtPvdbRateConceptTallyDialog(
    const boost::shared_ptr</* const */ pvdb::ConceptMap> sub_concept_map,
    QWidget *parent = 0);

  ~QtPvdbRateConceptTallyDialog();
  
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

private:
  Ui::QtPvdbRateConceptTallyDialog *ui;
  const boost::shared_ptr</* const */ pvdb::ConceptMap> m_map;
};

#endif // QTPVDBRATECONCEPTTALLYDIALOG_H
