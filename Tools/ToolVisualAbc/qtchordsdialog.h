#ifndef QTCHORDSDIALOG_H
#define QTCHORDSDIALOG_H

#include <QDialog>

namespace Ui {
    class QtChordsDialog;
}

class QtChordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QtChordsDialog(QWidget *parent = 0);
    ~QtChordsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QtChordsDialog *ui;
};

#endif // QTCHORDSDIALOG_H
