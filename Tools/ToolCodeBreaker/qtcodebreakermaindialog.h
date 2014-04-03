#ifndef QTCODEBREAKERMAINDIALOG_H
#define QTCODEBREAKERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtCodeBreakerMainDialog;
}

namespace ribi {

class QtCodeBreakerMainDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtCodeBreakerMainDialog(QWidget *parent = 0);
  QtCodeBreakerMainDialog(const QtCodeBreakerMainDialog&) = delete;
  QtCodeBreakerMainDialog& operator=(const QtCodeBreakerMainDialog&) = delete;
  ~QtCodeBreakerMainDialog();
  
private:
  Ui::QtCodeBreakerMainDialog *ui;
};

} //~namespace ribi

#endif // QTCODEBREAKERMAINDIALOG_H
