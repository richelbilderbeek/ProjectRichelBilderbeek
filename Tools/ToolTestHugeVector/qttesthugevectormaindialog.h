#ifndef QTTESTHUGEVECTORMAINDIALOG
#define QTTESTHUGEVECTORMAINDIALOG

#include <cln/cln.h>

#include "qthideandshowdialog.h"

namespace Ui {
  class Dialog;
}

namespace ribi {

class QtTestHugeVectorMainDialog : public QtHideAndShowDialog
{
    Q_OBJECT

public:
    explicit QtTestHugeVectorMainDialog(QWidget *parent = 0);
    ~QtTestHugeVectorMainDialog();

private:
    Ui::Dialog *ui;
};

} //~namespace ribi

#endif // QTTESTHUGEVECTORMAINDIALOG
