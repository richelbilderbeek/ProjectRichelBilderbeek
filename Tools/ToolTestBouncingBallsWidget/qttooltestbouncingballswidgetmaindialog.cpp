#include "qtbouncingballswidget.h"
#include "qttooltestbouncingballswidgetmaindialog.h"
#include "ui_qttooltestbouncingballswidgetmaindialog.h"

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
