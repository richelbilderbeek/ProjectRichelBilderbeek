#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "qtgravitywidget.h"
#include "qtgravitywidgetitem.h"
#include "tooltestgravitywidgetmaindialog.h"
#include "ui_tooltestgravitywidgetmaindialog.h"

ToolTestGravityWidgetMainDialog::ToolTestGravityWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTestGravityWidgetMainDialog)
{
  ui->setupUi(this);
}

ToolTestGravityWidgetMainDialog::~ToolTestGravityWidgetMainDialog()
{
  delete ui;
}
