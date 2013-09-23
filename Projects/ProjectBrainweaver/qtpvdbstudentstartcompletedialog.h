#ifndef QTPVDBSTUDENTSTARTCOMPLETEDIALOG_H
#define QTPVDBSTUDENTSTARTCOMPLETEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbStudentStartCompleteDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbStudentStartCompleteDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtPvdbStudentStartCompleteDialog(const boost::shared_ptr<pvdb::File> file, QWidget* parent = 0);
  QtPvdbStudentStartCompleteDialog(const QtPvdbStudentStartCompleteDialog&) = delete;
  QtPvdbStudentStartCompleteDialog& operator=(const QtPvdbStudentStartCompleteDialog&) = delete;
  ~QtPvdbStudentStartCompleteDialog() noexcept;

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

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBSTUDENTSTARTCOMPLETEDIALOG_H
