#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtsomedialog.h"
#include "ui_qtsomedialog.h"
#pragma GCC diagnostic pop

QtSomeDialog::QtSomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSomeDialog)
{
    ui->setupUi(this);
}

QtSomeDialog::~QtSomeDialog()
{
    delete ui;
}
