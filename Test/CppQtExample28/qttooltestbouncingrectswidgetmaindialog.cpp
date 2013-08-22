#include "qtbouncingrectswidget.h"
#include "qttooltestbouncingrectswidgetmaindialog.h"
#include "ui_qttooltestbouncingrectswidgetmaindialog.h"

QtToolTestBouncingRectsWidgetMainDialog::QtToolTestBouncingRectsWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtToolTestBouncingRectsWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtBouncingRectsWidget(this));
}

QtToolTestBouncingRectsWidgetMainDialog::~QtToolTestBouncingRectsWidgetMainDialog()
{
  delete ui;
}
