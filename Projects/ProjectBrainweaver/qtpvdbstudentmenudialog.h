#ifndef QTPVDBSTUDENTMENUDIALOG_H
#define QTPVDBSTUDENTMENUDIALOG_H

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

namespace Ui { class QtPvdbStudentMenuDialog; }

class QtPvdbStudentMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbStudentMenuDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  ~QtPvdbStudentMenuDialog();

  ///Get the student his/her name
  const std::string GetName() const;

  ///Save to file
  void Save(const std::string& filename) const;

  ///Set the student his/her name
  void SetName(const std::string& name);

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_clicked();

  void on_button_about_clicked();

  void on_button_quit_clicked();

  void on_edit_name_textChanged(const QString &arg1);

  void on_button_save_clicked();

private:
  Ui::QtPvdbStudentMenuDialog *ui;
  boost::shared_ptr<pvdb::File> m_file;

};


#endif // QTPVDBSTUDENTMENUDIALOG_H
