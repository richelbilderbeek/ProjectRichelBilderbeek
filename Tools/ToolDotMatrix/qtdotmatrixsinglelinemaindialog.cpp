#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdotmatrixsinglelinemaindialog.h"

#include <cassert>
#include <QPainter>

#include "dotmatrixstring.h"
#include "trace.h"
#include "ui_qtdotmatrixsinglelinemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtDotMatrixSingleLineMainDialog::QtDotMatrixSingleLineMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDotMatrixSingleLineMainDialog),
    m_image{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtDotMatrixSingleLineMainDialog::~QtDotMatrixSingleLineMainDialog() noexcept
{
  delete ui;
}

void ribi::QtDotMatrixSingleLineMainDialog::on_text_textChanged(const QString& text)
{
  const DotMatrixString m(text.toStdString(),1);
  m_image = m.CreateImage();
  ui->image->setPixmap(QPixmap::fromImage(*m_image.get()));
}

#ifndef NDEBUG
void ribi::QtDotMatrixSingleLineMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtDotMatrixSingleLineMainDialog::Test");
  QtDotMatrixSingleLineMainDialog d;
  d.on_text_textChanged("Hello world");
  TRACE("Finished ribi::QtDotMatrixSingleLineMainDialog::Test successfully");
}
#endif
