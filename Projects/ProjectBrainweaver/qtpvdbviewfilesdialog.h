#ifndef QTPVDBVIEWFILESDIALOG_H
#define QTPVDBVIEWFILESDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtPvdbViewFilesDialog; }

namespace ribi {
namespace pvdb {

class QtPvdbViewFilesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbViewFilesDialog(QWidget* parent = 0);
  QtPvdbViewFilesDialog(const QtPvdbViewFilesDialog&) = delete;
  QtPvdbViewFilesDialog& operator=(const QtPvdbViewFilesDialog&) = delete;
  ~QtPvdbViewFilesDialog() noexcept;
  
private slots:
  void on_button_left_clicked();
  void keyPressEvent(QKeyEvent* event);
  void OnTimerLeft();
  void OnTimerRight();

  void on_button_right_clicked();

private:
  Ui::QtPvdbViewFilesDialog *ui;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBVIEWFILESDIALOG_H
