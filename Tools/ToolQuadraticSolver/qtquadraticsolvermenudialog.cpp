#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtquadraticsolvermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "quadraticsolvermenudialog.h"
#include "qtaboutdialog.h"
#include "qtquadraticsolvermaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qtquadraticsolvermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtQuadraticSolverMenuDialog::QtQuadraticSolverMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtQuadraticSolverMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtQuadraticSolverMenuDialog::~QtQuadraticSolverMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtQuadraticSolverMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtQuadraticSolverMenuDialog::on_button_about_clicked()
{
  About a = QuadraticSolverMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtQuadraticSolverMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtQuadraticSolverMenuDialog::on_button_start_clicked()
{
  QtQuadraticSolverMainDialog d;
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

