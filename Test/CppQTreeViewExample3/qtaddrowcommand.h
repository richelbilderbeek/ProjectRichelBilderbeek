#ifndef QTADDROWCOMMAND_H
#define QTADDROWCOMMAND_H

#include <QModelIndex>
#include <QUndoCommand>

struct QStandardItemModel;
struct QAbstractItemView;

struct QtAddRowCommand : public QUndoCommand
{
  QtAddRowCommand(
    QStandardItemModel * const model,
    QAbstractItemView * const view,
    const std::string& text = "");
  void redo();
  void undo();

  private:
  QStandardItemModel * const m_model;
  const QModelIndex m_prev_index;
  std::string m_text;
  QAbstractItemView  * const m_view;
};

#endif // QTADDROWCOMMAND_H
