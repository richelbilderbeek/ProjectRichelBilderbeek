#include "dialogcreate.h"
#include "ui_dialogcreate.h"

DialogCreate::DialogCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreate)
{
    ui->setupUi(this);
}

DialogCreate::~DialogCreate()
{
    delete ui;
}

void DialogCreate::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
