#ifndef QTPVDBSTUDENTSTARTCOMPLETEDIALOG_H
#define QTPVDBSTUDENTSTARTCOMPLETEDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbfile.h"
#endif

namespace Ui { class QtPvdbStudentStartCompleteDialog; }

class QtPvdbStudentStartCompleteDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbStudentStartCompleteDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  ~QtPvdbStudentStartCompleteDialog();

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_associate_clicked();

  void on_button_start_construct_clicked();

  private:
  Ui::QtPvdbStudentStartCompleteDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  boost::shared_ptr<pvdb::File> m_file;

  ///Save to file
  void Save();
};


#endif // QTPVDBSTUDENTSTARTCOMPLETEDIALOG_H
