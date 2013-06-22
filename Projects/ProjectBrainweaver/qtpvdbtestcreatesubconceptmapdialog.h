#ifndef QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H
#define QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

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

#endif // QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

