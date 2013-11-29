#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstylesheetsettermaindialog.h"

#include <QKeyEvent>

#include "ui_qtstylesheetsettermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtStyleSheetSetterMainDialog::QtStyleSheetSetterMainDialog(
  const std::string& stylesheet, QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStyleSheetSetterMainDialog),
    m_stylesheet(stylesheet)
{
  ui->setupUi(this);
  ui->stylesheet->setPlainText(m_stylesheet.c_str());
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
