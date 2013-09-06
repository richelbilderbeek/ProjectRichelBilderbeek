#ifndef QTRUBIKSCLOCKMAINDIALOG_H
#define QTRUBIKSCLOCKMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtRubiksClockMainDialog;
}

namespace ribi {

class QtRubiksClockMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtRubiksClockMainDialog(QWidget *parent = 0);
  ~QtRubiksClockMainDialog();
  
private slots:
  void keyPressEvent(QKeyEvent *);
  void on_button_flip_clicked();
  void resizeEvent(QResizeEvent *);

private:
  Ui::QtRubiksClockMainDialog *ui;
};

} //~namespace ribi

#endif // QTRUBIKSCLOCKMAINDIALOG_H
