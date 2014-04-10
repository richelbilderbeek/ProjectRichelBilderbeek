#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtbouncingrectswidget.h"
#include "qttooltestbouncingrectswidgetmaindialog.h"
#include "ui_qttooltestbouncingrectswidgetmaindialog.h"
#pragma GCC diagnostic pop

QtToolTestBouncingRectsWidgetMainDialog::QtToolTestBouncingRectsWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtToolTestBouncingRectsWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtBouncingRectsWidget(this));
}

QtToolTestBouncingRectsWidgetMainDialog::~QtToolTestBouncingRectsWidgetMainDialog() noexcept
{
  delete ui;
}
