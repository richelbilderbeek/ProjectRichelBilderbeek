#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtbouncingballswidget.h"
#include "qttooltestbouncingballswidgetmaindialog.h"
#include "ui_qttooltestbouncingballswidgetmaindialog.h"
#pragma GCC diagnostic pop

QtToolTestBouncingBallsWidgetMainDialog::QtToolTestBouncingBallsWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtToolTestBouncingBallsWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtBouncingRectsWidget(this));
}

QtToolTestBouncingBallsWidgetMainDialog::~QtToolTestBouncingBallsWidgetMainDialog()
{
  delete ui;
}
