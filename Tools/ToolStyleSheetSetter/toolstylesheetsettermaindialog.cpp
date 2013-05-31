#include "toolstylesheetsettermaindialog.h"

#include <QKeyEvent>

#include "ui_toolstylesheetsettermaindialog.h"

ToolStyleSheetSetterMainDialog::ToolStyleSheetSetterMainDialog(
  const std::string& stylesheet, QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::ToolStyleSheetSetterMainDialog)
{
  ui->setupUi(this);
  ui->stylesheet->setPlainText(stylesheet.c_str());
}

ToolStyleSheetSetterMainDialog::~ToolStyleSheetSetterMainDialog()
{
  delete ui;
}

void ToolStyleSheetSetterMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ToolStyleSheetSetterMainDialog::on_stylesheet_textChanged()
{
  m_stylesheet = ui->stylesheet->toPlainText().toStdString();
  this->setStyleSheet(m_stylesheet.c_str());
}
