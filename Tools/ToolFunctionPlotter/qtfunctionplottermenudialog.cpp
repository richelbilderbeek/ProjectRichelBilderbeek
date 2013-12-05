#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtaboutdialog.h"
#include "functionplottermenudialog.h"
#include "qtfunctionplottermaindialog.h"
#include "qtfunctionplottermenudialog.h"
#include "ui_qtfunctionplottermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtFunctionPlotterMenuDialog::QtFunctionPlotterMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtFunctionPlotterMenuDialog)
{
    ui->setupUi(this);
}

ribi::QtFunctionPlotterMenuDialog::~QtFunctionPlotterMenuDialog() noexcept
{
    delete ui;
}

void ribi::QtFunctionPlotterMenuDialog::on_button_start_clicked()
{
  QtFunctionPlotterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtFunctionPlotterMenuDialog::on_button_about_clicked()
{
  About a(FunctionPlotterMenuDialog::GetAbout());
  //a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtFunctionPlotterMenuDialog::on_button_quit_clicked()
{
  this->close();
}
