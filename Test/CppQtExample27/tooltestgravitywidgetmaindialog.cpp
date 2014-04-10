#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "qtgravitywidget.h"
#include "qtgravitywidgetitem.h"
#include "tooltestgravitywidgetmaindialog.h"
#include "ui_tooltestgravitywidgetmaindialog.h"
#pragma GCC diagnostic pop

ToolTestGravityWidgetMainDialog::ToolTestGravityWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTestGravityWidgetMainDialog)
{
  ui->setupUi(this);
}

ToolTestGravityWidgetMainDialog::~ToolTestGravityWidgetMainDialog() noexcept
{
  delete ui;
}
