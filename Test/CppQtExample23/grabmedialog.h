#ifndef GRABMEDIALOG_H
#define GRABMEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class GrabMeDialog;
}

class GrabMeDialog : public QDialog
{
  Q_OBJECT

public:
  explicit GrabMeDialog(QWidget *parent = 0);
  GrabMeDialog(const GrabMeDialog&) = delete;
  GrabMeDialog& operator=(const GrabMeDialog&) = delete;
  ~GrabMeDialog();

private:
  Ui::GrabMeDialog *ui;

private slots:
  void on_button_grab_clicked();
};

#endif // GRABMEDIALOG_H

