#ifndef QTSIMMYSTERYMACHINEINSTRUCTIONSDIALOG_H
#define QTSIMMYSTERYMACHINEINSTRUCTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class QtSimMysteryMachineInstructionsDialog;
}

class QtSimMysteryMachineInstructionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QtSimMysteryMachineInstructionsDialog(QWidget *parent = 0);
    ~QtSimMysteryMachineInstructionsDialog();

private:
    Ui::QtSimMysteryMachineInstructionsDialog *ui;
};

#endif // QTSIMMYSTERYMACHINEINSTRUCTIONSDIALOG_H
