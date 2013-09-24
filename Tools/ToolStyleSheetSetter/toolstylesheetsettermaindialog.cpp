#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "toolstylesheetsettermaindialog.h"

#include <QKeyEvent>

#include "ui_toolstylesheetsettermaindialog.h"
#pragma GCC diagnostic pop

ribi::ToolStyleSheetSetterMainDialog::ToolStyleSheetSetterMainDialog(
  const std::string& stylesheet, QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::ToolStyleSheetSetterMainDialog),
    m_stylesheet(stylesheet)
{
  ui->setupUi(this);
  ui->stylesheet->setPlainText(m_stylesheet.c_str());
}

ribi::ToolStyleSheetSetterMainDialog::~ToolStyleSheetSetterMainDialog() noexcept
{
  delete ui;
}

void ribi::ToolStyleSheetSetterMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::ToolStyleSheetSetterMainDialog::on_stylesheet_textChanged()
{
  m_stylesheet = ui->stylesheet->toPlainText().toStdString();
  this->setStyleSheet(m_stylesheet.c_str());
}
