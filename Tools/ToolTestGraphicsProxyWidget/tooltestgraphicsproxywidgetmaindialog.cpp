#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestgraphicsproxywidget.h"
#include "tooltestgraphicsproxywidgetmaindialog.h"
#include "ui_tooltestgraphicsproxywidgetmaindialog.h"
#pragma GCC diagnostic pop

ToolTestGraphicsProxyWidgetMainDialog::ToolTestGraphicsProxyWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTestGraphicsProxyWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtTestGraphicsProxyWidget(this));
}

ToolTestGraphicsProxyWidgetMainDialog::~ToolTestGraphicsProxyWidgetMainDialog() noexcept
{
  delete ui;
}
