#ifndef QTPVDBASSESSORMENUDIALOG_H
#define QTPVDBASSESSORMENUDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

#include "pvdbfile.h"

namespace Ui {
class QtPvdbAssessorMenuDialog;
}


class QtPvdbAssessorMenuDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtPvdbAssessorMenuDialog(QWidget* parent = 0);
  ~QtPvdbAssessorMenuDialog();

private slots:
  void keyPressEvent(QKeyEvent *);
  void on_button_create_assessment_clicked();

  void on_button_about_clicked();

  void on_button_quit_clicked();

  void on_button_assess_result_clicked();

private:
  Ui::QtPvdbAssessorMenuDialog *ui;
};



#endif // QTPVDBASSESSORMENUDIALOG_H
