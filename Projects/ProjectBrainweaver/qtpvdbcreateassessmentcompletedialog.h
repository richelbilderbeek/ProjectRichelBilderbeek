#ifndef QTPVDBCREATEASSESSMENTCOMPLETEDIALOG_H
#define QTPVDBCREATEASSESSMENTCOMPLETEDIALOG_H

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

namespace Ui {
  class QtPvdbCreateAssessmentCompleteDialog;
}


class QtPvdbCreateAssessmentCompleteDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbCreateAssessmentCompleteDialog(QWidget* parent = 0);
  ~QtPvdbCreateAssessmentCompleteDialog();

  ///Get the filled in concept map focal question
  const std::string GetQuestion() const;

  ///Must the parent go back to the menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  ///Save file to disk
  void Save(const std::string& filename) const;

  ///Fill in the concept map focal question
  void SetQuestion(const std::string& question);

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_save_clicked();

  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtPvdbCreateAssessmentCompleteDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;
};


#endif // QTPVDBCREATEASSESSMENTCOMPLETEDIALOG_H
