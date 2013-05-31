#ifndef DIALOGCREATE_H
#define DIALOGCREATE_H

#include <QDialog>

namespace Ui {
    class DialogCreate;
}

class DialogCreate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreate(QWidget *parent = 0);
    ~DialogCreate();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogCreate *ui;
};

#endif // DIALOGCREATE_H
