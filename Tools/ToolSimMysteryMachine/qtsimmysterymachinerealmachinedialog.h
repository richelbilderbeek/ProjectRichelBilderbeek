#ifndef QTSIMMYSTERYMACHINEREALMACHINEDIALOG_H
#define QTSIMMYSTERYMACHINEREALMACHINEDIALOG_H

#include <QDialog>

namespace Ui {
    class QtSimMysteryMachineRealMachineDialog;
}

class QtSimMysteryMachineRealMachineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QtSimMysteryMachineRealMachineDialog(QWidget *parent = 0);
    ~QtSimMysteryMachineRealMachineDialog();

private:
    Ui::QtSimMysteryMachineRealMachineDialog *ui;
};

#endif // QTSIMMYSTERYMACHINEREALMACHINEDIALOG_H
