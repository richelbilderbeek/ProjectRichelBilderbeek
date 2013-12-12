#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttooldotmatrixmaindialog.h"

#include <cassert>
#include <QPainter>

#include "qtdotmatrixstring.h"
#include "trace.h"
#include "ui_qttooldotmatrixmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtToolDotMatrixMainDialog::QtToolDotMatrixMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolDotMatrixMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolDotMatrixMainDialog::~QtToolDotMatrixMainDialog() noexcept
{
  delete ui;
}

void ribi::QtToolDotMatrixMainDialog::on_text_textChanged(const QString &)
{
  repaint();
}

void ribi::QtToolDotMatrixMainDialog::paintEvent(QPaintEvent *)
{
  const QtDotMatrixString m(ui->text->text().toStdString(),1);
  QPixmap pixmap = m.CreatePixmap();
  QPainter painter(this);
  const int edit_height
    = ui->text->geometry().height()
    + (2 * this->layout()->margin());

  painter.drawPixmap(
    0,
    edit_height,
    this->width(),
    this->height() - edit_height,
    pixmap);
}

#ifndef NDEBUG
void ribi::QtToolDotMatrixMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtToolDotMatrixMainDialog::Test");
  TRACE("Finished ribi::QtToolDotMatrixMainDialog::Test successfully");
}
#endif
