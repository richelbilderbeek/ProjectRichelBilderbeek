#ifndef QTPVDBCREATEASSESSMENTPARTIALDIALOG_H
#define QTPVDBCREATEASSESSMENTPARTIALDIALOG_H

#include <boost/shared_ptr.hpp>

#include <QDialog>

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbfile.h"
#endif


namespace Ui {
class QtPvdbCreateAssessmentPartialDialog;
}

class QtPvdbCreateAssessmentPartialDialog : public QDialog
{
    Q_OBJECT
    
  public:
  explicit QtPvdbCreateAssessmentPartialDialog(
    const boost::shared_ptr<pvdb::File> file,
    QWidget* parent = 0);
  ~QtPvdbCreateAssessmentPartialDialog();

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_save_clicked();

  void AnyEditChanged();

  private:
  Ui::QtPvdbCreateAssessmentPartialDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;
};


#endif // QTPVDBCREATEASSESSMENTPARTIALDIALOG_H
