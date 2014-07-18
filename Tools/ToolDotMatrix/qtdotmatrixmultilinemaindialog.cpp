#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdotmatrixmultilinemaindialog.h"

#include <cassert>
#include <QPainter>

#include <boost/algorithm/string/split.hpp>

#include "container.h"
#include "dotmatrixtext.h"
#include "trace.h"

#include "ui_qtdotmatrixmultilinemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtDotMatrixMultiLineMainDialog::QtDotMatrixMultiLineMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDotMatrixMultiLineMainDialog),
    m_image{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtDotMatrixMultiLineMainDialog::~QtDotMatrixMultiLineMainDialog()
{
  delete ui;
}

void ribi::QtDotMatrixMultiLineMainDialog::on_edit_textChanged()
{
  const auto v
    = Container().SeperateString(ui->edit->toPlainText().toStdString(),'\n');

  const DotMatrixText m(v,1);
  m_image = m.CreateImage();
  ui->image->setPixmap(QPixmap::fromImage(*m_image.get()));
}

#ifndef NDEBUG
void ribi::QtDotMatrixMultiLineMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtDotMatrixMultiLineMainDialog::Test");
  QtDotMatrixMultiLineMainDialog d;
  d.ui->edit->setPlainText("Hello\n World");
  d.on_edit_textChanged();
  TRACE("Finished ribi::QtDotMatrixMultiLineMainDialog::Test successfully");
}
#endif

