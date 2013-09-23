#ifndef QTPVDBCREATEASSESSMENTPARTIALDIALOG_H
#define QTPVDBCREATEASSESSMENTPARTIALDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbCreateAssessmentPartialDialog;
}

namespace ribi {

namespace pvdb {

class QtPvdbCreateAssessmentPartialDialog : public QDialog
{
    Q_OBJECT
    
  public:
  explicit QtPvdbCreateAssessmentPartialDialog(
    const boost::shared_ptr<pvdb::File> file,
    QWidget* parent = 0);
  QtPvdbCreateAssessmentPartialDialog(const QtPvdbCreateAssessmentPartialDialog&) = delete;
  QtPvdbCreateAssessmentPartialDialog& operator=(const QtPvdbCreateAssessmentPartialDialog&) = delete;
  ~QtPvdbCreateAssessmentPartialDialog();

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_save_clicked();

  void AnyEditChanged();

  private:
  Ui::QtPvdbCreateAssessmentPartialDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCREATEASSESSMENTPARTIALDIALOG_H
