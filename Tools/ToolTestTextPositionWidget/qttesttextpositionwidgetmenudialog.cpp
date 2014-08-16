#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesttextpositionwidgetmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testtextpositionwidgetmenudialog.h"
#include "qtaboutdialog.h"
#include "qttesttextpositionwidgetmaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qttesttextpositionwidgetmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTextPositionWidgetMenuDialog::QtTestTextPositionWidgetMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTextPositionWidgetMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtTestTextPositionWidgetMenuDialog::~QtTestTextPositionWidgetMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTextPositionWidgetMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestTextPositionWidgetMenuDialog::on_button_about_clicked()
{
  About a = TestTextPositionWidgetMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestTextPositionWidgetMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestTextPositionWidgetMenuDialog::on_button_start_clicked()
{
  QtTestTextPositionWidgetMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

