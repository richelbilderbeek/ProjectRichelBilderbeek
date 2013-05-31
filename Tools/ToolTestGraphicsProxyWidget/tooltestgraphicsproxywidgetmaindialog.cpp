#include "qttestgraphicsproxywidget.h"
#include "tooltestgraphicsproxywidgetmaindialog.h"
#include "ui_tooltestgraphicsproxywidgetmaindialog.h"

ToolTestGraphicsProxyWidgetMainDialog::ToolTestGraphicsProxyWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTestGraphicsProxyWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtTestGraphicsProxyWidget(this));
}

ToolTestGraphicsProxyWidgetMainDialog::~ToolTestGraphicsProxyWidgetMainDialog()
{
  delete ui;
}
