#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstylesheetsettermaindialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testtimer.h"
#include "trace.h"
#include "ui_qtstylesheetsettermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtStyleSheetSetterMainDialog::QtStyleSheetSetterMainDialog(
  const std::string& stylesheet, QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStyleSheetSetterMainDialog),
    m_stylesheet(stylesheet)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->stylesheet->setPlainText(m_stylesheet.c_str());
  //Put the dialog in the screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10, screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::QtStyleSheetSetterMainDialog::~QtStyleSheetSetterMainDialog() noexcept
{
  delete ui;
}

void ribi::QtStyleSheetSetterMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtStyleSheetSetterMainDialog::on_stylesheet_textChanged()
{
  m_stylesheet = ui->stylesheet->toPlainText().toStdString();
  this->setStyleSheet(m_stylesheet.c_str());
}

#ifndef NDEBUG
void ribi::QtStyleSheetSetterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
