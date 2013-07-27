#include "qtdialog.h"

#include <QStandardItemModel>
#include <QStyledItemDelegate>

#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_model(new QStandardItemModel)
{
  ui->setupUi(this);
  ui->tree->setModel(m_model);
  ui->tree->setItemDelegate(new QStyledItemDelegate);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  QStandardItem * const item = new QStandardItem;
  item->setText("");
  m_model->appendRow(item);
  ui->tree->scrollToBottom();
  ui->tree->setCurrentIndex(item->index());
  ui->tree->edit(item->index());
}
