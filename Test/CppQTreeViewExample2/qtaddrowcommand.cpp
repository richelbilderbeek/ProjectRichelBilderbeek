#include "qtaddrowcommand.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QStandardItem>
#include <QStandardItemModel>

QtAddRowCommand::QtAddRowCommand(
  QStandardItemModel * const model,
  QAbstractItemView * const view)
  : m_model(model), m_view(view)
{

}

void QtAddRowCommand::redo()
{
  QStandardItem * const item = new QStandardItem;
  item->setText(m_text.c_str());
  m_model->appendRow(item);
  m_view->setCurrentIndex(item->index());
}

void QtAddRowCommand::undo()
{
  const int n_rows = m_model->rowCount();
  QStandardItem * const item = m_model->item(n_rows - 1);
  if (item) m_text = item->text().toStdString();
  m_model->removeRow(n_rows - 1);
}
