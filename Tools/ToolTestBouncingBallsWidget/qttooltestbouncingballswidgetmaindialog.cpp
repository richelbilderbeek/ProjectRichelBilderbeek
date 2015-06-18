#include "qttooltestbouncingballswidgetmaindialog.h"
#include "qtbouncingballswidget.h"
#include "ui_qttooltestbouncingballswidgetmaindialog.h"

QtToolTestBouncingBallsWidgetMainDialog::QtToolTestBouncingBallsWidgetMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolTestBouncingBallsWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtBouncingBallsWidget(this));
}

QtToolTestBouncingBallsWidgetMainDialog::~QtToolTestBouncingBallsWidgetMainDialog()
{
  delete ui;
}
