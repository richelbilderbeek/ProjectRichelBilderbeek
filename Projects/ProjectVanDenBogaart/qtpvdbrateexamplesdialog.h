#ifndef QTPVDBRATEEXAMPLESDIALOG_H
#define QTPVDBRATEEXAMPLESDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbconcept.h"
#endif

namespace Ui {
class QtPvdbRateExamplesDialog;
}

///Allows the user to rate the examples of a concept
class QtPvdbRateExamplesDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbRateExamplesDialog(const boost::shared_ptr<pvdb::Concept> concept, QWidget* parent = 0);
  ~QtPvdbRateExamplesDialog();

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_prof_clicked();
  void on_button_organisations_clicked();
  void on_button_social_clicked();
  void on_button_target_audience_clicked();
  void on_button_prof_development_clicked();
  void on_button_misc_clicked();
  void on_button_ti_knowledge_clicked();
  void on_button_ok_clicked();

private:
  Ui::QtPvdbRateExamplesDialog *ui;

  ///The concept, which is modified when clicking OK, but remains unmodified when
  ///the user clicks cancel
  const boost::shared_ptr<pvdb::Concept> m_concept;

  ///Obtain the rated examples
  const boost::shared_ptr<pvdb::Examples> GetRatedExamples() const;

  ///Test this class
  static void Test();

};

#endif // QTPVDBRATEEXAMPLESDIALOG_H
