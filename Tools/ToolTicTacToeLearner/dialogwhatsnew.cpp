#include "dialogwhatsnew.h"
#include "ui_dialogwhatsnew.h"

DialogWhatsNew::DialogWhatsNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWhatsNew)
{
    ui->setupUi(this);
}

DialogWhatsNew::~DialogWhatsNew()
{
    delete ui;
}

void DialogWhatsNew::changeEvent(QEvent *e)
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
