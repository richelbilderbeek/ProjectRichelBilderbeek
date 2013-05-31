#ifndef QTPVDBCREATEASSESSMENTMENUDIALOG_H
#define QTPVDBCREATEASSESSMENTMENUDIALOG_H

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

namespace Ui { class QtPvdbCreateAssessmentMenuDialog; }


class QtPvdbCreateAssessmentMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtPvdbCreateAssessmentMenuDialog(QWidget* parent = 0);
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


#endif // QTPVDBCREATEASSESSMENTMENUDIALOG_H
