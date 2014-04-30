#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "qtgravitywidget.h"
#include "qtgravitywidgetitem.h"
#include "qttestgravitywidgetmaindialog.h"
#include "ui_qttestgravitywidgetmaindialog.h"
#pragma GCC diagnostic pop

QtTestGravityWidgetMainDialog::QtTestGravityWidgetMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestGravityWidgetMainDialog)
{
  ui->setupUi(this);
}

QtTestGravityWidgetMainDialog::~QtTestGravityWidgetMainDialog() noexcept
{
  delete ui;
}
