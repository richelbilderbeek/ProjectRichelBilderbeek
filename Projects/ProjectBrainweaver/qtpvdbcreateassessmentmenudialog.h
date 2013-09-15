#ifndef QTPVDBCREATEASSESSMENTMENUDIALOG_H
#define QTPVDBCREATEASSESSMENTMENUDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbCreateAssessmentMenuDialog; }


namespace ribi {

namespace pvdb {

class QtPvdbCreateAssessmentMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtPvdbCreateAssessmentMenuDialog(QWidget* parent = 0);
  QtPvdbCreateAssessmentMenuDialog(const QtPvdbCreateAssessmentMenuDialog&) = delete;
  QtPvdbCreateAssessmentMenuDialog& operator=(const QtPvdbCreateAssessmentMenuDialog&) = delete;
  ~QtPvdbCreateAssessmentMenuDialog();

  ///Must the parent go back to the menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  protected:
  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_create_assessment_complete_clicked();

signals:

private:
  Ui::QtPvdbCreateAssessmentMenuDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;

  ///The focal concept map question
  std::string m_question;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCREATEASSESSMENTMENUDIALOG_H
