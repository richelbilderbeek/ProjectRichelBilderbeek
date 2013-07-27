#include "qtaddrowcommand.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QStandardItemModel>

#include "qtmyitem.h"

QtAddRowCommand::QtAddRowCommand(
  QStandardItemModel * const model,
  QAbstractItemView * const view,
  const std::string& text)
  : m_model(model),
    m_prev_index(view->currentIndex()),
    m_text(text),
    m_view(view)
{

}

void QtAddRowCommand::redo()
{
  QtMyItem * const item = new QtMyItem(m_text.c_str());
  item->setText(m_text.c_str());
  m_model->appendRow(item);
  m_view->setCurrentIndex(item->index());
  this->setText("Added row at index " + QString::number(item->index().row()));
}

void QtAddRowCommand::undo()
{
  const int n_rows = m_model->rowCount();
  QtMyItem * const item = dynamic_cast<QtMyItem *>(m_model->item(n_rows - 1));
  if (item) m_text = item->text().toStdString();
  m_model->removeRow(n_rows - 1);
  m_view->setCurrentIndex(m_prev_index);
}
