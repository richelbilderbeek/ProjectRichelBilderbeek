#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtchordsdialog.h"
#include "ui_qtchordsdialog.h"
#pragma GCC diagnostic pop

QtChordsDialog::QtChordsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtChordsDialog)
{
    ui->setupUi(this);
}

QtChordsDialog::~QtChordsDialog()
{
    delete ui;
}

void QtChordsDialog::changeEvent(QEvent *e)
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
