#ifndef QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H
#define QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

#include <boost/shared_ptr.hpp>

#include "pvdbfwd.h"
#include "qthideandshowdialog.h"

namespace Ui {
  class QtPvdbTestCreateSubConceptMapDialog;
}

namespace ribi {

namespace pvdb {

class QtPvdbTestCreateSubConceptMapDialog : public ribi::QtHideAndShowDialog
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

  boost::shared_ptr<QtPvdbConceptMapWidget> m_concept_map;
  boost::shared_ptr<QtPvdbConceptMapWidget> m_sub_concept_map;

  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBTESTCREATESUBCONCEPTMAPDIALOG_H

