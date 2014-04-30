#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestgraphicsproxywidget.h"
#include "qttestgraphicsproxywidgetmaindialog.h"
#include "ui_qttestgraphicsproxywidgetmaindialog.h"
#pragma GCC diagnostic pop

QtTestGraphicsProxyWidgetMainDialog::QtTestGraphicsProxyWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestGraphicsProxyWidgetMainDialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtTestGraphicsProxyWidget(this));
}

QtTestGraphicsProxyWidgetMainDialog::~QtTestGraphicsProxyWidgetMainDialog() noexcept
{
  delete ui;
}
