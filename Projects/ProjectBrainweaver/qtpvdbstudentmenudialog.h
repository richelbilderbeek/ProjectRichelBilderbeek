#ifndef QTPVDBSTUDENTMENUDIALOG_H
#define QTPVDBSTUDENTMENUDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbStudentMenuDialog; }

namespace ribi {

namespace pvdb {

class QtPvdbStudentMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbStudentMenuDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  QtPvdbStudentMenuDialog(const QtPvdbStudentMenuDialog&) = delete;
  QtPvdbStudentMenuDialog& operator=(const QtPvdbStudentMenuDialog&) = delete;
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

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBSTUDENTMENUDIALOG_H
