#ifndef QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H
#define QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#ifdef SUPPORT_TEST_CONCEPT_MAP_DIALOGS_86543723642

#include "qthideandshowdialog.h"

namespace Ui {
  class QtPvdbTestCreateSubConceptMapDialog;
}

class QtPvdbTestCreateSubConceptMapDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestCreateSubConceptMapDialog(QWidget *parent = 0);
  ~QtPvdbTestCreateSubConceptMapDialog();

private slots:
  ///The user changes to another concept map
  void OnConceptMapChanged();

  ///The user changes to another sub-concept map
  void OnSubConceptMapChanged();

private:
  Ui::QtPvdbTestCreateSubConceptMapDialog *ui;
};

#endif

#endif // QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

